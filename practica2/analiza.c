#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <dirent.h>
#include <unistd.h>
#include <time.h> // Para trabajar con fechas y horas



void print_file_info(const char *path) {
    struct stat file_stat; // Declara una estructura para almacenar información sobre el archivo.

    // Utiliza la función stat para obtener información sobre el archivo especificado por la ruta (path).
    if (stat(path, &file_stat) == 0) { // Verifica si la función stat se ejecutó exitosamente.

        // Imprime el nombre del archivo.
        printf("Nombre: %s\n", path);

        // Imprime el tamaño del archivo en bytes.
        printf("Tamaño: %ld bytes\n", (long)file_stat.st_size);

        // Imprime los permisos del archivo (r, w, x).
        printf("Permisos: ");
        //verificar si el permiso de lectura para el propietario está establecido en el modo del archivo.
        printf((file_stat.st_mode & S_IRUSR) ? "r" : "-");  //permiso de escritura //
        printf((file_stat.st_mode & S_IWUSR) ? "w" : "-");  //permiso de lectura
        printf((file_stat.st_mode & S_IXUSR) ? "x" : "-");  //permiso de ejecucion
        printf("\n");

        // Obtiene y muestra la fecha y hora de la última modificación del archivo.
        struct tm *mod_time = localtime(&file_stat.st_mtime);
        char mod_time_str[80];
        strftime(mod_time_str, sizeof(mod_time_str), "%Y-%m-%d %H:%M:%S", mod_time);
        printf("Última modificación: %s\n", mod_time_str);

        // Obtiene y muestra la fecha y hora del último acceso al archivo.
        struct tm *access_time = localtime(&file_stat.st_atime);
        char access_time_str[80];
        strftime(access_time_str, sizeof(access_time_str), "%Y-%m-%d %H:%M:%S", access_time);
        printf("Último acceso: %s\n", access_time_str);
        
        printf("****************\n");
        printf("****************\n");
    } else {
        // Si la función stat no se ejecuta correctamente, muestra un mensaje de error.
        perror("stat");
    }
}

// Función para explorar directorios y subdirectorios sin recursión
void explore_directory(const char* rootPath) {
    struct dirent *entry;
    struct stat fileStat;
    DIR *dir;

    // Abre el directorio raíz
    dir = opendir(rootPath);
    if (dir == NULL) {
        perror("Error al abrir el directorio");
        return;
    }

    // Recorre el directorio raíz
    while ((entry = readdir(dir)) != NULL) {
        if (strcmp(entry->d_name, ".") != 0 && strcmp(entry->d_name, "..") != 0) {
            char fullPath[1024]; // Tamaño máximo del camino, ajusta según tus necesidades
            sprintf(fullPath, "%s/%s", rootPath, entry->d_name);

            if (stat(fullPath, &fileStat) < 0) {
                perror("Error al obtener información del archivo");
                continue;
            }

            if (S_ISDIR(fileStat.st_mode)) {
                // Es un directorio, abre el directorio interno
                DIR *subdir = opendir(fullPath);
                if (subdir == NULL) {
                    perror("Error al abrir el directorio interno");
                    continue;
                }

                // Recorre el directorio interno
                struct dirent *subentry;
                while ((subentry = readdir(subdir)) != NULL) {
                    if (strcmp(subentry->d_name, ".") != 0 && strcmp(subentry->d_name, "..") != 0) {
                        char subFullPath[1024]; // Tamaño máximo del camino, ajusta según tus necesidades
                        sprintf(subFullPath, "%s/%s", fullPath, subentry->d_name);

                        // Realiza acciones en el archivo encontrado
                        //printf("Archivo encontrado: %s\n", subFullPath);
                        print_file_info(subFullPath);
                    }
                }

                closedir(subdir);
            } else {
                // Es un archivo, puedes realizar acciones en él aquí
                //printf("Archivo encontrado: %s\n", fullPath);
                print_file_info(fullPath);
            }
        }
    }

    closedir(dir);
}


int main(int argc, char *argv[]) {
    // Verifica si el número de argumentos de línea de comandos no es igual a 2.
    if (argc != 2) {
        // Imprime un mensaje de error en la salida de error estándar (stderr)
        // que informa al usuario sobre el uso correcto del programa.
        fprintf(stderr, "Uso: %s <ruta_del_directorio>\n", argv[0]);
        // Retorna un código de error 1 para indicar un uso incorrecto del programa.
        return 1;
    }

    // Si el número de argumentos es correcto, asigna el segundo argumento (argv[1])
    // a una variable llamada dir_path que representa la ruta del directorio a explorar.
    const char *dir_path = argv[1];

    // Llama a una función llamada explore_directory y pasa dir_path como argumento.
    explore_directory(dir_path);
    
   
    // Retorna 0 para indicar una ejecución exitosa del programa.
    return 0;
}