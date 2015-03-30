#include <stdio.h>

int main()
{
	FILE *fichero;
	char nombre[10] = "datos.dat";

	if ( (fichero = fopen(nombre, "w")) == NULL) {
		perror("\nEl fichero no se ha abierto correctamente\n");
		return -1;
	}

	printf("El fichero con identificador %p, se ha abirto correctamente\n",
               fichero);

	/* printf("Fichero: %s -> ", nombre); */
	/* if (fichero) { */
	/* 	printf("creado (ABIERTO)\n"); */
	/* } else { */
	/* 	printf("Error (NO ABIERTO)\n"); */
	/* 	return -1; */
	/* } */

	if (!fclose(fichero)) {
		printf("Fichero cerrado\n");
	} else {
		perror("Fichero NO CERRADO\n");
		return -1;
	}

	return 0;
}
