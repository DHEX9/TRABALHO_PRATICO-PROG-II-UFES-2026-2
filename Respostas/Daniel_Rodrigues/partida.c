#include <stdio.h>
#include <stdlib.h>
#include "acao_monstro.h"
#include "ouro.h"
#include "item.h"
#include "avanca.h"
#include "volta.h"
#include "jogador.h"
#include "mapa.h"
#include "dado.h"
#include "partida.h"

struct Partida{
    Mapa *mapa;
    Jogador **jogadores;
    int qtdJogadores;
    int proximo;
    Jogador *vencedor;
};

Partida *criaPartida(){
    Partida *p = malloc(sizeof(Partida));
    if(!p) exit(1);

    p->mapa = criaMapa();
    p->jogadores = NULL;
    p->proximo = NULL;
    p->vencedor = NULL;
    p->qtdJogadores = 0;
    
    return p;
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

        else if(!strcmp(cmd, "ITEM")){
            insereCelulaMapa(mapa, leItem(), executaItem, imprimeItem, desalocaItem);
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
void moveJogadorCasa(Partida *p, int n){

}

void rolagem(Partida *p, int n){
    
    while(n--){
        if(p->vencedor != NULL) break;
        turno(p);
    }

}

void turno(Partida *p){
    Jogador*j = p->jogadores[p->proximo];
    p->proximo = (p->proximo + 1) % p->qtdJogadores;

    incrementaJogadasJogador(j);

    int n = RolaDado();

    moveJogadorCasa(p, n);
}

void eventLoop(){
    
}


//Cadastra um novo jogador, e adiciona a uma lista de jogadores.
Jogador **cadastraJogadores(Partida *p){
    p->jogadores = realloc(p->jogadores, (p->qtdJogadores + 1) * sizeof(Jogador*));
    if(!p->jogadores) exit(1);

    p->jogadores[p->qtdJogadores++] = leJogador();

    return p->jogadores;
}

void desalocaPartida(Partida *p){
    desalocaMapa(p->mapa);
    free(p);
}