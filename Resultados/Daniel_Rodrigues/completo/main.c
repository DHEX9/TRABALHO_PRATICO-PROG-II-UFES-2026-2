#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "acao_monstro.h"
#include "celula.h"
#include "dado.h"
#include "jogador.h"
#include "mapa.h"

#define MAX_TAM_COMANDO 21
#define MAX_TAM_NOME_ITEM 21

// ---------------------
// --- --- Ações --- ---
// ---------------------

// --- Vazia ---
// A célula vazia não possui dados: a ação é NULL e nada é executado.
int executaVazia(void *dado, Jogador *j){
    return 0;
}

void imprimeVazia(void *dado){
    printf("VAZIA");
}

void desalocaVazia(void *dado){
}

// --- Ouro ---
typedef struct{
    int qtd;
}Ouro;

//Aloca ouro dinamicamente.
Ouro *criaOuro(int qtd){
    Ouro *o = malloc(sizeof(Ouro));
    if(!o) exit(1);

    o->qtd = qtd;

    return o;
}

//Lê a quantidade de ouro e retorna alocado.
Ouro *leOuro(){
    int qtd;
    scanf("%d", &qtd);

    return criaOuro(qtd);
}

//Concede o ouro ao jogador.
int executaOuro(void *dado, Jogador *j){
    adicionaOuroJogador(j, ((Ouro*)dado)->qtd);
    return 0;
}

void imprimeOuro(void *dado){
    printf("OURO %d", ((Ouro*)dado)->qtd);
}

void desalocaOuro(void *dado){
    free(dado);
}

// --- Item ---
typedef struct{
    char nome[MAX_TAM_NOME_ITEM];
    int preco, bonus;
}Item;

//Aloca item dinamicamente.
Item *criaItem(char *nome, int preco, int bonus){
    Item *i = malloc(sizeof(Item));
    if(!i) exit(1);

    strcpy(i->nome, nome);
    i->preco = preco;
    i->bonus = bonus;

    return i;
}

//Lê um item e retorna alocado.
Item *leItem(){
    char nome[MAX_TAM_NOME_ITEM];
    int preco, bonus;

    scanf(" %21s %d %d", nome, &preco, &bonus);

    return criaItem(nome, preco, bonus);
}

//Compra automática: só compra se tiver ouro suficiente.
int executaItem(void *dado, Jogador *j){
    Item *i = (Item*)dado;

    if(obtemOuroJogador(j) >= i->preco){
        adicionaOuroJogador(j, -i->preco);
        adicionaForcaJogador(j, i->bonus);
    }

    return 0;
}

void imprimeItem(void *dado){
    Item *i = (Item*)dado;

    printf("ITEM %s (P:%d F:+%d)", i->nome, i->preco, i->bonus);
}

void desalocaItem(void *dado){
    free(dado);
}

// --- Avanca ---
typedef struct{
    int qtd;
}Avanca;

//Aloca dinamicamente um avanço.
Avanca *criaAvanca(int qtd){
    Avanca *a = malloc(sizeof(Avanca));
    if(!a) exit(1);

    a->qtd = qtd;

    return a;
}

//Lê um avanço e retorna alocado.
Avanca *leAvanca(){
    int qtd;
    scanf("%d", &qtd);

    return criaAvanca(qtd);
}

//Devolve o deslocamento positivo: quem move o jogador é a partida.
int executaAvanca(void *dado, Jogador *j){
    return ((Avanca*)dado)->qtd;
}

void imprimeAvanca(void *dado){
    printf("AVANCA %d", ((Avanca*)dado)->qtd);
}

void desalocaAvanca(void *dado){
    free(dado);
}

// --- Volta ---
typedef struct{
    int qtd;
}Volta;

//Aloca dinamicamente uma volta.
Volta *criaVolta(int qtd){
    Volta *v = malloc(sizeof(Volta));
    if(!v) exit(1);

    v->qtd = qtd;

    return v;
}

//Lê uma volta e retorna alocada.
Volta *leVolta(){
    int qtd;
    scanf("%d", &qtd);

    return criaVolta(qtd);
}

//Devolve o deslocamento negativo: quem move o jogador é a partida.
int executaVolta(void *dado, Jogador *j){
    return -((Volta*)dado)->qtd;
}

void imprimeVolta(void *dado){
    printf("VOLTA %d", ((Volta*)dado)->qtd);
}

void desalocaVolta(void *dado){
    free(dado);
}

// -----------------------
// --- --- Partida --- ---
// -----------------------

typedef struct{
    Mapa *mapa;
    Jogador **jogadores;    //Jogadores na ordem de cadastro.
    int qtd;                //Quantidade de jogadores.
    int proximo;            //Índice do jogador que joga no próximo turno.
    Jogador *vencedor;      //NULL enquanto a partida está em andamento.
}Partida;

