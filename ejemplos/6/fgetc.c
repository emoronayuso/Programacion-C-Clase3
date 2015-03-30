#include <stdio.h>
#include <stdlib.h>

void genera_mensaje(FILE *file)
{
	fputc('K', file);
	fputc('i', file);
	fputc('i', file);
	fputc('k', file);
	fputc('e', file);
	fputc('L', file);
	rewind(file);
}

int main(void)
{
	FILE *file = fopen("datos.dat", "a+");
	char *code;
	int c;

	if (file == NULL) {
		perror("No se ha abierto el fichero correctamente");
		return -1;
	}

	genera_mensaje(file);

	if ((code = (char *) malloc(1001)) == NULL ) {
		perror("No se ha podido reservar memoria");
		return -1;
	}

	while ((c = fgetc(file)) != EOF) {
		code[n++] = (char) c;
	}

	code[n] = '\0';
	printf("El texto leido es %s\n", code);

	free(code);

	if (fclose(file) == EOF){
		perror("El fichero no se ha cerrado correctamente");
		return -1;
	}

	return 0;
}
