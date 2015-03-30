#include <stdio.h>
#include <string.h>

int main()
{
	FILE *fp;
	char cad[] = "ejemplo fwrite/fread";
	char buffer[20];

	fp = fopen("datos.dat", "w+");
	if (fp == NULL) {
		perror("No se ha abierto el fichero correctamente");
		return -1;
	}

	if (fwrite(cad, strlen(cad) + 1, 1, fp) == 0){
		perror("No se ha podido escribir ene l fichero");
		return -1;
	}

	rewind(fp);

	if (fread(buffer, strlen(cad) + 1, 1, fp) == 0){
		perror("No se ha podido leer del fichero");
		return -1;
	}

	printf("%s\n", buffer);

	if (EOF == fclose(fp)) {
		perror("El fichero no se ha cerrado correctamente");
		return -1;
	}

	return 0;
}
