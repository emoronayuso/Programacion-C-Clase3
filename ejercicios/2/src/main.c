#include "../include/concesionario.h"
#include <stdio.h>
#include <getopt.h>

void show_help(void)
{
	printf("\nDebe usar el comando con los siguientes"\
               " parametros:"\
               "\n  -m/-matricula <matricula>"\
               "\n         -i/-id <id>"\
               "\n       -g/-gama <gama>"\
               "\n-p/-propietario <propietario>\n"\
              );
}

int main(int argc, char *argv[])
{
	struct coche *c1;
	struct concesionario *con;
	char info[4000];
	char matricula[15] = "";
	char gama[50] = "";
	uint32_t id = 0;
	char dueno[50] = "";

	int val, option_index = 0;
	static struct option long_options[] = {
		{ "matricula", required_argument, 0, 'm' },
		{ "id", required_argument, 0, 'i' },
		{ "gama", required_argument, 0, 'g' },
		{ "propietario", required_argument, 0, 'p' },
		{ 0 }
	};

	while ( (val = getopt_long(argc, argv, "m:i:g:p:", long_options,
                                   &option_index)) != -1 ) {
		switch (val) {
		case 'm':
			printf("\n La nueva matricula es %s\n", optarg);
			strncpy(matricula, optarg, 14);
			break;
		case 'i':
			printf("\n El nuevo id es %d\n", atoi(optarg));
			id = atoi(optarg);
			break;
		case 'g':
			printf("\n La gama es %s\n", optarg);
			strncpy(gama, optarg, 49);
			break;
		case 'p':
			printf("\n El propietario del concecionario es %s\n",
                               optarg);
			strncpy(dueno, optarg, 49);

					break;
		default:
			show_help();
			return 0;
		}
	}

	if (argc != 9) {
		show_help();
		return 0;
	}

	c1 = curso_coche_alloc();
	con = curso_concesionario_alloc();

	curso_coche_attr_set_str(c1, CURSO_COCHE_ATTR_MATRICULA, matricula);
	curso_coche_attr_set_u32(c1, CURSO_COCHE_ATTR_ID, id);
	curso_coche_attr_set_str(c1, CURSO_COCHE_ATTR_MARCA, gama);
	curso_concesionario_attr_set_str(con, CURSO_CONCESIONARIO_ATTR_DUENO,
                                         dueno);

	curso_concesionario_attr_set_coche(con, CURSO_CONCESIONARIO_ATTR_COCHE,
                                           c1);


	curso_concesionario_snprintf(info, sizeof(info), con);
	printf("%s", info);

	curso_concesionario_free(con);
	return 0;
}
