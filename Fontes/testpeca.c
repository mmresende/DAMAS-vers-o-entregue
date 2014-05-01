
/***************************************************************************
*  $MCI Módulo de implementação: Testpeca  Teste do modulo peca
*
*  Arquivo gerado:              testpeca.c
*  Letras identificadoras:      TPEC
*
*  Projeto: damas
*  Arquivo: damas\Fontes\testpeca.c    
*
*  Autores: hs - Henrique Santiago
*	    mr - Marcelo Resende
*	    rh - Rafael Haeusler
*
*
*  $HA Histórico de evolução:
*     Versão  Autor    				Data     Observações
*     1       Henrique Santiago   13/abr/2014 início desenvolvimento
*
***************************************************************************/

#include    <string.h>
#include    <stdio.h>
#include    <malloc.h>

#include    <tst_espc.h>
#include    <generico.h>
#include    <lerparm.h>

#include    "peca.h"

static const char RESET_PECA_CMD      [] = "=resetteste";
static const char CRIAR_PECA_CMD      [] = "=criarpeca";
static const char DESTRUIR_PECA_CMD   [] = "=destruirpeca";
static const char OBTER_TIPO_CMD      [] = "=obtertipo";
static const char SETAR_TIPO_CMD      [] = "=setartipo";
static const char OBTER_CARACTER_CMD  [] = "=obtercaracter";
static const char SETAR_CARACTER_CMD  [] = "=setarcaracter";

#define TRUE  1
#define FALSE 0

#define VAZIO     0
#define NAO_VAZIO 1

#define DIM_VT_PECA   10
#define DIM_VALOR     100

Peca *vtPecas[DIM_VT_PECA];

/***** Protótipos das funções encapuladas no módulo *****/

static int ValidarInxPeca(int inxLista, int Modo);

/*****  Código das funções exportadas pelo módulo  *****/


/***********************************************************************
*
*  $FC Função: TPEC &Testar peca
*
*  $ED Descrição da função
*     Podem ser criadas até 10 pecas, identificadas pelos índices 0 a 9
*
*     Comandos disponíveis:
*
*     =resetteste
*           - anula o vetor de pecas. Provoca vazamento de memória
*     =criarpeca                   inxLista  int     string
*     =destruirpeca                inxLista
*     =obtertipo                   inxLista  int
*     =setartipo                   inxLista  int
*     =obtercaracter               inxLista  string
*     =setarcaracter               inxLista  string
*
***********************************************************************/

TST_tpCondRet TST_EfetuarComando(char *ComandoTeste)
{
    int inxLista  = -1;
    int numLidos   = -1;
    int CondRetEsp = -1;
    char StringDado[DIM_VALOR];
    int i;
    int tipo = -1;
    int caracter = -1;
    StringDado[0] = 0;

	/* Efetuar reset de teste de peca */               
    if(strcmp(ComandoTeste, RESET_PECA_CMD) == 0) {
        for(i = 0; i < DIM_VT_PECA; i++)
            vtPecas[i] = NULL;

        return TST_CondRetOK;
    } /* fim ativa: Efetuar reset de teste de lista */  

	/* Testar Criar peca */                              
    else if(strcmp(ComandoTeste, CRIAR_PECA_CMD) == 0) {
        numLidos = LER_LerParametros("iis", &inxLista, &tipo, StringDado);

        if((numLidos != 3) || (! ValidarInxPeca(inxLista, VAZIO)))
            return TST_CondRetParm;

        vtPecas[inxLista] = PEC_criar(tipo, StringDado[0]);
        return TST_CompararPonteiroNulo(1, vtPecas[inxLista], "Erro em ponteiro de nova peca.");
    } /* fim ativa: Testar Criar peca */                                       

	/* Testar Destruir peca*/                                                
    else if(strcmp(ComandoTeste, DESTRUIR_PECA_CMD) == 0) {
        numLidos = LER_LerParametros("i", &inxLista);

        if((numLidos != 1) || (! ValidarInxPeca(inxLista, NAO_VAZIO)))
            return TST_CondRetParm;

        PEC_destruir(vtPecas[inxLista]);
        vtPecas[inxLista] = NULL;

        return TST_CondRetOK;
    } /* fim ativa: Testar Destruir peca */                                     

	/* Testar Obter Tipo da peca*/                                            
    else if(strcmp(ComandoTeste, OBTER_TIPO_CMD) == 0) {
        numLidos = LER_LerParametros("ii", &inxLista, &CondRetEsp);

        if((numLidos != 2) || (! ValidarInxPeca(inxLista, NAO_VAZIO)))
            return TST_CondRetParm;

        tipo = PEC_obterTipo(vtPecas[inxLista]);
        return TST_CompararInt(CondRetEsp, tipo, "Tipo errado ao obter tipo.");   	
    } /* fim ativa: Testar Obter Tipo da peca */                                              

	/* Testar Setar Tipo da peca*/                                                           
    else if(strcmp(ComandoTeste, SETAR_TIPO_CMD) == 0) {
        numLidos = LER_LerParametros("ii", &inxLista, &tipo);

        if((numLidos != 2) || (! ValidarInxPeca(inxLista, NAO_VAZIO)))
            return TST_CondRetParm;

        PEC_setarTipo(vtPecas[inxLista], tipo);
        return TST_CondRetOK;
    } /* fim ativa: Testar Setar Tipo da peca */                                          

	/* Testar Obter Caracter da peca*/                                               
    else if(strcmp(ComandoTeste, OBTER_CARACTER_CMD) == 0) {
        numLidos = LER_LerParametros("is", &inxLista, StringDado);

        if((numLidos != 2) || (! ValidarInxPeca(inxLista, NAO_VAZIO)))
            return TST_CondRetParm;

        caracter = PEC_obterCaracter(vtPecas[inxLista]);
        return TST_CompararEspaco(StringDado, &caracter, 1, "Caracter errado ao obter caracter.");
    } /* fim ativa: Testar Obter Caracter da peca */                                             

	/* Testar Setar Caracter da peca*/                                                            
    else if(strcmp(ComandoTeste, SETAR_CARACTER_CMD) == 0) {
        numLidos = LER_LerParametros("is", &inxLista, StringDado);

        if((numLidos != 2) || (! ValidarInxPeca(inxLista, NAO_VAZIO)))
            return TST_CondRetParm;

        PEC_setarCaracter(vtPecas[inxLista], StringDado[0]);
        return TST_CondRetOK;
    } /* fim ativa: Testar Setar Caracter da peca */  

    return TST_CondRetNaoConhec;
} /* Fim função: TPEC &Testar peca */

/*****  Código das funções encapsuladas no módulo  *****/

/***********************************************************************
*
*  $FC Função: TPEC -Validar indice de peca
*
***********************************************************************/

int ValidarInxPeca(int inxLista, int Modo)
{
    if((inxLista <  0) || (inxLista >= DIM_VT_PECA))
        return FALSE;

    if(Modo == VAZIO) {
        if(vtPecas[inxLista] != 0)
            return FALSE;
    } else {
        if(vtPecas[inxLista] == 0)
            return FALSE;
    }
    return TRUE;
} /* Fim função: TPEC -Validar indice de lista */


/********** Fim do módulo de implementação: Testpeca  Teste do modulo peca **********/
