 <div align="center">

# UNIVERSIDADE FEDERAL DO ESPÍRITO SANTO

### DEPARTAMENTO DE INFORMÁTICA


## TRABALHO PRÁTICO

# 🎲 JOGO DA VOID

### Programação II — 2026/2

<br>

![Language](https://img.shields.io/badge/Linguagem-C-blue)
![Course](https://img.shields.io/badge/Disciplina-Programa%C3%A7%C3%A3o%20II-purple)
![Institution](https://img.shields.io/badge/UFES-2026%2F2-red)
![Status](https://img.shields.io/badge/Status-Em%20desenvolvimento-yellow)

</div>

---

> Um jogo de tabuleiro digital desenvolvido em C, no qual jogadores disputam uma corrida por uma trilha repleta de monstros, tesouros, equipamentos e desafios.

## Sobre o projeto

O **Jogo da Void** é um trabalho prático desenvolvido para a disciplina de Programação II da Universidade Federal do Espírito Santo (UFES).

O projeto consiste na implementação de um jogo de tabuleiro digital em que múltiplos jogadores percorrem um mapa linear, avançando por meio de lançamentos de dados e enfrentando diferentes desafios pelo caminho.

Durante a partida, os jogadores podem coletar ouro, derrotar monstros, adquirir equipamentos, avançar ou recuar no mapa e disputar posições ocupadas por adversários.

O objetivo é alcançar a casa final antes dos demais jogadores.

Mais do que desenvolver um jogo funcional, o projeto busca aplicar conceitos fundamentais da programação em C, especialmente **TADs opacos e genéricos, ponteiros, alocação dinâmica de memória e modularização**.

## Como funciona?

A partida acontece em um mapa linear composto por células, delimitado por uma posição inicial e uma posição final.

Cada jogador começa na posição `0`, com sua força inicial, `0 XP` e `0 ouro`.

Os jogadores realizam suas jogadas em ordem de cadastro. A cada turno, um dado determina quantas casas o jogador avança.

Ao alcançar uma célula, sua respectiva ação é executada.

### Tipos de células

| Tipo | Descrição |
|---|---|
| `VAZIA` | Não realiza nenhuma ação. |
| `OURO` | Concede uma quantidade de ouro ao jogador. |
| `MONSTRO` | Inicia um confronto baseado na força do jogador. |
| `ITEM` | Permite comprar automaticamente um equipamento, caso haja ouro suficiente. |
| `AVANCA` | Desloca o jogador algumas casas à frente. |
| `VOLTA` | Desloca o jogador algumas casas para trás. |

### Sistema de combate

Os confrontos contra monstros são determinados pela comparação entre a força do jogador e a força do monstro.

- Se a força do jogador for maior ou igual à do monstro, ele vence e recebe a experiência indicada.
- Caso contrário, perde o confronto e precisa recuar.

### Disputas territoriais

Cada célula comporta apenas um jogador, com exceção da posição inicial.

Quando um jogador tenta ocupar uma posição já ocupada, ocorre uma disputa:

1. Maior força vence.
2. Em caso de empate, vence quem possui mais XP.
3. Persistindo o empate, o jogador que já ocupava a célula permanece.

O perdedor recua até encontrar uma posição livre ou alcançar o início.

## Funcionalidades

- Cadastro dinâmico do mapa.
- Cadastro de jogadores.
- Sistema de movimentação por dados.
- Execução das ações das células.
- Sistema de combate contra monstros.
- Compra automática de equipamentos.
- Disputas territoriais entre jogadores.
- Sistema de recuo.
- Consulta do estado da partida.
- Ranking dos jogadores.
- Relatório geral da partida.
- Gerenciamento adequado da memória.

## Arquitetura e organização

O projeto utiliza modularização e TADs opacos para separar as responsabilidades e organizar a implementação.

Os principais módulos definidos para a primeira etapa são:

| Módulo | Responsabilidade |
|---|---|
| `jogador.h` | TAD responsável pela representação e manipulação dos jogadores. |
| `mapa.h` | TAD responsável pelo gerenciamento dinâmico das células do mapa. |
| `celula.h` | TAD genérico relacionado às células e suas ações. |
| `acao_monstro.h` | TAD específico para a implementação das ações do tipo monstro. |
| `main.c` | Ponto de entrada e integração das funcionalidades do jogo. |

### Ações genéricas

Um dos principais conceitos explorados no projeto é a implementação de ações genéricas em C.

As ações armazenam seus dados específicos por meio de um ponteiro genérico `void *` e utilizam ponteiros de função para definir três operações:

- **Executar:** aplica a ação sobre um jogador.
- **Imprimir:** apresenta as informações da ação.
- **Liberar:** desaloca os dados utilizados pela ação.

Essa abordagem permite que diferentes tipos de ações sejam manipulados por uma interface comum, sem que o módulo responsável por conduzir a partida precise conhecer seus detalhes internos.

## Conceitos de programação utilizados

- Linguagem C.
- Structs e tipos abstratos de dados.
- TADs opacos e encapsulamento.
- TADs genéricos.
- Ponteiros e ponteiros genéricos (`void *`).
- Ponteiros de função.
- Alocação dinâmica (`malloc`, `realloc` e `calloc`).
- Gerenciamento e liberação de memória (`free`).
- Manipulação de strings.
- Modularização com arquivos `.h` e `.c`.
- Estruturas de dados dinâmicas.
- Algoritmos de ordenação.
- Controle de fluxo e lógica de simulação.

## Entrada de dados

O programa recebe os comandos pela entrada padrão (`stdin`).

A entrada segue uma sequência definida:

1. Cadastro do mapa.
2. Cadastro dos jogadores.
3. Execução de rolagens e consultas.

### Exemplo de entrada

```text
INICIO MAPA
OURO 10
MONSTRO GOBLIN 3 10
AVANCA 2
VAZIA
ITEM ESPADA 10 2
FIM MAPA

J
ANA
VERMELHO
5

J
BRUNO
VERDE
5

ROLAGEM 4

E
ESTADO

E
RANKING

E
RELATORIO

F
```

### Comandos disponíveis

| Comando | Descrição |
|---|---|
| `INICIO MAPA` | Inicia o cadastro do mapa. |
| `FIM MAPA` | Finaliza o cadastro do mapa. |
| `J` | Inicia o cadastro de um jogador. |
| `ROLAGEM <n>` | Executa até `n` jogadas. |
| `E` + `ESTADO` | Exibe o estado atual da partida. |
| `E` + `RANKING` | Exibe o ranking dos jogadores. |
| `E` + `RELATORIO` | Exibe as estatísticas da partida. |
| `F` | Encerra o programa. |

O valor do dado deve ser obtido exclusivamente por meio da função `RolaDado()` disponibilizada no template da disciplina.

## Regras importantes de implementação

- O mapa e a quantidade de jogadores não possuem tamanho previamente conhecido, exigindo alocação dinâmica.
- Todos os TADs devem ser opacos e encapsulados.
- A memória alocada deve ser liberada corretamente.
- As ações das células são permanentes e podem ser executadas novamente por outros jogadores.
- O dado deve ser chamado exatamente uma vez por jogada.
- A ordem dos turnos deve ser rotativa.
- A partida termina quando um jogador alcança ou ultrapassa a posição final.
- A saída deve respeitar rigorosamente o formato especificado no enunciado.

## Testes e validação

A implementação deve ser validada utilizando os casos de teste disponibilizados pela disciplina e o script de correção automática.

Também é importante verificar:

- Correspondência exata entre a saída produzida e a saída esperada.
- Ausência de vazamentos de memória.
- Uso correto de alocação e desalocação dinâmica.
- Funcionamento adequado dos diferentes cenários de movimentação e combate.

## Referências

**Repositório oficial do template:**

[prog-II-ufes/2026-2-template-TP-etapa-1](https://github.com/prog-II-ufes/2026-2-template-TP-etapa-1)

**Instituição:** Universidade Federal do Espírito Santo (UFES)  
**Disciplina:** Programação II  
**Período:** 2026/2  
**Trabalho:** Jogo da Void — Etapa 1

---

*Projeto acadêmico desenvolvido individualmente para fins de aprendizado e aplicação dos conceitos de programação em C.*