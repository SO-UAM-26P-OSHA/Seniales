#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <signal.h>

// Variable global para contar los segundos
int segundos_transcurridos = 0;

void manejador(int sig){
    // Incrementamos el contador cada vez que recibimos la señal SIGALRM
    segundos_transcurridos++;
    printf("Segundos transcurridos desde el inicio: %d\n", segundos_transcurridos);
}

int main() {
    if (signal(SIGALRM, manejador) == SIG_ERR) {
        printf("\nNo se puede cachar la senial: SIGALRM\n");
        exit(0);
    }

    // Guardamos el PID por si necesitas detenerlo desde otra terminal
    printf("Programa iniciado. Mi PID es: %d\n", getpid());

    while(1){
        alarm(1); // Configuramos la alarma para que suene cada 1 segundo
        pause();  // Esperamos la señal sin consumir CPU
    }
    
    return 1;
}
