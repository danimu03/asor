#!/bin/bash

#man ps

#Mostrar todos los procesos del usuario actual en formato extendido
ps -u $USER -f

#Mostrar los procesos del sistema,...
ps -eo pid,gid,sid,s,command

#PID shell -> SID del nuevo proceso, mismo GID
#1000

exit