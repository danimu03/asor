#!/bin/bash

#En otro terminal 
#sleep 600
#Con pid del terminal

#Listar las señales
#kill -l

#dexconectar close
#kill -s SIGHUP 14180

#interrumpir ctrl+c
#kill -s SIGINT 14180

#parar ctrl+z
kill -s SIGTSTP 14180
pkill sleep -SIGTSTP


#...

exit