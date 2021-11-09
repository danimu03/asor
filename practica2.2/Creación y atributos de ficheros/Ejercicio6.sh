#!/bin/bash

umask 0027
touch prueba
ls -l
rm prueba
umask 0022

exit

