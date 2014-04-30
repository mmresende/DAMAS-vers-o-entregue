
/***************************************************************************
*  $MCD Módulo de declaração: TAB  Tabuleiro 
*
*  Arquivo gerado:              TABULEIRO.h
*  Letras identificadoras:      TAB
*  
*  Projeto: damas
*  Arquivo: damas\fontes\tabuleiro.h
*
*
*  Autores: hs - Henrique Santiago
*	    mr - Marcelo Resende
*	    rh - Rafael Haeusler
*  

*  $HA Histórico de evolução: 
*     Versão  Autor    Data     Observações
*     1       hs/mr/rh   30/abril/2014    implementação parcial do jogo
*
*  $ED Descrição do módulo
*
*      A implementação deste módulo define todas as ações possíveis em
*      relação ao tabuleiro do jogo, como sua inicialização e
*      destruição. Também foi implementado a possíbilidade de se obter
*      uma determida peça do tabuleiro oque envolve uma conexão com o
*      módulo Peca onde sé definido a estrutura de peças. Aqui também
*      é definido o tipo de estrutura que o tabuleiro deve ter (8 por
*      8) e estruturado por 8 lista duplamente encadeadas de tamanho 8
*      cada.
*  
*  $CRE Créditos
*    Arndt von Staa. Programa AutoTest - Arcabouço para a automação de testes de 
*    programas redigidos em C;
*  
***************************************************************************/

#ifndef TABULEIRO_H
#define TABULEIRO_H

/***** Declarações exportadas pelo módulo *****/

/***********************************************************************
*
*  $TC Tipo de dados: TAB estrutura que referencia uma lista
*  duplamente encadeada que representa as linhas do tabuleiro
*
*  $ED Descrição do tipo 
*     Estipula a estrura do tabuleiro, definido por uma lista duplamente 
*     encadeada, onde cada lista (tamanho 8) é uma linha.
*
***********************************************************************/
typedef struct _Tabuleiro Tabuleiro;

/***********************************************************************
*
*  $TC Tipo de dados: TAB tipo referencia uma peça 
*  
*  $ED Descrição do tipo 
*      Este tipo caracteriza uma peça, contendo seu tipo (DAMA ou não)
*      e seu caracter representativo('x' ou 'o') diferenciando os times. 

***********************************************************************/

typedef struct _Peca Peca;

/***********************************************************************
*
*  $FC Função: TAB  &Criar tabuleiro
*
*  $ED Descrição da função
*     
*       Cria um novo tabuleiro (8x8) a partir da estrutura de lista,
*       sem qualquer valor, todas as posições possuem valor NULL.
*  
*  $EP Parâmetros
*       Não possui parâmetro de entrada 
*
*  $FV Valor retornado 
*
*        O valor retornado é um ponteiro para um tabuleiro 8 por 8, com 
*		 todos os seus valores iguais a NULL
*		 Se ocorreu algum erro, por exemplo falta de memória ou dados errados,
*		 a função retornará NULL.
*		 Não será dada mais informação quanto ao problema ocorrido.
*		
*
***********************************************************************/
Tabuleiro *TAB_criar();


/***********************************************************************
*
*  $FC Função: TAB  &Destruir tabuleiro
*
*  $ED Descrição da função
*     
*       Destroi um tabuleiro (8 listas duplamente encadeadas)
*       
*  $EP Parâmetros
*       Recebe como entrada um ponteiro para um tabuleiro do
*       tipo Tabuleiro definido neste próprio módulo.
*
*  $FV Valor retornado 
*
*        Não possui valor de retorno, simplesmente destroi (free()) o
*        tabuleiro.
*
*
***********************************************************************/
void TAB_destruir(Tabuleiro *tabuleiro);

/***********************************************************************
*
*  $FC Função: TAB  &Inicializar tabuleiro
*
*  $ED Descrição da função
*     
*       Se tabuleiro diferente de NULL, inicializa o tabuleiro de
*       damas, de acordo com as especificações, onde o 'x' preenche
*       todas as casas brancas do topo (duas primeiras linhas), e 'o'
*       preenche todas as casas brancas do rabo do tabuleiro (duas
*       ultimas linhas).
*       
*  $EP Parâmetros
*
*       Recebe como entrada um ponteiro para um tabuleiro do
*       tipo Tabuleiro definido neste próprio módulo, estando as
*       posiçoes do tabuleiro nulas ou não.
*
*  $FV Valor retornado 
*
*        Não retorna nenhum valor, simplesmente inicializa o tabuleiro
*        com as pecas nas posições adequadas para um jogo de damas.
*
*
*
***********************************************************************/
void TAB_inicializar(Tabuleiro *tabuleiro);

/***********************************************************************
*
*  $FC Função: TAB  &Imprimir tabuleiro
*
*  $ED Descrição da função
*     
*      Se tabuleiro diferente de NULL, está função imprime um
*      tabuleiro (8 listas duplamente encadeadas)
*       
*  $EP Parâmetros
*
*       Recebe como entrada um ponteiro para um tabuleiro do
*       tipo Tabuleiro definido neste próprio módulo, estando as
*       posiçoes do tabuleiro nulas ou não.
*
*  $FV Valor retornado 
*
*        Imprime na tela de execução o tabuleiro com suas coordenadas
*        de coluna e de linha.
*
*
*
***********************************************************************/
void TAB_imprimir(Tabuleiro *tabuleiro);

/***********************************************************************
*
*  $FC Função: TAB  &Obter peça do tabuleiro
*
*  $ED Descrição da função
*     
*      Se tabuleiro diferente de NULL e as linhas e colunas estiverem
*      dentro as dimensões do tabuleiro (8x8), a função obtem o valor
*      associado a tal coordenada no tabuleiro
*       
*  $EP Parâmetros
*
*       Recebe como entrada um ponteiro para um tabuleiro do tipo
*       Tabuleiro definido neste próprio módulo, a coordenada da linha
*       e a coordenada da coluna da onde se quer obter o valor
*
*  $FV Valor retornado 
*
*        Utilizando as funções de manipulação do módulo lista retorna
*        o valor associado as entradas de tabuleiro e coordenadas do
*        mesmo.
*		 Se a casa especificada não existir, retorna NULL. Isso pode ocorrer
*		 devido a linha ou coluna especificadas como parâmetros estarem vazias
*		 (criação inadequada de tabuleiro) ou não estarem de acordo com o tamanho
*		 do tabuleiro (exemplo: foi passado como parâmetro a linha 9)		
*
*
***********************************************************************/
Peca *TAB_obterCasa(Tabuleiro *tabuleiro, int linha, char coluna);


/***********************************************************************
*
*  $FC Função: TAB  &Setar Casa do tabuleiro
*
*  $ED Descrição da função
*
*      Se tabuleiro diferente de NULL e as linhas e colunas estiverem
*      dentro as dimensões do tabuleiro (8x8), a função coloca a peça  
*	   recebida como parâmetro na casa especificada.
*	   Caso contrário, faz nada.
*	   Também é usada para retirar uma peca de determinada casa, passando
*	   O parâmetro NULL.
*
*  $EP Parâmetros
*
*       Recebe como entrada um ponteiro para um tabuleiro do tipo
*       Tabuleiro definido neste próprio módulo, a coordenada da linha
*       e a coordenada da coluna onde se quer setar o valor e a peca.
*
*		O parametro peca pode ser NULL, caso em que a funcao destruirá a peca
*		localizada na casa epecificada. Se nao houver peca nessa casa, faz nada.
*
*
***********************************************************************/
void TAB_setarCasa(Tabuleiro *tabuleiro, int linha, char coluna, Peca *peca);

#endif
