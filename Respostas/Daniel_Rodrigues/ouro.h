#ifndef _OURO_H_
#define _OURO_H_

// --- Ouro ---
typedef struct Ouro Ouro;

//Aloca ouro dinâmicamente.
Ouro *criaOuro(int qtd);

//Lê a quantidade de ouro, e retorna alocado.
Ouro *leOuro();

void executaOuro(void *dado);

void imprimeOuro(void *dado);

//Desaloca ouro.
void desalocaOuro(void *dado);

#endif