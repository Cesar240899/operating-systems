#!/bin/bash


# Intervalo de tiempo en segundos entre cada monitoreo
tiempo=60  # 1 minuto

while true; do
    # Obtener la hora actual
    horaAct=$(date +"%Y-%m-%d %H:%M:%S")

    # Obtener la lista de usuarios conectados y tiempo de arranque
    usuarioConec=$(who |awk '{printf $1}')
    arranque=$(who -b)
    
    # Escribir la información en la bitácora
    echo "$arranque" >> Bitacora.txt
    echo "Hora de monitoreo: $horaAct" >> Bitacora.txt
    echo "Usuario: $usuarioConec " >> Bitacora.txt
    echo "************************" >> Bitacora.txt
    
    # Esperar el intervalo de tiempo antes de la próxima verificación
    sleep "$tiempo"
done
