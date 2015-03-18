# Datos iniciales para generar el configure
AC_INIT([gestor_tareas_listas], [1.0], [emoronayuso@gmail.com])
AM_INIT_AUTOMAKE([-Wall -Werror foreign])
AC_CONFIG_SRCDIR([src/main.c])

# Comprueba si tenemos el compilador C (GNU cc)
AC_PROG_CC

# Comprobamos las bibliotecas

# Comprobamos si estan las cabeceras
AC_CHECK_HEADERS([stdlib.h stdint.h stdbool.h])

# Comprobamos si existe la funcion malloc en nuestras bibliotecas
AC_FUNC_MALLOC

# Ficheros que generamos
AC_OUTPUT(Makefile src/Makefile)
