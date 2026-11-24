#ifndef _VOLTA_H_
#define _VOLTA_H_

// --- Volta ---
typedef struct Volta Volta;

//Aloca Volta dinâmicamente.
Volta *criaVolta(int qtd);

//Lê a quantidade de Volta, e retorna alocado.
Volta *leVolta();

void executaVolta(void *dado);

void imprimeVolta(void *dado);

//Desaloca Volta.
void desalocaVolta(void *dado);

#endif