//Cria uma partida com o mapa informado e sem jogadores.
Partida *criaPartida(Mapa *mapa){
    Partida *p = malloc(sizeof(Partida));
    if(!p) exit(1);

    p->mapa = mapa;
    p->jogadores = NULL;
    p->qtd = 0;
    p->proximo = 0;
    p->vencedor = NULL;

    return p;
}

//Desaloca a partida, o mapa e os jogadores.
void desalocaPartida(Partida *p){
    for(int i = 0; i < p->qtd; i++){
        desalocaJogador(p->jogadores[i]);
    }

    free(p->jogadores);
    desalocaMapa(p->mapa);
    free(p);
}

//Lê as células do mapa até encontrar "FIM MAPA" (a palavra INICIO MAPA já foi lida).
void leMapa(Mapa *mapa){
    char cmd[MAX_TAM_COMANDO];

    while(scanf(" %20s", cmd) == 1){

        if(!strcmp(cmd, "FIM")){
            scanf(" %20s", cmd); //Consome o "MAPA".
            return;
        }

        else if(!strcmp(cmd, "VAZIA")){
            insereCelulaMapa(mapa, NULL, executaVazia, imprimeVazia, desalocaVazia);
        }

        else if(!strcmp(cmd, "OURO")){
            insereCelulaMapa(mapa, leOuro(), executaOuro, imprimeOuro, desalocaOuro);
        }

        else if(!strcmp(cmd, "MONSTRO")){
            insereCelulaMapa(mapa, leMonstro(), executaMonstro, imprimeMonstro, desalocaMonstro);
        }

        else if(!strcmp(cmd, "ITEM")){
            insereCelulaMapa(mapa, leItem(), executaItem, imprimeItem, desalocaItem);
        }

        else if(!strcmp(cmd, "AVANCA")){
            insereCelulaMapa(mapa, leAvanca(), executaAvanca, imprimeAvanca, desalocaAvanca);
        }

        else if(!strcmp(cmd, "VOLTA")){
            insereCelulaMapa(mapa, leVolta(), executaVolta, imprimeVolta, desalocaVolta);
        }
    }
}

//Retorna 1 se já existe um jogador com esse nome na partida.
int existeJogador(Partida *p, char *nome){
    for(int i = 0; i < p->qtd; i++){
        if(comparaNomeJogador(p->jogadores[i], nome)){
            return 1;
        }
    }

    return 0;
}

//Lê um jogador e o cadastra, exceto se já existir outro com o mesmo nome.
void cadastraJogador(Partida *p){
    Jogador *j = leJogador();

    if(existeJogador(p, obtemNomeJogador(j))){
        desalocaJogador(j);
        return;
    }

    p->jogadores = realloc(p->jogadores, (p->qtd + 1) * sizeof(Jogador*));
    if(!p->jogadores) exit(1);

    p->jogadores[p->qtd++] = j;
}

//Faz o jogador chegar na casa informada: resolve disputa, executa a ação (se pedido) e trata os deslocamentos.
void MoveParaCasa(Partida *p, Jogador *j, int destino, int executaAcao){
    Mapa *m = p->mapa;
    int fim = obtemPosicaoFimMapa(m);

    //Chegou (ou passou) do Fim: o jogador vence.
    if(destino >= fim){
        moveJogadorMapa(m, j, fim);
        p->vencedor = j;
        return;
    }

    //Voltou até o Início (ou antes): fica no Início, que não tem ação.
    if(destino <= 0){
        moveJogadorMapa(m, j, 0);
        return;
    }

    Jogador *ocupante = obtemOcupanteMapa(m, destino);

    //Casa ocupada por outro jogador: disputa territorial.
    if(ocupante != NULL && ocupante != j){

        //Quem chega sai da própria casa antes: ela conta como livre no recuo de quem perder.
        retiraJogadorMapa(m, j);

        if(venceDisputaJogador(j, ocupante)){
            incrementaDisputasVencidasJogador(j);
            recuaJogadorMapa(m, ocupante, destino);
        }
        else{
            incrementaDisputasVencidasJogador(ocupante);
            recuaJogadorMapa(m, j, destino);
            return;
        }
    }

    moveJogadorMapa(m, j, destino);

    //Deslocamentos (AVANCA/VOLTA) não disparam a ação da casa de destino.
    if(!executaAcao){
        return;
    }

    int resultado = executaAcaoCelula(obtemCelulaMapa(m, destino), j);

    if(resultado == RECUO_CELULA){
        recuaJogadorMapa(m, j, destino);
    }
    else if(resultado != 0){
        MoveParaCasa(p, j, destino + resultado, 0);
    }
}

//Realiza a jogada do próximo jogador da fila.
void turno(Partida *p){
    Jogador *j = p->jogadores[p->proximo];
    p->proximo = (p->proximo + 1) % p->qtd;

    int dado = RolaDado();
    incrementaJogadasJogador(j);

    MoveParaCasa(p, j, obtemPosicaoJogador(j) + dado, 1);
}

