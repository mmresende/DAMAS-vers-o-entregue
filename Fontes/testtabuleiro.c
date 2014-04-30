
/***************************************************************************
*  $MCI Módulo de implementação: Testtabuleiro  Teste do módulo tabuleiro
*
*  Arquivo gerado:              Testtabuleiro.c
*  Letras identificadoras:      TTAB
*
*  Projeto: damas
*  Arquivo: damas\Fontes\testtabuleiro.c    
*
*  Autores: hs - Henrique Santiago
*	    mr - Marcelo Resende
*	    rh - Rafael Haeusler
*
*  $HA Histórico de evolução:
*     Versão  Autor   				 Data     Observações
*     1       Henrique Santiago   13/abr/2014 início desenvolvimento
*
*
***************************************************************************/

#include    <string.h>
#include    <stdio.h>
#include    <malloc.h>

#include    <tst_espc.h>
#include    <generico.h>
#include    <lerparm.h>

#include    "tabuleiro.h"
#include    "peca.h"

static const char RESET_TABULEIRO_CMD      [] = "=resetteste";
static const char CRIAR_TABULEIRO_CMD      [] = "=criartabuleiro";
static const char DESTRUIR_TABULEIRO_CMD   [] = "=destruirtabuleiro";
static const char INICIALIZAR_TABULEIRO_CMD[] = "=inicializartabuleiro";
static const char OBTER_CASA_CMD           [] = "=obtercasa";
static const char SETAR_CASA_CMD           [] = "=setarcasa";
static const char REMOVER_PECA_CMD         [] = "=removerpeca";

#define TRUE  1
#define FALSE 0

#define VAZIO     0
#define NAO_VAZIO 1

#define DIM_VT_TABULEIRO   10
#define DIM_VALOR     100

Tabuleiro *vtTabuleiros[DIM_VT_TABULEIRO];

/***** Protótipos das funçõees encapuladas no módulo *****/

static int ValidarInxTabuleiro(int inxLista, int Modo);

/*****  Código das funções exportadas pelo módulo  *****/


/***********************************************************************
*
*  $FC Função: TTAB &Testar tabuleiro
*
*  $ED Descrição da função
*     Podem ser criadas atÃ© 10 tabuleiros, identificados pelos í­ndices 0 a 9
*
*     Comandos disponíveis:
*
*     =resetteste
*           - anula o vetor de pecas. Provoca vazamento de memória
*     =criartabuleiro
*     =destruirtabuleiro         inxLista
*     =inicializartabuleiro      inxLista
*     =obterpeca                 inxLista  linha  coluna  ret
*	  =setarcasa				 inxlista  linha  coluna
*	  =removerpeca				 inxlista  linha  coluna
*
***********************************************************************/

