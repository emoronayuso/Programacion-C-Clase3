#include <stdio.h>
#include <stdlib.h>

void genera_mensaje(FILE *file)
{
	fputs("El mensaje a escribir es Kike", file);
	rewind(file);
}

int main (void)
{
	FILE *file = fopen("datos.dat", "a+");
	char *code;

	if (file == NULL) {
		perror("El fichero no se ha abierto correctamente");
		return -1;
	}

	genera_mensaje(file);

	if ((code = (char *) malloc(101)) == NULL) {
		perror("No se ha podido reservar memoria");
		return -1;
	}

	while(fgets(code, 100, file)) {
		printf("%s\n", code);
	}

	free(code);

	if (fclose(file) == EOF) {
		perror("El fichero no se ha cerrado correctamente");
		return -1;
	}

	return 0;
}