//Executa até n jogadas, parando se alguém vencer.
void rolagem(Partida *p, int n){
    for(int i = 0; i < n && p->qtd > 0 && p->vencedor == NULL; i++){
        turno(p);
    }
}

// -----------------------
// --- --- Consultas --- -
// -----------------------

//Imprime a lista de jogadores que estão na casa informada, no formato " <- A, B, C".
void imprimeOcupantes(Partida *p, int posicao){
    char *sep = " <- ";

    for(int i = 0; i < p->qtd; i++){
        if(obtemPosicaoJogador(p->jogadores[i]) == posicao){
            printf("%s%s", sep, obtemNomeJogador(p->jogadores[i]));
            sep = ", ";
        }
    }
}

//Imprime a situação da partida.
void imprimeSituacao(Partida *p){
    if(p->vencedor == NULL){
        printf("- Situacao: EM ANDAMENTO\n");
    }
    else{
        printf("- Situacao: VENCEDOR %s\n", obtemNomeJogador(p->vencedor));
    }
}

void imprimeEstado(Partida *p){
    printf("=========== ESTADO ============\n");

    printf("[INICIO]");
    imprimeOcupantes(p, 0);
    printf("\n");

    imprimeCelulasMapa(p->mapa);

    printf("[FIM]");
    imprimeOcupantes(p, obtemPosicaoFimMapa(p->mapa));
    printf("\n");

    printf("-------------------------------\n");

    for(int i = 0; i < p->qtd; i++){
        printEstadoJogador(p->jogadores[i]);
    }

    imprimeSituacao(p);
    printf("===============================\n");
}

void imprimeRanking(Partida *p){
    printf("=========== RANKING ===========\n");

    //Ordena cópias dos jogadores para não alterar a lista original.
    Jogador **copias = malloc(p->qtd * sizeof(Jogador*));
    if(!copias && p->qtd > 0) exit(1);

    for(int i = 0; i < p->qtd; i++){
        copias[i] = copiaJogador(p->jogadores[i]);
    }

    qsort(copias, p->qtd, sizeof(Jogador*), comparaOrdJogador);

    for(int i = 0; i < p->qtd; i++){
        printRankingJogador(copias[i], i + 1);
        desalocaJogador(copias[i]);
    }

    free(copias);

    printf("===============================\n");
}

void imprimeRelatorio(Partida *p){
    int jogadas = 0, disputas = 0, monstros = 0;

    for(int i = 0; i < p->qtd; i++){
        jogadas += obtemJogadasJogador(p->jogadores[i]);
        disputas += obtemDisputasVencidasJogador(p->jogadores[i]);
        monstros += obtemMonstrosDerrotadosJogador(p->jogadores[i]);
    }

    printf("========= RELATORIO ===========\n");
    printf("- Celulas do mapa: %d\n", obtemQtdCelulasMapa(p->mapa));
    printf("- Jogadores: %d\n", p->qtd);
    printf("- Jogadas totais: %d\n", jogadas);
    printf("- Disputas: %d\n", disputas);
    printf("- Monstros derrotados: %d\n", monstros);
    imprimeSituacao(p);
    printf("-------------------------------\n");

    for(int i = 0; i < p->qtd; i++){
        printRelatorioJogador(p->jogadores[i]);
    }

    printf("===============================\n");
}

//Lê o tipo de consulta e a executa.
void consulta(Partida *p){
    char tipo[MAX_TAM_COMANDO];

    if(scanf(" %20s", tipo) != 1){
        return;
    }

    if(!strcmp(tipo, "ESTADO")){
        imprimeEstado(p);
    }
    else if(!strcmp(tipo, "RANKING")){
        imprimeRanking(p);
    }
    else if(!strcmp(tipo, "RELATORIO")){
        imprimeRelatorio(p);
    }
}

//Lê e executa os comandos da entrada padrão até o "F" (ou fim da entrada).
void eventLoop(Partida *p){
    char cmd[MAX_TAM_COMANDO];

    while(scanf(" %20s", cmd) == 1){

        if(!strcmp(cmd, "J")){
            cadastraJogador(p);
        }

        else if(!strcmp(cmd, "ROLAGEM")){
            int n;
            if(scanf("%d", &n) == 1){
                rolagem(p, n);
            }
        }

        else if(!strcmp(cmd, "E")){
            consulta(p);
        }

        else if(!strcmp(cmd, "F")){
            return;
        }
    }
}

int main(){
    char cmd[MAX_TAM_COMANDO];
    Mapa *mapa = criaMapa();

    //Lê o "INICIO MAPA" e as células.
    if(scanf(" %20s", cmd) == 1 && !strcmp(cmd, "INICIO")){
        scanf(" %20s", cmd); //Consome o "MAPA".
        leMapa(mapa);
    }

    Partida *partida = criaPartida(mapa);

    eventLoop(partida);

    desalocaPartida(partida);

    return 0;
}
