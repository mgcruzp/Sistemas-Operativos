/***********************************************************************
 * Autor: G. Cruz
 * Materia: Sistemas Operativos
 * Fecha: 17-10-24
 * Tema: Comunicacion entre procesos: Cliente-Servidor con FIFO
 ***********************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>

#define FIFO_FILE "/tmp/fifo_twoway"

int main() {
    int fd;
    char readbuf[80];
    const char end_str[] = "end"; // Cadena que indica el fin del proceso

    // Indicar al usuario que el cliente envia mensajes hasta que se ingrese "end"
    printf("FIFO_CLIENT: Enviar mensajes infinitamente, para terminar ingrese \"end\"\n");

    // Abrir la FIFO para lectura y escritura, creándola si no existe
    mkfifo(FIFO_FILE, 0666); // Crear FIFO si no existe
    fd = open(FIFO_FILE, O_RDWR);
    if (fd == -1) {
        perror("Error al abrir FIFO");
        exit(EXIT_FAILURE);
    }

    // Bucle infinito para enviar mensajes al servidor
    while (1) {
        printf("Ingrese una cadena: ");
        fgets(readbuf, sizeof(readbuf), stdin);
        readbuf[strcspn(readbuf, "\n")] = '\0'; // Eliminar el salto de línea

        // Si es "end", enviar y cerrar la conexión
        if (strcmp(readbuf, end_str) == 0) {
            write(fd, readbuf, strlen(readbuf));
            printf("FIFOCLIENT: Cadena enviada: \"%s\"\n", readbuf);
            close(fd);
            break;
        }

        // Enviar el mensaje al servidor
        write(fd, readbuf, strlen(readbuf));
        printf("FIFOCLIENT: Cadena enviada: \"%s\"\n", readbuf);

        // Leer la respuesta del servidor
        int read_bytes = read(fd, readbuf, sizeof(readbuf));
        if (read_bytes > 0) {
            readbuf[read_bytes] = '\0';
            printf("FIFOCLIENT: Cadena recibida: \"%s\"\n", readbuf);
        }
    }

    return 0;
}
