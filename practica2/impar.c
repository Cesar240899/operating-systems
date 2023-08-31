#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>

void createOddProcesses(int currentProcess, int maxProcesses) {
    if (currentProcess > maxProcesses) {
        return;
    }

    pid_t childPid = fork();

    if (childPid == 0) {  // Proceso hijo
        if (currentProcess % 2 != 0) {
            printf("Soy el proceso impar número %d, PID: %d\n", currentProcess, getpid());
        }
        exit(0);
    } else if (childPid > 0) {  // Proceso padre
        createOddProcesses(currentProcess + 1, maxProcesses);
    }
    sleep(30);
}

int main() {
    int maxProcesses = 10;  // Número total de procesos (ajusta según tu preferencia)
    printf("Soy el proceso raíz, PID: %d\n", getpid());
    createOddProcesses(1, maxProcesses);
    
    for (int i = 0; i < maxProcesses; i++) {
        wait(NULL);  // Espera a que todos los procesos hijos terminen
    }
    //sleep(30);
    return 0;
}