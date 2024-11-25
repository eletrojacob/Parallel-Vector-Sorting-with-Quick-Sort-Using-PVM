#include <stdio.h>
#include "pvm3.h"

#define MaxVet 60000
#define NUM_PROC 5

typedef int vetor[(MaxVet / NUM_PROC)];
typedef int indice;

void particao(vetor a, indice esq, indice dir, indice *i, indice *j) {
    int x, w;
    *i = esq;
    *j = dir;
    x = a[(*i + *j) / 2];

    do {
        while (a[*i] < x)
            (*i)++;
        while (a[*j] > x)
            (*j)--;
        if (*i <= *j) {
            w = a[*i];
            a[*i] = a[*j];
            a[*j] = w;
            (*i)++;
            (*j)--;
        }
    } while (*i <= *j);
}

void ordena(vetor a, indice esq, indice dir) {
    indice i, j;
    particao(a, esq, dir, &i, &j);
    if (esq < j)
        ordena(a, esq, j);
    if (i < dir)
        ordena(a, i, dir);
}

int main() {
    int tid_parent;
    int tot_subvet;
    vetor a;

    tid_parent = pvm_parent();
    tot_subvet = MaxVet / NUM_PROC;

    pvm_recv(tid_parent, 1);
    pvm_upkint(a, tot_subvet, 1);

    ordena(a, 0, tot_subvet - 1);

    pvm_initsend(PvmDataRaw);
    pvm_pkint(a, tot_subvet, 1);
    pvm_send(tid_parent, 2);

    pvm_exit();
    return 0;
}
