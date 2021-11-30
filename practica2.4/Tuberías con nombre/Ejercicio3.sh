#!/bin/bash

#man mkfifo

mkfifo t
ls -l
stat t

#en un terminal
echo "prueba" > t

#en otro terminar
cat t 

exit