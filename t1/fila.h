#ifndef FILA_H
#define FILA_H

/* ------------------------------------------------------------------ */
/* Fila de prontos FIFO, implementada como buffer circular sobre um   */
/* vetor de indices (0..numProcessos-1). A capacidade maxima e        */
/* numProcessos, ja que cada processo so pode estar uma vez na fila.  */
/* ------------------------------------------------------------------ */
typedef struct {
    int *itens;
    int capacidade;
    int inicio;
    int quantidade;
} FilaProntos;

/* Inicializa a fila com a capacidade informada (aloca o vetor). */
void filaInicializar(FilaProntos *fila, int capacidade);

/* Libera a memoria alocada pela fila. */
void filaLiberar(FilaProntos *fila);

/* Retorna 1 se a fila estiver vazia, 0 caso contrario. */
int filaVazia(const FilaProntos *fila);

/* Insere um indice de processo no final da fila. */
void filaInserir(FilaProntos *fila, int indice);

/* Remove e retorna o indice de processo no inicio da fila. */
int filaRemover(FilaProntos *fila);

#endif /* FILA_H */
