# Función para convertir el tamaño en unidades legibles
human_readable_size() {
    local size=$1
    local units=("bytes" "KB" "MB" "GB" "TB")
    local unit=0

    while [[ $size -ge 1024 && $unit -lt 4 ]]; do
        size=$((size / 1024))
        unit=$((unit + 1))
    done

    echo "$size ${units[unit]}"
}

# Obtén una lista de todos los directorios en el directorio actual
directorios=$(find . -type d)

# Iterar sobre cada directorio
for directorio in $directorios; do
    # Obtén el tamaño del directorio
    tamanio=$(du -s "$directorio" | cut -f1)
    
    # Convierte el tamaño en unidades legibles por humanos
    tamanio_legible=$(human_readable_size $tamanio)
    
    # Imprime el tamaño del directorio en unidades legibles
    echo "Directorio '$directorio': Tamaño: $tamanio_legible"
done
