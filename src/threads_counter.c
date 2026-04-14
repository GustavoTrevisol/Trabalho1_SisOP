#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

// Definindo o alvo: 1 bilhão
#define TARGET 1000000000LL

long long counter = 0;
pthread_mutex_t lock;
int experiment_type = 1; // 1 para T1, 2 para T2

void* increment_work(void* arg) {
    long long iterations = *(long long*)arg;

    for (long long i = 0; i < iterations; i++) {
        if (experiment_type == 1) {
            // T1: Sem sincronização
            counter++;
        } else {
            // T2: Com Mutex
            pthread_mutex_lock(&lock);
            counter++;
            pthread_mutex_unlock(&lock);
        }
    }
    return NULL;
}

int main(int argc, char* argv[]) {
    if (argc < 3) {
        printf("Uso: %s <N_THREADS> <TIPO_EXPERIMENTO (1 ou 2)>\n", argv[0]);
        return 1;
    }

    int n_threads = atoi(argv[1]);
    experiment_type = atoi(argv[2]);

    pthread_t threads[n_threads];
    long long iterations_per_thread = TARGET / n_threads;

    // Inicializa o mutex se for o experimento T2
    if (experiment_type == 2) {
        pthread_mutex_init(&lock, NULL);
    }

    // Criação das threads
    for (int i = 0; i < n_threads; i++) {
        pthread_create(&threads[i], NULL, increment_work, &iterations_per_thread);
    }

    // Aguarda todas as threads terminarem
    for (int i = 0; i < n_threads; i++) {
        pthread_join(threads[i], NULL);
    }

    printf("Valor final do contador: %lld\n", counter);

    if (experiment_type == 2) {
        pthread_mutex_destroy(&lock);
    }

    return 0;
}