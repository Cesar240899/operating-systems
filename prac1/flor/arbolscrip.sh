#!/bin/bash

# Pedimos al usuario el número de tallos
echo "¿Cuántos tallos quieres?"
read tallos

# Pedimos al usuario el número de flores
echo "¿Cuántas flores quieres?"
read flores

# Pedimos al usuario el número de pétalos por flor
echo "¿Cuántos pétalos quieres por flor?"
read petalos

# Compilamos el código
gcc -o flor flor.c

# Ejecutamos el código
./flor $tallos $flores $petalos

