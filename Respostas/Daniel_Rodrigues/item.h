#ifndef _ITEM_H_
#define _ITEM_H_

// --- Item ---
typedef struct Item Item;

//Aloca Item dinâmicamente.
Item *criaItem(int qtd);

//Lê a quantidade de Item, e retorna alocado.
Item *leItem();

void executaItem(void *dado);

void imprimeItem(void *dado);

//Desaloca Item.
void desalocaItem(void *dado);

#endif