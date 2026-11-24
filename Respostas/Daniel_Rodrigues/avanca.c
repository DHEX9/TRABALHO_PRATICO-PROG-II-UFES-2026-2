#include <stdio.h>
#include <stdlib.h>
#include "avanca.h"

// --- Avanca ---
struct Avanca{
    int avanca;
};

//Aloca dinâmicamente um avanço.
Avanca *criaAvanco(int qtd){
    Avanca *v = malloc(sizeof(Avanca));
    if(!v) exit(1);

    v->avanca = qtd;

    return v;
}

//Lê um avaço e retorna alocado.
Avanca *leAvanco(){
    int qtd;

    scanf("%d", &qtd);

    return criaAvanco(qtd);
}

//Executa um avanço.
void executaAvanco(void *dado){
    return ((Avanca*)dado)->avanca;
}

void imprimeAvanco(void *dado){
    printf("AVANCA %d", ((Avanca*)dado)->avanca);
}

//Desaloca um avanço.
void desalocaAvanco(void *dado){
    free(((Avanca*)dado));
}