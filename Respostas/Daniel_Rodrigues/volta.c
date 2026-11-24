#include <stdio.h>
#include <stdlib.h>
#include "volta.h"

// --- Volta ---
typedef struct{
    int volta;
}Volta;

//Aloca uma volta dinâmicamente.
Volta *criaVolta(int qtd){
    Volta *v = malloc(sizeof(Volta));
    if(!v) exit(1);

    v->volta = qtd;

    return v;
}

//Lê uma volta e aloca dinâmicamente.
Volta *leVolta(){
    int qtd;

    scanf("%d", &qtd);

    return criaVolta(qtd);
}

int executaVolta(void *dado){
    return ((Volta*)dado)->volta;
}

void imprimeVolta(void *dado){
    printf("VOLTA %d", ((Volta*)dado)->volta);
}

//Desaloca volta.
void desalocaVolta(void *dado){
    free(((Volta*)dado));
}