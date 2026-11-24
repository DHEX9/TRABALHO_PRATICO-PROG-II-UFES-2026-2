#include <stdio.h>
#include <stdlib.h>
#include "ouro.h"

// --- Ouro ---
struct Ouro{
    int qtd;
};

//Aloca ouro dinâmicamente.
Ouro *criaOuro(int qtd){
    Ouro *o = malloc(sizeof(Ouro));
    if(!o) exit(1);

    o->qtd = qtd;

    return o;
}

//Lê a quantidade de ouro, e retorna alocado.
Ouro *leOuro(){
    int qtd;
    scanf("%d", &qtd);

    return criaOuro(qtd);
}

void executaOuro(void *dado){
    return ((Ouro*)dado)->qtd;
}

void imprimeOuro(void *dado){
    printf("OURO %d", ((Ouro*)dado)->qtd);
}

//Desaloca ouro.
void desalocaOuro(void *dado){
    free(((Ouro*)dado));
}