/***************************************************************************
*  $MCI Módulo de implementação: PEC  Peca 
*
*  Arquivo gerado:              PECA.c
*  Letras identificadoras:      PEC
*
*  Projeto: damas
*  Arquivo: damas\Fontes\peca.c    
*
*  Autores: hs - Henrique Santiago
*	    mr - Marcelo Resende
*	    rh - Rafael Haeusler
*  
*  $HA Histórico de evolução: 
*     Versão  Autor    Data     Observações
*     1       hs/mr/rh   30/abril/2014    implementação parcial do jogo
*  
*  $CRE Créditos
*    Arndt von Staa. Programa AutoTest - Arcabouço para a automação de testes de 
*    programas redigidos em C;
*  
***************************************************************************/

#include <assert.h>
#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#define peca_OWN
#include "peca.h"
#undef peca_OWN   


/***********************************************************************
*
*  $TC Tipo de dados: PEC tipo estipula a estrutura de peca
*
*
***********************************************************************/
typedef struct _Peca {
    PecaTipo tipo;
    char caracter;
} Peca;


/*****  Código das funções exportadas pelo módulo  *****/

/***************************************************************************
*
*  Função: PEC  &Criar uma peça
*  ****/
Peca *PEC_criar(PecaTipo tipo, char caracter)
{
    Peca *peca = (Peca*)malloc(sizeof(Peca));
	if (peca==NULL)
		return NULL;
    PEC_setarTipo(peca, tipo);
    PEC_setarCaracter(peca, caracter);
    return peca;
}/* Fim função: PEC  &Criar uma peça */


/***************************************************************************
*
*  Função: PEC  &Destruir uma determinada peça
*  ****/
void PEC_destruir(Peca *peca)
{
	#ifdef _DEBUG
       assert(peca);
    #endif  
	free(peca);
}/* Fim função: PEC  &Destruir uma determinada peça */


/***************************************************************************
*
*  Função: PEC  &Imprimir uma determinada  peça
*  ****/
void PEC_imprimir(Peca *peca)
{
	#ifdef _DEBUG
       assert(peca);
	#endif  
    if(peca->tipo == PecaNormal)
        printf("%c|", peca->caracter);
    else
        printf("%c|", toupper(peca->caracter));
}/* Fim função: PEC  &Imprimir uma determinada peça */


/***************************************************************************
*
*  Função: PEC  &Obter tipo de uma determinada  peça
*  ****/
PecaTipo PEC_obterTipo(Peca *peca)
{
	#ifdef _DEBUG 
       assert(peca);
	#endif 
    return peca->tipo;
}/* Fim função: PEC  &Obter tipo de uma determinada peça */


/***************************************************************************
*
*  Função: PEC  &Setar tipo de uma determinada  peça
*  ****/
void PEC_setarTipo(Peca *peca, PecaTipo tipo)
{
	#ifdef _DEBUG 
       assert(peca);
       assert(tipo == PecaNormal || tipo == PecaDama);
	#endif
    peca->tipo = tipo;
}/* Fim função: PEC  &Setar tipo de uma determinada peça */


/***************************************************************************
*
*  Função: PEC  &Obter caracter identificador de uma determinada  peça
*  ****/
char PEC_obterCaracter(Peca *peca)
{
	#ifdef _DEBUG
       assert(peca);
    #endif                                    
	return peca->caracter;
}/* Fim função: PEC  &Obter caracter identificador de uma determinada peça */


/***************************************************************************
*
*  Função: PEC  &Setar caracter identificador de uma determinada  peça
*  ****/
void PEC_setarCaracter(Peca *peca, char caracter)
{
	#ifdef _DEBUG
       assert(peca);
       assert(islower(caracter));
	#endif    
    peca->caracter = caracter;
}/* Fim função: PEC  &Setar caracter identificador de uma determinada  peça */

/********** Fim do módulo de definição: PEC Peca **********/
