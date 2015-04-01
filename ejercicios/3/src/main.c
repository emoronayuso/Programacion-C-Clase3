#include "../include/concesionario.h"
#include <stdio.h>
#include <getopt.h>
#include <libxml2/libxml/tree.h>

void show_help(void);
static void get_nodo_xml(FILE *data_base, xmlNode * nodo_root);
static void set_lista_coches_from_nodo_xml(FILE *data_base, xmlNode * a_node);
static void get_lista_coches(FILE *fd);
static void set_lista_coches(FILE *fd, uint32_t id, char *ma, char *ga);
static int close_database(FILE *fd);

int main(int argc, char *argv[])
{
	char matricula[15] = "";
	char gama[50] = "";
	uint32_t id = 0;
	char dueno[50] = "";
	int num_param_req = 9;

	xmlDoc   *document = NULL;
	xmlNode  *root_element = NULL;

	int val, option_index = 0;
	static struct option long_options[] = {
		{ "matricula", required_argument, 0, 'm' },
		{ "id", required_argument, 0, 'i' },
		{ "gama", required_argument, 0, 'g' },
		{ "propietario", required_argument, 0, 'p' },
		{ "xml", required_argument, 0, 'x' },
		{ "list", no_argument, 0, 'l' },
		{ 0 }
	};

	FILE *file = fopen("datos.dat", "a+");

	if (file == NULL) {
		perror("El fichero de base de datos 'datos.dat' no"\
                       " se ha abierto correctamente o no existe");
		return -1;
	}

	while ((val = getopt_long(argc, argv, "m:i:g:p:x:l-", long_options,
                                   &option_index)) != -1 ) {
		switch (val) {
		case 'm':
			strncpy(matricula, optarg, 14);
			break;
		case 'i':
			id = atoi(optarg);
			break;
		case 'g':
			strncpy(gama, optarg, 49);
			break;
		case 'p':
			strncpy(dueno, optarg, 49);
			break;
		case 'x':
		/* Guia de referencia: http://xmlsoft.org/html/index.html */
			num_param_req = 3;

			if ((document = xmlReadFile(optarg, NULL, 0)) == NULL) {
				perror("No se ha podido abrir el fichero XML"
                                       " o el fichero esta vacio");
				return -1;
			}

			root_element = xmlDocGetRootElement(document);
			get_nodo_xml(file, root_element);
			xmlFreeDoc(document);
			xmlCleanupParser();

			close_database(file);
			return 0;
		case 'l':
			get_lista_coches(file);
			return 0;
		default:
			show_help();
			return 0;
		}
	}

	if (argc != num_param_req) {
		show_help();
		return 0;
	}

	set_lista_coches(file, id, matricula, gama);

	close_database(file);

	return 0;
}



void show_help(void)
{
	printf("\nCONCESIONARIO\n"\
               " Parametros para incluir un nuevo coche al consecionario:"\
               "\n  -m/-matricula <matricula>"\
               "\n         -i/-id <id>"\
               "\n       -g/-gama <gama>"\
               "\n-p/-propietario <propietario>\n"\
               "\n O mediante un fichero xml con la información de los coches"\
               "\n        -x/-xml <fichero_xml>\n"\
               "\nConsulta listado de coches:"\
               "\n-l/-list\n"\
              );
}

static void get_nodo_xml(FILE *data_base, xmlNode * nodo_root)
{
	xmlNode *cur_node = NULL;

	for (cur_node = nodo_root; cur_node; cur_node = cur_node->next) {

		if (cur_node->type == XML_ELEMENT_NODE &&
                    0 == strcmp("Coche", cur_node->name))
		{
			set_lista_coches_from_nodo_xml(data_base, cur_node);
		}

		get_nodo_xml(data_base, cur_node->children);
	}
}

static void set_lista_coches_from_nodo_xml(FILE *data_base, xmlNode * a_node)
{
	xmlAttr *cur_node = NULL;
	char matricula[15] = "";
	char gama[50] = "";
	uint32_t id = 0;

	for (cur_node = a_node->properties; cur_node;
             cur_node = cur_node->next)
	{
		if(cur_node->type == XML_ATTRIBUTE_NODE) {

			if (0 == strcmp("matricula",cur_node->name))
				strcat(matricula, cur_node->children->content);

			if (0 == strcmp("modelo",cur_node->name))
				strcat(gama, cur_node->children->content);

			if (0 == strcmp("id", cur_node->name))
				id = atoi(cur_node->children->content);
		}
	}

	set_lista_coches(data_base, id, matricula, gama);
}


static void get_lista_coches(FILE *fd)
{
	char cad[1000] = "";

	while (EOF != (fscanf(fd,"%s\n", cad)))
		printf("%s\n", cad);
}

static void set_lista_coches(FILE *fd, uint32_t id, char * ma, char * ga)
{
	fprintf(fd,"--ID:%d--MATRICULA:%s--GAMA:%s\n",id, ma, ga);
}

static int close_database(FILE *fd)
{
	if (fclose(fd) == EOF) {
		perror("El fichero no se ha cerrado correctamente");
		return -1;
	}
	return 0;
}

