#!/bin/bash
mkdir pruebaDir
touch pruebaFich
ln -s pruebaDir e-simb-fi
ln -s pruebaFich e-simb-dir  
ls -l
ls -i

ln pruebaDir e-rig-fi  
ln pruebaFich e-rig-dir  
ls -li

exit