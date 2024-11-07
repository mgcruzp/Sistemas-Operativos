#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>

#define FIFO_FILE "/tmp/fifo_twoway"

void reverse_string(char *);

int main() {
    int fd;
    char readbuf[80];
    const char end_str[] = "end";

    // Crear la FIFO si no existe
    mkfifo(FIFO_FILE, 0666);
    fd = open(FIFO_FILE, O_RDWR);
    if (fd == -1) {
        perror("Error al abrir FIFO");
        exit(EXIT_FAILURE);
    }

    // Bucle infinito para leer mensajes del cliente
    while (1) {
        int read_bytes = read(fd, readbuf, sizeof(readbuf));
        if (read_bytes <= 0) {
            continue; // Reintentar si no hay datos
        }

        readbuf[read_bytes] = '\0';
        printf("FIFOSERVER: Cadena recibida: \"%s\"\n", readbuf);

        // Si es "end", cerrar la conexión y terminar
        if (strcmp(readbuf, end_str) == 0) {
            close(fd);
            break;
        }

        // Invertir la cadena recibida
        reverse_string(readbuf);
        printf("FIFOSERVER: Cadena invertida enviada: \"%s\"\n", readbuf);
        write(fd, readbuf, strlen(readbuf));
        // Pausa para que el cliente tenga tiempo de leer la respuesta
        sleep(1);
    }

    return 0;
}

// Funcion que invierte la cadena recibida
void reverse_string(char *str) {
    int last = strlen(str) - 1;
    int first = 0;

    // Intercambiar caracteres desde los extremos hacia el centro
    while (first < last) {
        char temp = str[first];
        str[first] = str[last];
        str[last] = temp;
        first++;
        last--;
    }
}
