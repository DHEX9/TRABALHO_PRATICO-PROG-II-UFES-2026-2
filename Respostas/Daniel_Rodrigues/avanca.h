#ifndef _AVANCA_H_
#define _AVANCA_H_

// --- Avanca ---
typedef struct Avanca Avanca;

//Aloca Avanca dinâmicamente.
Avanca *criaAvanco(int qtd);

//Lê a quantidade de Avanca, e retorna alocado.
Avanca *leAvanco();

void executaAvanco(void *dado);

void imprimeAvanco(void *dado);

//Desaloca Avanca.
void desalocaAvanco(void *dado);

#endif