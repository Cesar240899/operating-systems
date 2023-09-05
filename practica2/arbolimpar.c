#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

// Descripción: Arbol de procesos impares organizados linealmente.
// El proceso raíz debe mostrar el número total de procesos creados.

int main (int argc, char *argv[])
{
    int i, n, p, raiz;
    
    int nivel = atoi(argv[1]);
    
    p = 0;
    n = nivel - 1;

    //raiz = getpid(); // Obtenemos el ID de proceso del proceso raíz

    while (p < nivel / 2) { // Si N = 7, N/2 = 3, por lo que se ejecutará hasta que p >= 3
        if (fork()) { // Se crea un nuevo proceso hijo y el proceso padre entra en este bloque
            for (i = 0; i < n; i++) {
                if (fork()) // Se crean procesos hijos adicionales si i < n
                    break; // Los procesos hijos adicionales salen de este bucle
            }
            break; // El proceso padre principal sale de este bucle
        }
        p++; // Incrementa p para llevar el control del nivel actual
        n = n - 2; // Reducción de n para disminuir la creación de procesos en el siguiente ciclo
    }

    sleep(30); // Todos los procesos (incluidos los hijos) esperan 30 segundos
    //exit(0);   // Salir del proceso actual
    return 0;  // Esta línea no se ejecutará, ya que exit(0) finaliza el programa
}