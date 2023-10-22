#!/bin/bash
# Esta línea indica que el intérprete de comandos a utilizar es Bash.

# Compila el archivo Java llamado "Pipe.java".
javac Pipe.java

# Ejecuta el programa Java "Pipe" tres veces con diferentes argumentos en segundo plano.
# Los procesos se ejecutan en segundo plano debido al uso del '&' al final de cada línea.

# Ejecuta "java Pipe 0" en segundo plano.
java Pipe 0 &

# Ejecuta "java Pipe 1" en segundo plano.
java Pipe 1 &

# Ejecuta "java Pipe 2" en segundo plano.
java Pipe 2
