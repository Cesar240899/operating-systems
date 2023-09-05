#!/bin/bash

# Pedimos al usuario el número de niveles para el árbol de procesos
echo "Indique un numero impar (cantidad de niveles del árbol):"
read nivel

# Verificamos si el número ingresado es impar
if [ $((nivel % 2)) -eq 0 ]; then
    echo "El número ingresado no es impar. Saliendo del programa."
    exit 1
fi

# Compilar el programa
gcc -o impar arbolimpar.c

# Verificamos si la compilación fue exitosa
if [ $? -ne 0 ]; then
    echo "Error al compilar el programa. Saliendo del programa."
    exit 1
fi

# Ejecutar el programa en segundo plano y guardar su PID
./impar $nivel &

# Obtener el PID del proceso principal
mainPid=$!

# Esperar un poco para que los procesos se creen
sleep 3

# Mostrar el árbol de procesos antes de matar procesos
echo "Árbol de procesos Impar"
pstree -p $mainPid
