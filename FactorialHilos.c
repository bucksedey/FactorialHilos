/*Marco Antonio Flores Anzurez 4CV1
Programa que imprime el factorial de 5 números al mismo tiempo
utilizando multiples hilos.
*/
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define NUM_THREADS 5

// Estructura para pasar argumentos a la función del hilo
typedef struct {
    int num;
    int result;
} datos_hilo;

// Función para calcular el factorial de un número
int factorial(int n) {
    int result = 1;
    for (int i = 1; i <= n; i++) {
        result *= i;
    }
    return result;
}

// Función que ejecutará cada hilo
void *calcular_factorial(void *arg) {
    datos_hilo *data = (datos_hilo *) arg;
    data->result = factorial(data->num);
    return NULL;
}

int main() {
    pthread_t threads[NUM_THREADS]; // Identificadores de los hilos
    datos_hilo datos_hilo_array[NUM_THREADS]; // Datos para cada hilo

    // Inicializar los datos para cada hilo
    for (int i = 0; i < NUM_THREADS; i++) {
        datos_hilo_array[i].num = i + 1;
        datos_hilo_array[i].result = 0;
    }

    // Crear los hilos
    for (int i = 0; i < NUM_THREADS; i++) {
        pthread_create(&threads[i], NULL, calcular_factorial, &datos_hilo_array[i]);
    }

    // Esperar a que todos los hilos terminen
    for (int i = 0; i < NUM_THREADS; i++) {
        pthread_join(threads[i], NULL);
    }

    // Imprimir los resultados
    for (int i = 0; i < NUM_THREADS; i++) {
        printf("Factorial de %d es %d\n", datos_hilo_array[i].num, datos_hilo_array[i].result);
    }

    return 0;
}