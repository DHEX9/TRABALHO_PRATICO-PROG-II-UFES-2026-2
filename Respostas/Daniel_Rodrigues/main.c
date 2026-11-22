#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "acao_monstro.h"
#include "jogador.h"
#include "mapa.h"

// ---------------------
// --- --- Ações --- ---
// ---------------------

// --- Ouro ---
typedef struct{
    int qtd;
}Ouro;

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

void executaOuro(Jogador *j, void *dado){
    adicionaOuroJogador(j, ((Ouro*)dado)->qtd);
}

void imprimeOuro(void *dado){
    printf("OURO %d", ((Ouro*)dado)->qtd);
}

//Desaloca ouro.
void desalocaOuro(void *dado){
    free(((Ouro*)dado));
}

// --- Item ---
typedef struct{
    char nome[21];
    int preco, bonus;
}Item;

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

// --- Avanca ---
typedef struct{
    int avanca;
}Avanca;

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
void executaAvanco(void *dado, Mapa *mapa, Jogador *j){
    Avanca *a = (Avanca*)dado;
    moveJogadorMapa(mapa, j, a->avanca);
}

void imprimeAvanco(void *dado){
    printf("AVANCA %d", ((Avanca*)dado)->avanca);
}

//Desaloca um avanço.
void desalocaAvanco(void *dado){
    free(((Avanca*)dado));
}

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

int executaVolta(void *dado, Mapa *mapa, Jogador *j){
    
    Volta *v = (Volta*)dado;
    recuaJogadorMapa(mapa, j, v->volta);

}

void imprimeVolta(void *dado){
    printf("VOLTA %d", ((Volta*)dado)->volta);
}

//Desaloca volta.
void desalocaVolta(void *dado){
    free(((Volta*)dado));
}

// -----------------------
// --- --- Jogador --- ---
// -----------------------

//Struct Lista de jogadores.
typedef struct{
    Jogador **ListaJogadores;
    int qtd;
}ListaJogadores;

//Cadastra um novo jogador, e adiciona a uma lista de jogadores.
ListaJogadores **cadastraJogadores(ListaJogadores **listaJogadores){
    listaJogadores = realloc(listaJogadores, ((*listaJogadores)->qtd + 1) * sizeof(ListaJogadores*));
    if(!listaJogadores) exit(1);

    listaJogadores[(*listaJogadores)->qtd++] = leJogador();

    return listaJogadores;
}

//Lê as casas do mapa.
Mapa *leMapa(Mapa *mapa){
    char cmd[21];

    while(scanf(" %20s", cmd) == 1 || !strcmp(cmd, "FIM MAPA")){

        if(!strcmp(cmd, "VAZIO")){
            insereCelulaMapa(mapa, NULL, NULL, printf("VAZIA"), NULL);
        }

        else if(!strcmp(cmd, "OURO")){
            insereCelulaMapa(mapa, leOuro(), executaOuro, imprimeOuro, desalocaOuro);
        }

        else if(!strcmp(cmd, "MONSTRO")){
            insereCelulaMapa(mapa, leMonstro(), executaMonstro, imprimeMonstro, desalocaMonstro);
        }

        else if(!strcmp(cmd, "AVANCO")){
            insereCelulaMapa(mapa, leAvanco(), executaAvanco, imprimeAvanco, desalocaAvanco);
        }

        else if(!strcmp(cmd, "VOLTA")){
            insereCelulaMapa(mapa, leVolta(), executaVolta, imprimeVolta, desalocaVolta);
        }
    }
}




int turno(){

}

void eventLoop(Mapa *mapa, ListaJogadores listaJogadores){
    
}

int main(){

    Mapa *mapa = criaMapa();
    ListaJogadores listaJogadores = {NULL, 0};

    eventLoop(mapa, listaJogadores);
    return 0;
}