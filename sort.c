#include <stdio.h>
#include <limits.h>
#include "pvm3.h"
#include <time.h>

#define TRUE 1
#define FALSE 0
#define MaxVet 60000
#define NUM_PROC 5
#define SORT "quick"

int main() {
    int t, ind, ind2, info;
    int tid_sort[NUM_PROC], indices[NUM_PROC];
    int tot_subvet, pos_min;
    int vetor[MaxVet], vet_ordenado[MaxVet];
    unsigned long int val_min;
    struct timeval tv1, tv2; // Para capturar o tempo
    int dt1;                 // Tempo gasto para ordenação

    static char *hosts[] = { "xavante", "caiapo", "caiua", "xapacura" };

    tot_subvet = MaxVet / NUM_PROC;

    // Gera elementos do vetor aleatoriamente
    for (t = 0; t < MaxVet; t++)
        vetor[t] = rand();

    // Determinar tempo de ordenação
    gettimeofday(&tv1, (struct timezone *)0);

    // Cria os processos paralelos para ordenação dos subvetores
    info = TRUE;
    for (t = 0; t < NUM_PROC; t++) {
        if ((pvm_spawn(SORT, (char **)0, 1, hosts[t], 1, &tid_sort[t])) < 1)
            info = FALSE;
    }

    if (!info) {
        printf("ERRO: pvm_spawn não gerou todas as tasks...\n");
    } else {
        // Envia subvetores para os processos
        for (t = 0; t < NUM_PROC; t++) {
            pvm_initsend(PvmDataRaw);
            pvm_pkint(&vetor[tot_subvet * t], tot_subvet, 1);
            pvm_send(tid_sort[t], 1);
        }

        // Recebe os subvetores ordenados
        for (t = 0; t < NUM_PROC; t++) {
            pvm_recv(-1, 2);
            pvm_upkint(&vetor[tot_subvet * t], tot_subvet, 1);
            indices[t] = tot_subvet * t;
        }

        // Merge - Busca o menor elemento dos subvetores
        for (t = 0; t < MaxVet; t++) {
            val_min = ULONG_MAX;
            pos_min = -1;
            for (ind = 0; ind < NUM_PROC; ind++) {
                if ((indices[ind] < tot_subvet * (ind + 1)) &&
                    (vetor[indices[ind]] <= val_min)) {
                    val_min = vetor[indices[ind]];
                    pos_min = ind;
                }
            }

            if (pos_min > -1) {
                vet_ordenado[t] = val_min;
                indices[pos_min]++;
            } else {
                printf("Não conseguiu achar o menor...\n");
            }
        }

        gettimeofday(&tv2, (struct timezone *)0);

        // Calcula o tempo em microsegundos
        dt1 = (tv2.tv_sec - tv1.tv_sec) * 1000000 + tv2.tv_usec - tv1.tv_usec;

        printf("Tempo gasto (μs): %d\n", dt1);
    }

    // Envia sinal para matar os processos paralelos
    for (t = 0; t < NUM_PROC; t++)
        pvm_kill(tid_sort[t]);

    pvm_exit();
    return 0;
}
