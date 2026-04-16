#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <semaphore.h>
#include <fcntl.h>

#define TARGET 1000000000LL
#define SEM_NAME "/p2_semaphore"

int main(int argc, char* argv[]) {
    if (argc < 3) {
        printf("Uso: %s <N_PROCESSOS> <TIPO_EXPERIMENTO (1=P1, 2=P2)>\n", argv[0]);
        return 1;
    }

    int n_procs = atoi(argv[1]);
    int experiment_type = atoi(argv[2]);
    long long iterations_per_proc = TARGET / n_procs;

    // 1. Criar o segmento de Memória Compartilhada (shmget)
    // IPC_PRIVATE garante uma chave única para este programa
    // 0666 define permissões de leitura e escrita
    int shmid = shmget(IPC_PRIVATE, sizeof(long long), IPC_CREAT | 0666);
    if (shmid < 0) {
        perror("Erro ao criar memória compartilhada");
        exit(1);
    }

    // 2. Anexar o segmento ao nosso espaço de endereçamento (shmat)
    long long *counter = (long long *) shmat(shmid, NULL, 0);
    *counter = 0; // Inicializa o contador na memória compartilhada

    sem_t *sem = NULL;

    // 3. Preparar Semáforo se for Experimento P2
    if (experiment_type == 2) {
        // Remove qualquer semáforo com o mesmo nome que tenha ficado aberto antes
        sem_unlink(SEM_NAME); 
        // Cria um novo semáforo com valor inicial 1
        sem = sem_open(SEM_NAME, O_CREAT, 0666, 1);
        if (sem == SEM_FAILED) {
            perror("Erro ao abrir semáforo");
            exit(1);
        }
    }

    // 4. Criação dos Processos Filhos (fork)
    for (int i = 0; i < n_procs; i++) {
        pid_t pid = fork();

        if (pid < 0) {
            perror("Erro no fork");
            exit(1);
        }

        if (pid == 0) {
            // --- Código do Filho ---
            for (long long j = 0; j < iterations_per_proc; j++) {
                if (experiment_type == 2) {
                    sem_wait(sem);   // Down (espera o semáforo ficar 1)
                    (*counter)++;
                    sem_post(sem);   // Up (libera o semáforo)
                } else {
                    (*counter)++;    // P1: Sem sincronização (caos)
                }
            }
            // Filho desanexa a memória antes de sair
            shmdt(counter);
            exit(0); 
        }
    }

    // 5. Código do Pai: Esperar todos os filhos terminarem
    for (int i = 0; i < n_procs; i++) {
        wait(NULL);
    }

    printf("Valor final do contador: %lld\n", *counter);

    // 6. Limpeza Geral
    if (experiment_type == 2) {
        sem_close(sem);
        sem_unlink(SEM_NAME);
    }

    // Desanexa e remove o segmento de memória do sistema
    shmdt(counter);
    shmctl(shmid, IPC_RMID, NULL);

    return 0;
}