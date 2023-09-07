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
    struct stat file_stat;

    if (stat(path, &file_stat) == 0) {
    	
        printf("Nombre: %s\n", path);
        printf("Tamaño: %ld bytes\n", (long)file_stat.st_size);
        printf("Tipo: %s\n", S_ISDIR(file_stat.st_mode) ? "Directorio" : "Archivo");
        printf("Permisos: ");
        printf((file_stat.st_mode & S_IRUSR) ? "r" : "-");
        printf((file_stat.st_mode & S_IWUSR) ? "w" : "-");
        printf((file_stat.st_mode & S_IXUSR) ? "x" : "-");
        printf("\n");

        // Obtener y mostrar información de fechas
        //printf("Último acceso: %s", ctime(&file_stat.st_atime));
        //printf("Última modificación: %s", ctime(&file_stat.st_mtime));
        
        // Obtener la fecha y hora de la última modificación
        struct tm *mod_time = localtime(&file_stat.st_mtime);
        char mod_time_str[80];
        strftime(mod_time_str, sizeof(mod_time_str), "%Y-%m-%d %H:%M:%S", mod_time);
        printf("Última modificación: %s\n", mod_time_str);

        // Obtener la fecha y hora del último acceso
        struct tm *access_time = localtime(&file_stat.st_atime);
        char access_time_str[80];
        strftime(access_time_str, sizeof(access_time_str), "%Y-%m-%d %H:%M:%S", access_time);
        printf("Último acceso: %s\n", access_time_str);
        
        printf("****************\n");
    	printf("****************\n");
    } else {
        perror("stat");
    }
}

void explore_directory(const char *dir_path) {
    DIR *dir;
    struct dirent *entry;

    dir = opendir(dir_path);

    if (!dir) {
        perror("opendir");
        return;
    }

    while ((entry = readdir(dir))) {
        if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0) {
            continue; // Ignorar . y ..
        }

        char entry_path[256];
        snprintf(entry_path, sizeof(entry_path), "%s/%s", dir_path, entry->d_name);

        if (entry->d_type == DT_DIR) {
            // Es un directorio, crea un proceso hijo para explorar el directorio
            pid_t child_pid = fork();

            if (child_pid == 0) {
                // Proceso hijo
                printf("Soy el proceso PID...%d\",getpid());
                explore_directory(entry_path);
                exit(0);
            } else if (child_pid < 0) {
                perror("fork");
            } else {
                // Proceso padre
                wait(NULL);
            }
        } else {
            // Es un archivo, muestra la información
            print_file_info(entry_path);
        }
    }

    closedir(dir);
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Uso: %s <ruta_del_directorio>\n", argv[0]);
        return 1;
    }

    const char *dir_path = argv[1];
    explore_directory(dir_path);

    return 0;
}
