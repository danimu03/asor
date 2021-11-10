#!/bin/bash

#Cambiar valor de nice a -10
sudo renice -n -10 11284  #ps (obtencion de pid)
#cambiar politica de planificacion 
sudo chrt -f -p 12 11284
sudo chrt -p 11284

exit