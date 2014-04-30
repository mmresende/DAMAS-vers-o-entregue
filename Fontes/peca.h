/***************************************************************************
*  $MCI Módulo de implementação: PEC  Peca 
*
*  Arquivo gerado:              PECA.h
*  Letras identificadoras:      PEC
*
*  Projeto: damas
*  Arquivo: damas\Fontes\peca.h    
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
*      A Implementação deste módulo define as funções referentes a
*      manipulação das peças mas não em relação a manipulação das
*      peças no tabuleiro. Todas as funções aqui definidas são
*      restritas ao tipo de estrura aqui definido Peca, que foi
*      definido com umm campo de tipo de peça (normal ou dama) e um
*      caracter identificador associado que seria determinado em um
*      jogo normal pela cor das peças (branca ou preta).
*
*  $CRE Créditos
*    Arndt von Staa. Programa AutoTest - Arcabouço para a automação de testes de 
*    programas redigidos em C;
*  
***************************************************************************/

#ifndef PECA_H
#define PECA_H

/***** Declarações exportadas pelo módulo *****/

/***********************************************************************
*
*  $TC Tipo de dados: PEC tipo estipula a estrutura do tipo da peça
*  $ED Descrição de tipo
*
*      Este tipo define o tipo da peça se é PecaNormal (normal) ou
*      PecaDama (dama).
*
***********************************************************************/
typedef enum _PecaTipo {
    PecaNormal,
    PecaDama
} PecaTipo;

/***********************************************************************
*
*  $TC Tipo de dados: PEC tipo estipula a estrutura de peca
*  $ED Descrição de tipo
*
*      Este tipo define peça apartir de um caracter(char) que
*      identifica uma peça como 'x' ou 'o' e apartir do tipo PecaTipo,
*      que define se a peça é dama ou normal.
*
***********************************************************************/
typedef struct _Peca Peca;

/***********************************************************************
*
*  $FC Função: PEC  &Criar uma peça
*
*  $ED Descrição da função
*     
*       Cria uma nova peça apatir do seu tipo e seu caracter
*       associado, utilizando as próprias funções do módulo de setar
*       tipo e setar caracter.
*  
*  $EP Parâmetros
*
*        Recebe o tipo da peca estipulado em PecaTipo, e
*       recebe um caracter indicador 'x' ou 'o'.
*
*  $FV Valor retornado 
*
*        O valor retornado é um ponteiro do tipo Peca, que contém os
*        valores tipo e caracter recebidos como parâmetro.
*		 Retorna NULL se ocorrer falta de memória
*
***********************************************************************/
Peca *PEC_criar(PecaTipo tipo, char caracter);

/***********************************************************************
*
*  $FC Função: PEC  &Destruir uma determinada peça
*
*  $ED Descrição da função
*     
*       Destroi uma peça, ou seja elimina determinada peça do
*       tabuleiro, da lista que ela está localizada.
*  
*  $EP Parâmetros
*
*       Recebe um ponteiro de peca do tipo estruturado Peca.
*
*  $FV Valor retornado 
*
*        Não possui valor retornado, simplesmente libera (free()) a
*        peça da lista que ela está localizada
*
***********************************************************************/
void PEC_destruir(Peca *peca);

/***********************************************************************
*
*  $FC Função: PEC  &Imprimir uma determinada peça
*
*  $ED Descrição da função
*     
*       Imprimi o caracter associado a uma peça concatenado com pipe
*       para se encaixar na estrutura do tabuleiro.
*  
*  $EP Parâmetros
*
*       Recebe um ponteiro de peca do tipo estruturado Peca.
*
*  $FV Valor retornado 
*
*        Não possui valor retornado, simplesmente imprime (printf()) a
*        peça no console.
*
***********************************************************************/
void PEC_imprimir(Peca *peca);

/***********************************************************************
*
*  $FC Função: PEC  &Obter tipo de uma determinada  peça
*
*  $ED Descrição da função
*     
*       Obtem o tipo (PecaNormal ou PecaDama) de uma determinada peça
*       que possui um tipo de estrutura Peca.
*  
*  $EP Parâmetros
*
*       Recebe um ponteiro de peca do tipo estruturado Peca.
*
*  $FV Valor retornado 
*
*        Retorna o tipo da peça recebida como parâmetro na forma do
*        tipo de estrutura PecaTipo.
*
***********************************************************************/
PecaTipo PEC_obterTipo(Peca *peca);

/***********************************************************************
*
*  $FC Função: PEC  &Setar tipo de uma determinada  peça
*
*  $ED Descrição da função
*     
*       Seta o tipo (PecaNormal ou PecaDama) de uma determinada peça
*       que possui um tipo de estrutura Peca.
*  
*  $EP Parâmetros
*
*       Recebe um ponteiro de peca do tipo estruturado Peca e o tipo
*       da peça (PecaTipo) a ser mudado.
*
*  $FV Valor retornado 
*
*        Não retorna um valor, simplesmente muda o valor tipo da peca
*        recebida como parâmetro pelo valor de tipo recebido também
*        como parâmetro.
*
***********************************************************************/
void PEC_setarTipo(Peca *peca, PecaTipo tipo);

/***********************************************************************
*
*  $FC Função: PEC  &Obter caracter identificador de uma determinada  peça
*
*  $ED Descrição da função
*     
*       Obtem o caracter ('x/X' ou 'o/O') de uma determinada peça
*       que possui um tipo de estrutura Peca.
*  
*  $EP Parâmetros
*
*       Recebe um ponteiro de peca do tipo estruturado Peca.
*
*  $FV Valor retornado 
*
*        Retorna o caracter (char) identificador da peça recebida como
*        parâmetro.
*
***********************************************************************/
char PEC_obterCaracter(Peca *peca);

/***********************************************************************
*
*  $FC Função: PEC  &Setar caracter identificador de uma determinada  peça
*
*  $ED Descrição da função
*     
*       Seta o caracter de uma determinada peça que possui um tipo de
*       estrutura Peca.
*  
*  $EP Parâmetros
*
*       Recebe um ponteiro de peca do tipo estruturado Peca e o caracter identificador
*       da peça (char) a ser mudado.
*
*  $FV Valor retornado 
*
*        Não retorna um valor, simplesmente muda o valor do caracter da peca
*        recebida como parâmetro pelo valor de caracter também recebido como parâmetro.
*
***********************************************************************/
void PEC_setarCaracter(Peca *peca, char caracter);

#endif
