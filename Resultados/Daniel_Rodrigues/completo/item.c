#include <stdio.h>
#include <stdlib.h>
#include "jogador.h"
#include "item.h"

// --- Item ---
struct Item{
    char nome[21];
    int preco, bonus;
};

//Aloca item dinâmicamente.
Item *criaItem(char nome, int preco, int bonus){
    Item *i = malloc(sizeof(Item));
    if(!i) exit(1);

    strcpy(i->nome, nome);
    i->preco = preco;
    i->bonus = bonus;

    return i;
}

//Lê um item e retorna alocado.
Item *leItem(){
    char nome[21];
    int preco, bonus;

    scanf("%20s %d %d", nome, &preco, &bonus);

    return criaItem(nome, preco, bonus);
}

//Compra automática: só compra se tiver ouro suficiente.
void executaItem(void *dado, Jogador *j){
    Item *i = (Item*)dado;
    if(obtemOuroJogador(j) >= i->preco){
        adicionaOuroJogador(j, -i->preco);
        adicionaForcaJogador(j, i->bonus);
    }
}

//Imprime item.
void imprimeItem(void *dado){
    Item *i = (Item*)dado;

    printf("ITEM %s (P:%d F:+%d)", i->nome, i->preco, i->bonus);
}

//Desaloca um item.
void desalocaItem(void *dado){
    free(((Item*)dado));
}