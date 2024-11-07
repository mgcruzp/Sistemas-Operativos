/***********************************************************************
 * Autor: G. Cruz
 * Materia: Sistemas Operativos
 * Fecha: 17-10-24
 * Tema: Comunicacion entre procesos: Cliente-Servidor con FIFO
 ***********************************************************************/

/* El siguiente codigo implementa un sistema de comunicacion entre procesos usando una FIFO .
El cliente envia mensajes al servidor, que responde invirtiendo los mensajes recibidos. 
El intercambio termina cuando el cliente envia la palabra "end". */

############################
# CLIENTE
#############
#define FIFO_FILE "/tmp/fifo_twoway"

// funcion principal
int main() {
  // declaracion de variables utilizadas
   int fd;                  
   int end_process;    
   int stringlen;           
   int read_bytes;          
   char readbuf[80];   
   char end_str[5];           
   
   // Indicar al usuario que el cliente envia mensajes hasta que se ingrese "end"
   printf("FIFO_CLIENT: Enviar mensajes infinitamente, para terminar ingrese \"end\"\n");
   
   // Abrir la FIFO para lectura y escritura, creandola si no existe
   fd = open(FIFO_FILE, O_CREAT|O_RDWR);
   strcpy(end_str, "end");    // Cadena que indica el fin del proceso
   
   // Bucle infinito para enviar mensajes al servidor
   while (1) {
      printf("Ingrese una cadena: ");
      fgets(readbuf, sizeof(readbuf), stdin);     
      stringlen = strlen(readbuf);
      readbuf[stringlen - 1] = '\0';           
      end_process = strcmp(readbuf, end_str);     
      
      // Si no es "end", enviar el mensaje al servidor
      if (end_process != 0) {
         write(fd, readbuf, strlen(readbuf));  
         printf("FIFOCLIENT: Cadena enviada: \"%s\", longitud: %d\n", readbuf, (int)strlen(readbuf));
         
         // Leer la respuesta del servidor
         read_bytes = read(fd, readbuf, sizeof(readbuf));
         readbuf[read_bytes] = '\0';
         printf("FIFOCLIENT: Cadena recibida: \"%s\", longitud: %d\n", readbuf, (int)strlen(readbuf));
      } else {
         // Si es "end", enviar y cerrar la conexion
         write(fd, readbuf, strlen(readbuf));
         printf("FIFOCLIENT: Cadena enviada: \"%s\", longitud: %d\n", readbuf, (int)strlen(readbuf));
         close(fd);
         break;
      }
   }
   return 0;
}

#######
# SERVIDOR

####
#define FIFO_FILE "/tmp/fifo_twoway"

// Funcion para invertir la cadena recibida
void reverse_string(char *);

int main() {
   int fd;
   char readbuf[80];      
   char end[10];        
   int to_end;               
   int read_bytes;             

   // Crear la FIFO si no existe
   mkfifo(FIFO_FILE, S_IFIFO|0640);
   strcpy(end, "end");       
   fd = open(FIFO_FILE, O_RDWR);  

   // Bucle infinito para leer mensajes del cliente
   while(1) {
      read_bytes = read(fd, readbuf, sizeof(readbuf));   
      readbuf[read_bytes] = '\0';                  
      printf("FIFOSERVER: Cadena recibida: \"%s\", longitud: %d\n", readbuf, (int)strlen(readbuf));
      to_end = strcmp(readbuf, end);                  
      
      if (to_end == 0) {
         // Si es "end", cerrar la conexion y terminar
         close(fd);
         break;
      }
      
      // Invertir la cadena recibida
      reverse_string(readbuf);
      printf("FIFOSERVER: Cadena invertida enviada: \"%s\", longitud: %d\n", readbuf, (int) strlen(readbuf));
      write(fd, readbuf, strlen(readbuf));              

      // Pausa para que el cliente tenga tiempo de leer la respuesta
      sleep(2);
   }
   return 0;
}

// Funcion que invierte la cadena recibida
void reverse_string(char *str) {
   int last, limit, first;
   char temp;

   last = strlen(str) - 1;    
   limit = last / 2;       
   first = 0;

   // Intercambiar caracteres desde los extremos hacia el centro
   while (first < last) {
      temp = str[first];
      str[first] = str[last];
      str[last] = temp;
      first++;
      last--;
   }
   return;
}
