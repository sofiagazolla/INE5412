#include <stdio.h>
#include <stdlib.h>

#include "escalonador_io.h"
#include "fila.h"

/*
 * escalonador
 * -----------
 * Implementa o algoritmo de escalonamento Round-Robin (RR).
 *
 * Parametros de entrada:
 *   processos    - vetor com os processos lidos do arquivo de entrada
 *                  (id, chegada, cpu ja preenchidos).
 *   numProcessos - quantidade de elementos em `processos`.
 *   quantum      - tamanho da fatia de tempo usada pelo RR.
 *
 * Parametros de saida (devem ser preenchidos pela funcao):
 *   gantt - a linha do tempo da simulacao, ja inicializada pelo main
 *           (veja `inicializarGantt`). Para registrar cada fatia de
 *           execucao ou ociosidade da CPU, basta chamar:
 *
 *               registrarFaixaGantt(gantt, id, inicio, fim);
 *
 *           na ordem em que as fatias ocorrerem (id = ID_IDLE quando a
 *           CPU ficar ociosa).
 *
 * Alem disso, para cada processo em `processos` esta funcao deve
 * calcular e preencher: termino, primeira_execucao, retorno, espera e 
 * resposta.
 */

static void escalonador(Processo *processos, int numProcessos, int quantum, Gantt *gantt) {

    int tempo_atual = 0;
    int concluidos = 0;
    int prox_id = 0;
    int restantes[numProcessos];
    int fila[2000];
    int inicio = 0;
    int fim = 0;

    for (int i = 0; i < numProcessos; i++) {
        restantes[i] = processos[i].cpu;
    }

    while(concluidos < numProcessos) {

        if (inicio == fim) { // fila vazia

            if (tempo_atual < processos[prox_id].chegada){
                registrarFaixaGantt(gantt, ID_IDLE, tempo_atual, processos[prox_id].chegada); 
                tempo_atual = processos[prox_id].chegada;
            }
            while(prox_id < numProcessos && processos[prox_id].chegada <= tempo_atual){
                fila[fim++] = prox_id++;
            }

        }

        int p = fila[inicio];
        inicio++;

        if (processos[p].primeira_execucao == -1){
            processos[p].primeira_execucao = tempo_atual;
        }

        int fatia = (restantes[p] < quantum) ? restantes[p] : quantum;

        registrarFaixaGantt(gantt, processos[p].id, tempo_atual, tempo_atual + fatia);
        restantes[p] -= fatia;
        tempo_atual += fatia;

        while(prox_id < numProcessos && processos[prox_id].chegada <= tempo_atual){
            fila[fim++] = prox_id++;
        }

        if (restantes[p] > 0) {
            fila[fim++] = p;
        } else {
            processos[p].termino = tempo_atual;
            processos[p].retorno = tempo_atual - processos[p].chegada;
            processos[p].espera = processos[p].retorno - processos[p].cpu;
            processos[p].resposta = processos[p].primeira_execucao - processos[p].chegada;
            concluidos++;
        }

    }




    /* TODO: Implemente aqui o algoritmo Round-Robin descrito acima. */

    /* Exemplo de uso (remova ao implementar o algoritmo de verdade):
     *
     *   registrarFaixaGantt(gantt, ID_IDLE, 0, 1);         // adiciona CPU ociosa no Gantt (iniciando no tempo 0 e finalizando no tempo 1)
     *   registrarFaixaGantt(gantt, processos[0].id, 1, 4); // adiciona a fatia de tempo usada pelo processo Px no Gantt (iniciando no tempo 1 e finalizando no tempo 4), onde x é o id do processo
     */
}

int main(int argc, char *argv[]) {
    if (argc != 3) {
        fprintf(stderr, "Uso correto: %s <arquivo de entrada> <arquivo de saida>\n", argv[0]);
        return 1;
    }

    const char *arquivoEntrada = argv[1];
    const char *arquivoSaida = argv[2];
    int quantum = 0;

    Processo *processos = NULL;
    int numProcessos = 0;

    lerArquivoEntrada(arquivoEntrada, &quantum, &processos, &numProcessos);

    if (quantum <= 0) {
        fprintf(stderr, "Erro: quantum invalido ou nao informado.\n");
        free(processos);
        exit(1);
    }

    Gantt gantt;
    inicializarGantt(&gantt);

    escalonador(processos, numProcessos, quantum, &gantt);

    double somaRetorno = 0.0;
    double somaEspera = 0.0;
    double somaResposta = 0.0;

    for (int i = 0; i < numProcessos; i++) {
        somaRetorno += processos[i].retorno;
        somaEspera += processos[i].espera;
        somaResposta += processos[i].resposta;
    }

    double mediaRetorno = numProcessos > 0 ? somaRetorno / numProcessos : 0.0;
    double mediaEspera = numProcessos > 0 ? somaEspera / numProcessos : 0.0;
    double mediaResposta = numProcessos > 0 ? somaResposta / numProcessos : 0.0;

    escreverSaida(arquivoSaida, &gantt, processos, numProcessos,
                  mediaRetorno, mediaEspera, mediaResposta);

    liberarGantt(&gantt);
    free(processos);

    return 0;
}
