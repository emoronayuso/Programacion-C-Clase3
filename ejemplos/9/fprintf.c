#include <stdio.h>
#include <stdlib.h>

void genera_mensaje(FILE *file)
{
	int linea = 0;

	while (linea < 6) {
		fprintf(file, "Linea %d: Mensaje de prueba\n", linea);
		linea++;
	}
	rewind(file);
}

int main (void)
{
	FILE *file = fopen("datos.dat", "a+");
	char *code;

	if (file == NULL) {
		perror("No se ha podido abrir el fichero");
		return -1;
	}

	genera_mensaje(file);

	if ((code = (char *) malloc(101)) == NULL) {
		perror("No se ha podido reservar memoria");
		return -1;
	}

	while(fgets(code, 100, file)) {
		printf("%s", code);
	}

	free(code);
	
	if (fclose(file) == EOF) {
		perror("El fichero no se ha cerrado correctamente");
		return -1;
	}

	return 0;
}
