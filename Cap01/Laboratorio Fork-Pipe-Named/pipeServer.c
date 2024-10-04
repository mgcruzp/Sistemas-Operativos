/***********************************************************************
 * Autor: G. Cruz
 * Materia: Sistemas Operativos
 * Fecha: 03-10-24
 * Tema: Comunicación Interprocesos mediante Pipes Nombrados (FIFO) 
         Todo este apartado funciona como un servidor el cual trabajar
         de la mano con el código del cliente.
 ***********************************************************************/

#include <stdio.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <cstdio>
#include <cstring>

#define FIFO_FILE "MYFIFO" 

int main() {
    int fd;
    char readbuf[80];
    char end[10];
    int to_end;
    int read_bytes;

    /* Create the FIFO if it does not exist */
    mknod(FIFO_FILE, S_IFIFO | 0640, 0);
    strcpy(end, "end");
    
    while (1) {
        fd = open(FIFO_FILE, O_RDONLY);
        read_bytes = read(fd, readbuf, sizeof(readbuf));
        readbuf[read_bytes] = '\0';
        printf("Received string: \"%s\" and length is %d\n", readbuf, (int)strlen(readbuf));
        to_end = strcmp(readbuf, end);
        
        if (to_end == 0) {
            close(fd);
            break;
        }
    }
}
