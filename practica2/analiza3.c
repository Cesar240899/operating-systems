#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <dirent.h>
#include <time.h> // Necesario para trabajar con fechas y horas
#include <sys/wait.h>

// Función para mostrar la información de un archivo dado su ruta
void mostrar_info_archivo(const char *ruta) {
    struct stat info;
    if (stat(ruta, &info) == 0) {
        printf("Ruta: %s\n", ruta);
        printf("Tamaño: %ld bytes\n", info.st_size);
        printf("Tipo de archivo: %s\n", S_ISDIR(info.st_mode) ? "Directorio" : "Archivo");
        printf("Permisos: %o\n", info.st_mode & 0777);

        // Obtener la fecha y hora de la última modificación
        struct tm *mod_time = localtime(&info.st_mtime);
        char mod_time_str[80];
        strftime(mod_time_str, sizeof(mod_time_str), "%Y-%m-%d %H:%M:%S", mod_time);
        printf("Última modificación: %s\n", mod_time_str);

        // Obtener la fecha y hora del último acceso
        struct tm *access_time = localtime(&info.st_atime);
        char access_time_str[80];
        strftime(access_time_str, sizeof(access_time_str), "%Y-%m-%d %H:%M:%S", access_time);
        printf("Último acceso: %s\n", access_time_str);

        printf("================================\n");
    } else {
        perror("stat"); // Manejo de errores si no se puede obtener la información del archivo
    }
}

// Función para explorar un directorio dado y sus subdirectorios de manera recursiva
void explorar_directorio_recursivo(const char *ruta) {
    DIR *dir;
    struct dirent *entrada;
    if ((dir = opendir(ruta)) != NULL) {
        while ((entrada = readdir(dir)) != NULL) {
            // Ignorar las entradas "." y ".."
            if (strcmp(entrada->d_name, ".") != 0 && strcmp(entrada->d_name, "..") != 0) {
                char ruta_completa[1024];
                snprintf(ruta_completa, sizeof(ruta_completa), "%s/%s", ruta, entrada->d_name);
                mostrar_info_archivo(ruta_completa); // Mostrar información del archivo
                if (S_ISDIR(entrada->d_type)) {
                    pid_t pid = fork(); // Crear un nuevo proceso para subdirectorios
                    if (pid == -1) {
                        perror("fork"); // Manejo de errores si no se puede crear el proceso hijo
                    } else if (pid == 0) {
                        // Proceso hijo: explorar el subdirectorio
                        explorar_directorio_recursivo(ruta_completa);
                        exit(0); // Salir del proceso hijo
                    }
                }
            }
        }
        closedir(dir); // Cerrar el directorio actual
    } else {
        perror("opendir"); // Manejo de errores si no se puede abrir el directorio
    }
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Uso: %s <ruta_del_directorio>\n", argv[0]);
        return 1; // Mostrar mensaje de uso y salir con código de error si no se proporciona la ruta del directorio
    }
    
    char *ruta = argv[1]; // Obtener la ruta del directorio desde la línea de comandos
    explorar_directorio_recursivo(ruta); // Iniciar la exploración recursiva del directorio
    
    // Esperar a que todos los procesos hijos terminen
    while (wait(NULL) > 0);
    
    return 0; // Salir con éxito
}