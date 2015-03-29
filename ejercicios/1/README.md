
### 10PASOS PARA COMPILAR Y GENERAR EL FICHERO EJECUTABLE CON AUTOCONF Y AUTOMAKE

1) Creamos el fichero configure.ac en la carpeta principal del proyecto.

2) Ejecutamos autoconf. Este comando nos creará una carpeta llamada autom4te.cache y el ejecutable configure

 $ autoconf

3) Creamos el fichero Makefile.am en la carpeta principal del proyecto.

4) Creamos un fichero Makefile.am dentro de cada uno de los directorios de nuestro proyecto.

5) Ejecutamos aclocal. Este comando nos genera un fichero llamado aclocal.m4, que contendrá todos los comando de Makefile que nos harań falta para conpilar nuestro proyecto.

 $ aclocal

6) Ejecutamos automake. Este comando a partir de los ficheros configure.ac y Makefile.am, genera una ficheros llamados Makefile.in, con una serie de comprobaciones de sintaxis.
 
 $ automake --add-missing

7) Ejecutamos de nuevo autoconf, esto genera de nueco el ejecutable configure teniendo en cuenta las comprobaciones anteriores

8) Ejecutamos el archivo configure, que pondrá en orden todos los prerequisitos para compilar nuestro programa:

 $ ./configure

9) Compilamos nuestro programa:

 $ make

10) Entramos en la carpeta src y tendremos nuestro programa ejecutable.


 #Más información en:
   - http://www.gnu.org/software/automake/manual/autoconf.html
   - http://www.gnu.org/software/automake/manual/automake.html

