#!/bin/bash

touch prueba_fichero
ls -l prueba_fichero
chmod 645 prueba_fichero
#chmod u+rw-x,g+r-wx,o+r+x-w prueba_permisos
ls -l prueba_fichero

exit