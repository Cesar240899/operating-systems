#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <dirent.h>
#include <unistd.h>
#include <errno.h>

void analizar_archivo(const char *ruta) {
    struct stat informacion;
    if (stat(ruta, &informacion) == 0) {
        printf("Archivo: %s\n", ruta);
        printf("Tamaño: %lld bytes\n", (long long)informacion.st_size);
        printf("Último acceso: %ld\n", informacion.st_atime);
        printf("Última modificación: %ld\n", informacion.st_mtime);
        printf("Permisos: %o\n", informacion.st_mode & 0777);
        printf("====================\n");
    } else {
        printf("Error al analizar %s: %s\n", ruta, strerror(errno));
    }
}

void analizar_directorio(const char *ruta) {
    DIR *dir = opendir(ruta);
    if (dir == NULL) {
        printf("Error al abrir el directorio %s: %s\n", ruta, strerror(errno));
        return;
    }

    struct dirent *entrada;
    while ((entrada = readdir(dir)) != NULL) {
        if (strcmp(entrada->d_name, ".") == 0 || strcmp(entrada->d_name, "..") == 0) {
            continue;
        }
        
        char ruta_completa[PATH_MAX];
        snprintf(ruta_completa, sizeof(ruta_completa), "%s/%s", ruta, entrada->d_name);
        
        struct stat informacion;
        if (stat(ruta_completa, &informacion) == 0) {
            if (S_ISREG(informacion.st_mode)) {
                analizar_archivo(ruta_completa);
            } else if (S_ISDIR(informacion.st_mode)) {
                printf("Explorando directorio: %s\n", ruta_completa);
                pid_t pid = fork();
                if (pid == 0) {
                    analizar_directorio(ruta_completa);
                    exit(0);
                }
            }
        } else {
            printf("Error al obtener información de %s: %s\n", ruta_completa, strerror(errno));
        }
    }
    
    closedir(dir);
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("Uso: %s <ruta>\n", argv[0]);
        return 1;
    }

    const char *ruta_inicial = argv[1];
    analizar_directorio(ruta_inicial);

    return 0;
}
