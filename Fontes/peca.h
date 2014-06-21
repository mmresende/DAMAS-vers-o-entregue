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
*     2       hs/mr/rh   17/junho/2014    implementação completa do jogo
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
*    programas redigidos em C;módulo Lista Duplamente Encadeada
*  
***************************************************************************/

#ifndef PECA_H
#define PECA_H

/***** Declarações exportadas pelo módulo *****/

/***********************************************************************
*
*  $TC Tipo de dados: PEC Condições de retorno
*
*
*  $ED Descrição do tipo
*     Condições de retorno das funções da peca
*
***********************************************************************/

typedef enum _PEC_tpCondRet{
    PEC_CondRetOK, /* Concluiu corretamente */
    PEC_CondRetPecaVazia, /* A peca não existe */
    PEC_CondRetTipoInexistente, /* A peca não contém tipo adequado */
    PEC_CondRetCaracterInexistente, /* A peca não contém caracter adequado */
} PEC_tpCondRet;

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
    PecaDama,
    PecaErro
} PecaTipo;

/***********************************************************************
*
*  $TC Tipo de dados: PEC tipo estipula a estrutura de peca
*  $ED Descrição de tipo
*
*      Este tipo define peça a partir de um caracter(char) minusculo, que
*      identifica uma peça (como 'x' ou 'o') e a partir do tipo PecaTipo,
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
*       $P PecaTipo tipo - define PecaNormal e PecaDama
*       $P char caracter -  um caracter indicador da peca. Para implementção do 
*							jogo, deve ser 'x' (branca) ou 'o'(preta), embora possa
*							receber qualquer caracter.
*
*  $FV Valor retornado 
*
*        O valor retornado é um ponteiro do tipo Peca, que contém os
*        valores tipo e caracter recebidos como parâmetro.
*		 Caso o caracter recebido como parâmetro seja maiusculo, será convertido
*		 para uma letra minúscula e esta será armazenada em Peca.
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
*       $P Peca* peca - um ponteiro que representa uma peça do tipo
*                       estruturado Peca.
*
*  $FV Valor retornado 
*
*        retorna PEC_tpCondRetOK e se não houver peça(==NULL), retorna
*        PEC_tpCondRetPecaVazia
*
*
***********************************************************************/
PEC_tpCondRet PEC_destruir(Peca *peca);

/***********************************************************************
*
*  $FC Função: PEC  &Imprimir uma determinada peça
*
*  $ED Descrição da função
*     
*       Imprime o caracter associado a uma peça concatenado com pipe
*       para se encaixar na estrutura do tabuleiro.
*  
*  $EP Parâmetros
*
*       $P Peca* peca - um ponteiro que representa uma peça do tipo
*                       estruturado Peca.
*
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
*       $P Peca* peca - um ponteiro que representa uma peça do tipo
*                       estruturado Peca.
*
*
*  $FV Valor retornado 
*
*        Retorna o tipo da peça recebida como parâmetro, na forma do
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
*       $P Peca* peca - um ponteiro que representa uma peça do tipo
*                       estruturado Peca.
*       $P PecaTipo tipo - define PecaNormal e PecaDama
*
*  $FV Valor retornado 
*
*        retorna PEC_tpCondRetOK. Se não houver peça(==NULL), retorna
*        PEC_tpCondRetPecaVazia e se o tipo não for adequado retorna
*        PEC_tpCondRetTipoInexistente 
***********************************************************************/
PEC_tpCondRet PEC_setarTipo(Peca *peca, PecaTipo tipo);

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
*      $P Peca* peca - um ponteiro que representa uma peça do tipo
*                       estruturado Peca.
*
*  $FV Valor retornado 
*
*        Retorna o caracter (char) identificador da peça recebida como
*        parâmetro. Se a peca tiver sido corretamente criada, deve ser
*		 minusculo.
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
*      $P Peca* peca - um ponteiro que representa uma peça do tipo
*                       estruturado Peca.
*
*      $P char caracter -  um caracter indicador da peca.Para implementção do 
*						   jogo, deve ser 'x' (branca) ou 'o'(preta), embora possa
*						   receber qualquer caracter.
*  $FV Valor retornado 
*
*        retorna PEC_tpCondRetOK. Se não houver peça(==NULL), retorna
*        PEC_tpCondRetPecaVazia.
***********************************************************************/
PEC_tpCondRet PEC_setarCaracter(Peca *peca, char caracter);

#endif
