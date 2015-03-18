#include "gestor_tareas_listas.h"
#include <string.h>

struct gestor_tareas{
	struct list_head  lista_tareas;
	uint32_t          num_tareas;
	char              *nombre;

	uint32_t          flags;
};

struct gestor_tareas *curso_gestor_tareas_alloc(void)
{
	char * nombre_ini = "Nuevo gestor de tareas";
	struct gestor_tareas *gt;
	int i;

	gt = (struct gestor_tareas *)malloc(sizeof(struct gestor_tareas));

	/* Inicializamos las variables */
	gt->num_tareas = 0;
	gt->flags &= ~(1 << CURSO_GESTOR_TAREAS_ATTR_NUM_TAREAS);

	INIT_LIST_HEAD(&gt->lista_tareas);

	gt->nombre = strdup(nombre_ini);

	return gt;
}

void curso_gestor_tareas_free(struct gestor_tareas *gt)
{
	struct tarea *tarea_actual;
	struct list_head *pos, *next;

	if (gt->num_tareas != 0) {
		list_for_each_safe(pos, next, &gt->lista_tareas){
			tarea_actual = list_entry(pos, struct tarea, head);
			list_del(pos);
			curso_tarea_free(tarea_actual);
		}
	}

	if (gt->flags & (1 << CURSO_GESTOR_TAREAS_ATTR_NOMBRE))
		xfree(gt->nombre);

	xfree(gt);
}

void curso_gestor_tareas_attr_unset(struct gestor_tareas *gt, uint16_t attr,
                                    uint32_t num)
{

	struct tarea *tarea_actual;
	struct list_head *pos, *next;
	int count = 0;

	if (!(gt->flags & (1 << attr)))
		return;

	switch (attr) {
	case CURSO_GESTOR_TAREAS_ATTR_LIST_TAREAS:
		list_for_each_safe(pos, next, &gt->lista_tareas) {
			tarea_actual = list_entry(pos, struct tarea, head);
			if (count == num)
				break;
			count++;
		}

		list_del(&(tarea_actual->head));
		curso_tarea_free(tarea_actual);

		gt->num_tareas--;

		// Si hemos borrado la ultima tarea ponemos el flag a 0
		if (gt->num_tareas == 0)
			gt->flags &= ~(1 << attr);

		break;
	case CURSO_GESTOR_TAREAS_ATTR_NUM_TAREAS:
		break;
	case CURSO_GESTOR_TAREAS_ATTR_NOMBRE:
		if (gt->nombre) {
			xfree(gt->nombre);
			//gt->nombre = NULL;
		}
		gt->flags &= ~(1 << attr);
		break;
	}

}

bool curso_gestor_tareas_attr_is_set(const struct gestor_tareas *gt,
                                     uint16_t attr)
{
	return gt->flags & (1 << attr);
}

/* Funciones get */
const void *curso_gestor_tareas_attr_get_data(struct gestor_tareas *gt,
                                              uint16_t attr, uint32_t num)
{
	struct tarea *tarea_actual;
	struct list_head *pos, *next;
	int count = 0;

	if (!(gt->flags & (1 << attr)))
		return NULL;

	switch(attr) {
	case CURSO_GESTOR_TAREAS_ATTR_LIST_TAREAS:
		list_for_each_safe(pos, next, &gt->lista_tareas) {
			tarea_actual = list_entry(pos, struct tarea, head);
			if (count == num)
				break;
			count++;
		}
		return (void *)tarea_actual;

	case CURSO_GESTOR_TAREAS_ATTR_NUM_TAREAS:
		return &(gt->num_tareas);

	case CURSO_GESTOR_TAREAS_ATTR_NOMBRE:
		return gt->nombre;
	}
	return NULL;

}

const char *curso_gestor_tareas_attr_get_str(struct gestor_tareas *gt,
                                             uint16_t attr)
{
	return curso_gestor_tareas_attr_get_data(gt, attr, 0);
}


uint32_t curso_gestor_tareas_attr_get_u32(struct gestor_tareas *gt,
                                          uint16_t attr)
{
	const char *ret = curso_gestor_tareas_attr_get_data(gt, attr, 0);
	return ret == NULL ? 0 : *((uint32_t *)ret);
}

struct tarea *curso_gestor_tareas_attr_get_tarea(struct gestor_tareas *gt,
                                                 uint16_t attr, uint32_t pos)
{
	return (struct tarea *)curso_gestor_tareas_attr_get_data(gt, attr, pos);
}

/* Funciones set */
void curso_gestor_tareas_attr_set_data(struct gestor_tareas *gt, uint16_t attr,
                                void *data)
{
	struct tarea *tarea_actual;
	struct list_head *pos, *next;
	struct tarea *tarea_nueva;

	tarea_nueva = (struct tarea *)data;


	if (attr > CURSO_GESTOR_TAREAS_ATTR_MAX)
		return;

	switch (attr) {
	case CURSO_GESTOR_TAREAS_ATTR_LIST_TAREAS:
		/* Incluimos la tarea en la lista, segun su prioridad */

		//Si la lista esta vacia
		if (list_empty(&gt->lista_tareas))
			list_add(&(tarea_nueva->head), &gt->lista_tareas);
		else {
			list_for_each_safe(pos, next, &gt->lista_tareas) {
				tarea_actual = list_entry(pos, struct tarea,
                                                          head);
				if (tarea_actual->prioridad >
                                    tarea_nueva->prioridad)
					list_add_tail(&(tarea_nueva->head),
                                                        pos);
			}
		}

		// Ponemos el flag de num_tareas a 1
		gt->flags |= (1 << CURSO_GESTOR_TAREAS_ATTR_NUM_TAREAS);

		gt->num_tareas++;
		break;

	case CURSO_GESTOR_TAREAS_ATTR_NUM_TAREAS:
		break;

	case CURSO_GESTOR_TAREAS_ATTR_NOMBRE:
		if (gt->nombre)
			xfree(gt->nombre);
		gt->nombre = strdup(data);
		break;
	}

	gt->flags |= (1 << attr);

}

void curso_gestor_tareas_attr_set_tarea(struct gestor_tareas *gt,
                                        uint16_t attr, struct tarea *t)
{
	curso_gestor_tareas_attr_set_data(gt, attr, t);
}

void curso_gestor_tareas_attr_set_u32(struct gestor_tareas *gt, uint16_t attr,
                                      uint32_t data)
{
	curso_gestor_tareas_attr_set_data(gt, attr, &data);
}


void curso_gestor_tareas_attr_set_str(struct gestor_tareas *gt, uint16_t attr,
                                      char *data)
{
	curso_gestor_tareas_attr_set_data(gt, attr, data);
}


/* Función que imprime todas las tareas */
int curso_gestor_tareas_snprintf(char *buf, size_t size,
                                 struct gestor_tareas *gt)
{
	struct tarea *tarea_actual;
	struct list_head *pos, *next;
	int ret = 0;

	if (gt->num_tareas != 0) {
		list_for_each_safe(pos, next, &gt->lista_tareas){
			tarea_actual = list_entry(pos, struct tarea, head);
			ret += curso_tarea_snprintf(buf + ret, size - ret,
                                                    tarea_actual);

			ret += snprintf(buf + ret, size - ret, "\n");
		}
	}

	return ret;
}
