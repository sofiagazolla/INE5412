#include <stdlib.h>

#include "fila.h"

void filaInicializar(FilaProntos *fila, int capacidade) {
    fila->itens = malloc((size_t)capacidade * sizeof(int));
    fila->capacidade = capacidade;
    fila->inicio = 0;
    fila->quantidade = 0;
}

void filaLiberar(FilaProntos *fila) {
    free(fila->itens);
    fila->itens = NULL;
}

int filaVazia(const FilaProntos *fila) {
    return fila->quantidade == 0;
}

void filaInserir(FilaProntos *fila, int indice) {
    int posicao = (fila->inicio + fila->quantidade) % fila->capacidade;
    fila->itens[posicao] = indice;
    fila->quantidade++;
}

int filaRemover(FilaProntos *fila) {
    int indice = fila->itens[fila->inicio];
    fila->inicio = (fila->inicio + 1) % fila->capacidade;
    fila->quantidade--;
    return indice;
}
