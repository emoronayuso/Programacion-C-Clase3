# Datos principales para generar el configure
AC_INIT([concesionario], [1.0], [emoronayuso@gmail.com])
AM_INIT_AUTOMAKE
AC_CONFIG_SRCDIR([src/main.c])

# Comprueba si tenemos el compilador C (GNU CC)
AC_PROG_CC

# Comprueba las cabeceras
AC_CHECK_HEADERS([stdlib.h stdint.h stdbool.h])

# Archivos de configuracion de Makefile
AC_CONFIG_FILES([Makefile src/Makefile])

# Comprobamos si existe la funcion malloc en nuestras bibliotecas
AC_FUNC_MALLOC

# Fichero que generamos
AC_OUTPUT
