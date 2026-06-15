#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#include <stdlib.h>

// Definimos los estados posibles
#define ROJO 0
#define VERDE 1
#define AMARILLO 2

// Variable global para mantener el estado actual (iniciamos en ROJO)
int estado_actual = ROJO;

// Un único manejador para todas las señales de nuestro semáforo
void manejador_semaforo(int senial) {
    if (senial == SIGUSR1) {
        estado_actual = VERDE; // Cambia a VERDE al recibir SIGUSR1
    } else if (senial == SIGUSR2) {
        estado_actual = AMARILLO; // Cambia a AMARILLO al recibir SIGUSR2
    } else if (senial == SIGINT) {
        estado_actual = ROJO; // Cambia a ROJO al recibir SIGINT
    }
}

int main() {
    // 1. Configuramos el manejador para las tres señales
    if (signal(SIGUSR1, manejador_semaforo) == SIG_ERR) {
        printf("Error al atrapar SIGUSR1\n");
    }
    if (signal(SIGUSR2, manejador_semaforo) == SIG_ERR) {
        printf("Error al atrapar SIGUSR2\n");
    }
    if (signal(SIGINT, manejador_semaforo) == SIG_ERR) {
        printf("Error al atrapar SIGINT\n");
    }

    // 2. Imprimimos el PID y las instrucciones de uso
    printf("=== SEMÁFORO INICIADO ===\n");
    printf("PID del proceso: %d\n\n", getpid());
    printf("Desde otra terminal, envía las señales para cambiar el color:\n");
    printf(" -> Para VERDE:    kill -SIGUSR1 %d\n", getpid());
    printf(" -> Para AMARILLO: kill -SIGUSR2 %d\n", getpid());
    printf(" -> Para ROJO:     Presiona Ctrl-C aquí mismo (o kill -SIGINT %d)\n", getpid());
    printf(" -> Para SALIR:    Presiona Ctrl-\\ (SIGQUIT)\n");
    printf("=========================\n\n");

    // 3. Bucle infinito que muestra continuamente el estado actual
    while(1) {
        switch(estado_actual) {
            case ROJO:
                printf("[ ROJO]     - Alto\n");
                break;
            case VERDE:
                printf("[ VERDE]    - Siga\n");
                break;
            case AMARILLO:
                printf("[ AMARILLO] - Precaución\n");
                break;
        }
        sleep(2); // Pausa de 2 segundos para no saturar la terminal
    }

    return 0;
}
