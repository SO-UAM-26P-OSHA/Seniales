#include <sys/types.h>
#include <signal.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

// Variable global para que el hijo lleve la cuenta
int contador = 0;

void manejador_hijo(int senial){
    contador++;
    printf("Hijo: He recibido la senial SIGUSR1. Llevo: %d\n", contador);
    
    // Si llega a 10, el hijo termina limpiamente
    if(contador == 10){
        printf("Hijo: He recibido las 10 seniales. Terminando...\n");
        exit(0);
    }
}

int main(){
    int pid = fork();
    
    if(pid == 0){
        // CÓDIGO DEL HIJO
        signal(SIGUSR1, manejador_hijo);
        
        while(1) {
            pause(); // Se duerme esperando la señal
        }
    } else {
        // CÓDIGO DEL PADRE
        for(int i = 0; i < 10; i++){
            sleep(1); // Espera 1 segundo entre envíos para que se vea claro en terminal
            kill(pid, SIGUSR1);
        }
        
        printf("Padre: He terminado de enviar las 10 seniales. Mi trabajo aqui acabo.\n");
    }
    
    return 0;
}
