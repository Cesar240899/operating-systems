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


void explore_directory(const char *dir_path) {
    DIR *dir;                // Declara un puntero a una estructura DIR para representar el directorio.
    struct dirent *entry;    // Declara un puntero a una estructura dirent para representar una entrada de directorio.
    int cont=0;
    int suma=0;
    //int status=0;
    int status;
    int i=0;
    int raiz;
    
    raiz=getpid();

    // Abre el directorio especificado por la ruta dir_path y obtiene un puntero a él.
    dir = opendir(dir_path);

    // Verifica si la apertura del directorio fue exitosa. Si no, muestra un mensaje de error y retorna.
    if (!dir) {
        perror("opendir");   // Muestra un mensaje de error utilizando perror.
        return;
    }

    // Itera a través de todas las entradas en el directorio.
    while ((entry = readdir(dir))) { // leer secuencialmente las entradas de un directorio mientras haya entradas válidas en el directorio
        // Ignora las entradas especiales "." y "..".
        if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0) {
            continue;
        }
 
        // Construye la ruta completa al archivo o directorio utilizando dir_path y el nombre de la entrada.
        char entry_path[257];//Es el bufer // Aumenta el tamaño del búfer para acomodar 257 bytes (256 caracteres + el carácter nulo '\0'). 
        //La función snprintf asegura que no se produzcan desbordamientos de búfer al especificar el tamaño del búfer 
        snprintf(entry_path, sizeof(entry_path), "%s/%s", dir_path, entry->d_name); // cadena de ruta completa concatenando dir_path y entry->d_name

        if (entry->d_type == DT_DIR) { // si la entrada es de tipo directorio
            // Si la entrada es un directorio, crea un proceso hijo para explorar el directorio.
            pid_t child_pid = fork();

            if (child_pid == 0) {
                // Proceso hijo: muestra su PID y explora el directorio llamando a explore_directory recursivamente.
                printf("Soy el proceso PID: %d ENCONTRE UN DIRECTORIO %s \n", getpid(),entry_path);
                explore_directory(entry_path);
                exit(0); // Termina el proceso hijo.
            } else if (child_pid < 0) {
                perror("fork"); // En caso de error al crear el proceso hijo, muestra un mensaje de error.
            } else {
                // Proceso padre: espera a que el proceso hijo termine.
                //wait(NULL);
                //Proceso padre
		cont+=1;
            }
        } else {
            // Si la entrada es un archivo, muestra información sobre el archivo utilizando la función print_file_info.
            print_file_info(entry_path);
        }
    }
    if(cont>0){
	for(i=0; i<cont; i++){
	wait(&status);
	suma+=WEXITSTATUS(status);
	}
    }
    suma+=1;
    
    if(raiz==getpid()){
	printf("Procesos totales: %d\n", suma);
	exit(suma);	
    }
    //exit(total);
    //exit(1);

    // Cierra el directorio después de procesar todas las entradas.
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