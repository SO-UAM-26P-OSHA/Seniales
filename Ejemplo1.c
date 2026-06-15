#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#include <stdlib.h> // Necesario para poder usar exit()

// 1. Declaramos la variable global para mantener la cuenta
int contador = 0;

void manejador(int signo){
    // 2. Incrementamos el contador cada vez que entra la señal
    contador++;
    
    printf("\nPresionaste Ctrl-C. Intento %d de 5. Mi PID es: %d\n", contador, getpid());
    
    // 3. Evaluamos si ya llegamos al límite
    if(contador == 5){
        printf("Límite alcanzado. Terminando el programa automáticamente...\n");
        exit(0); // 4. Termina el programa de forma limpia
    }
}

int main(){
    if (signal(SIGINT, manejador) == SIG_ERR)
        printf("\nNo se puede cachar la senial: SIGINT\n");

    while(1)
        sleep(1);

    return 1;
}
