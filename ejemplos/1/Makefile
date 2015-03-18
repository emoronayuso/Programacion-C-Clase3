NAME=concesionario.out
BIN_DIR=bin


all: build ${NAME}

${NAME}: ${BIN_DIR}/concesionario.o ${BIN_DIR}/coche.o main.c
	     gcc -g ${BIN_DIR}/coche.o ${BIN_DIR}/concesionario.o main.c -o ${NAME} 

${BIN_DIR}/concesionario.o: concesionario.c concesionario.h
	     gcc -g -c concesionario.c -o ${BIN_DIR}/concesionario.o

${BIN_DIR}/coche.o: coche.c coche.h
	     gcc -g -c coche.c -o ${BIN_DIR}/coche.o

build:
	mkdir bin

clean:
	rm -rf bin
