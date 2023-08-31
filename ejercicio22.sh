#!/bin/bash

# Función para generar una cadena aleatoria de longitud específica
generarCadenas() {
    local length=$1
    cat /dev/urandom | tr -dc 'a-zA-Z0-9@#$%&' | fold -w "$length" | head -n 1
}

# Función para verificar si una cadena cumple con las restricciones
verificarRestriccion() {
    local string="$1"
    local mayus=$(echo "$string" | grep -o '[A-Z]' | wc -l)  
    local minus=$(echo "$string" | grep -o '[a-z]' | wc -l)   
    local digis=$(echo "$string" | grep -o '[0-9]' | wc -l)
    local simbols=$(echo "$string" | grep -o '[@#$%&]' | wc -l)
	
    # delimitar la cadena de 8 a 12
    if [[ ${#string} -ge 8 && ${#string} -le 12 && 
          $mayus -ge 2 && $minus -ge 2 && 
          $digis -ge 2 && $simbols -ge 2 ]]; then
        return 0
    else
        return 1  # no cumple las restricciones
    fi
}

# Obtener el número de cadenas a generar
read -p "Ingrese el número de cadenas a generar: " n

# Verificar si el usuario quiere guardar las cadenas en un archivo
read -p "¿Desea guardar las cadenas en un archivo? (s/n): " guardaArchi

if [[ $guardaArchi == "s" ]]; then
    read -p "Ingrese el nombre del archivo: " nomArchi
    touch "$nomArchi"
fi

# Generar y verificar las cadenas aleatorias
contador=0
while [[ $contador -lt $n ]]; do
    cadenaAle=$(generarCadenas $((RANDOM % 5 + 8))) #cadena de caracteres utilizando el número aleatorio como longitud para la cadena.
    if verificarRestriccion "$cadenaAle"; then
        contador=$((contador + 1))
        echo "Cadena generada: $cadenaAle"
        if [[ $guardaArchi == "s" ]]; then
            echo "$cadenaAle" >> "$nomArchi"
        fi
    fi
done

if [[ $guardaArchi == "s" ]]; then
    echo "Cadenas generadas guardadas en el archivo: $nomArchi"
fi