TST_tpCondRet TST_EfetuarComando(char *ComandoTeste)
{
    int inxLista  = -1;
    int numLidos   = -1;
    int CondRetEsp = -1;
    void *retPtr;
    char StringDado[DIM_VALOR];
    int i;
    int linha = -1;
    int coluna = -1;
    Peca *peca;
	StringDado[0] = 0;
   

    /* Efetuar reset de teste de tabuleiro */              
    if(strcmp(ComandoTeste, RESET_TABULEIRO_CMD) == 0) {
        for(i = 0; i < DIM_VT_TABULEIRO; i++)
            vtTabuleiros[i] = NULL;

        return TST_CondRetOK;
    } /* fim ativa: Efetuar reset de teste de tabuleiro */  

	/* Testar Criar tabuleiro */                              
    else if(strcmp(ComandoTeste, CRIAR_TABULEIRO_CMD) == 0) {
        numLidos = LER_LerParametros("i", &inxLista);

        if((numLidos != 1) || (!ValidarInxTabuleiro(inxLista, VAZIO)))
            return TST_CondRetParm;

        vtTabuleiros[inxLista] = TAB_criar();
        return TST_CompararPonteiroNulo(1, vtTabuleiros[inxLista], "Erro em ponteiro do novo tabuleiro.");
    } /* fim ativa: Testar Criar tabuleiro */  

	/* Testar Destruir tabuleiro */                              
    else if(strcmp(ComandoTeste, DESTRUIR_TABULEIRO_CMD) == 0) {
        numLidos = LER_LerParametros("i", &inxLista);

        if((numLidos != 1) || (!ValidarInxTabuleiro(inxLista, NAO_VAZIO)))
            return TST_CondRetParm;

        TAB_destruir(vtTabuleiros[inxLista]);
        vtTabuleiros[inxLista] = NULL;

        return TST_CondRetOK;
    } /* fim ativa: Testar Destruir tabuleiro */                                     

	/* Testar Inicializar tabuleiro*/                                             
    else if(strcmp(ComandoTeste, INICIALIZAR_TABULEIRO_CMD) == 0) {
        numLidos = LER_LerParametros("i", &inxLista);

        if((numLidos != 1) || (!ValidarInxTabuleiro(inxLista, NAO_VAZIO)))
            return TST_CondRetParm;

        TAB_inicializar(vtTabuleiros[inxLista]);
        return TST_CondRetOK;
    } /* fim ativa: Testar Inicializar tabuleiro */                                    

	/* Testar Obter casa*/                                             
    else if(strcmp(ComandoTeste, OBTER_CASA_CMD) == 0) {
        numLidos = LER_LerParametros("iisi", &inxLista, &linha, StringDado, &CondRetEsp);

        if((numLidos != 4) || (!ValidarInxTabuleiro(inxLista, NAO_VAZIO)))
            return TST_CondRetParm;

        coluna = StringDado[0];
        retPtr = (void*)TAB_obterCasa(vtTabuleiros[inxLista], linha, coluna);
        return TST_CompararPonteiroNulo(CondRetEsp, retPtr, "Valor não deveria existir.");
    } /* fim ativa: Testar Obter casa */

    /* Testar Setar casa*/
    else if(strcmp(ComandoTeste, SETAR_CASA_CMD) == 0) {
        numLidos = LER_LerParametros("iis", &inxLista, &linha, StringDado);

        if((numLidos != 3) || (!ValidarInxTabuleiro(inxLista, NAO_VAZIO)))
            return TST_CondRetParm;

        coluna = StringDado[0];
        peca = PEC_criar(PecaNormal, 'r');
        TAB_setarCasa(vtTabuleiros[inxLista], linha, coluna, peca);
        return TST_CondRetOK;
    } /* fim ativa: Testar Setar casa */

	/* Testar Remover peca*/
    else if(strcmp(ComandoTeste, REMOVER_PECA_CMD) == 0) {
        numLidos = LER_LerParametros("iis", &inxLista, &linha, StringDado);

        if((numLidos != 3) || (!ValidarInxTabuleiro(inxLista, NAO_VAZIO)))
            return TST_CondRetParm;

        coluna = StringDado[0];
        TAB_setarCasa(vtTabuleiros[inxLista], linha, coluna, NULL);
        return TST_CondRetOK;
    } /* fim ativa: Testar Remover peca */

    return TST_CondRetNaoConhec;
} /* Fim função: TTAB &Testar tabuleiro */

/*****  Código das funções encapsuladas no módulo  *****/

/***********************************************************************
*
*  $FC Função: TTAB -Validar indice de tabuleiro
*
***********************************************************************/

int ValidarInxTabuleiro(int inxLista, int Modo)
{
    if((inxLista <  0) || (inxLista >= DIM_VT_TABULEIRO))
        return FALSE;

    if(Modo == VAZIO) {
        if(vtTabuleiros[inxLista] != 0)
            return FALSE;
    } else {
        if(vtTabuleiros[inxLista] == 0)
            return FALSE;
    }
    return TRUE;
} /* Fim função: TTAB -Validar indice de tabuleiro */

/********** Fim do módulo de implementação: Testtabuleiro  Teste do módulo tabuleiro **********/
