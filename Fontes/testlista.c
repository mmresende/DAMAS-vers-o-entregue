/***************************************************************************
*  $MCI Módulo de implementação: Testlista Teste lista de símbolos
*
*  Arquivo gerado:              Testlista.c
*  Letras identificadoras:      TLIS
*
*  Projeto: damas
*  Arquivo: damas\Fontes\testlista.c    
*
*  Autores: hs - Henrique Santiago
*	    mr - Marcelo Resende
*	    rh - Rafael Haeusler
*
*  $HA Histórico de evolução:
*     Versão  Autor    				Data     Observações
*     1       Henrique Santiago   13/abr/2014 início desenvolvimento
*
*  $CRE Créditos
*     Arndt von Staa. Programa AutoTest - Arcabouço para a automação de testes de
*	     programas redigidos em C; módulo Lista Duplamente Encadeada
***************************************************************************/

#include    <string.h>
#include    <stdio.h>
#include    <malloc.h>

#include    <tst_espc.h>
#include    <generico.h>
#include    <lerparm.h>

#include    "lista.h"

static const char RESET_LISTA_CMD         [] = "=resetteste"		;
static const char CRIAR_LISTA_CMD         [] = "=criarlista"		;
static const char DESTRUIR_LISTA_CMD      [] = "=destruirlista"	    ;
static const char ESVAZIAR_LISTA_CMD      [] = "=esvaziarlista"	    ;
static const char INS_ELEM_ANTES_CMD      [] = "=inselemantes"		;
static const char INS_ELEM_ANTES_CMD_INT  [] = "=inselemantes.int"  ;
static const char INS_ELEM_APOS_CMD       [] = "=inselemapos"		;
static const char INS_ELEM_APOS_CMD_INT   [] = "=inselemapos.int"   ;
static const char OBTER_VALOR_CMD         [] = "=obtervalorelem"	;
static const char OBTER_VALOR_CMD_INT     [] = "=obtervalorelem.int";
static const char EXC_ELEM_CMD            [] = "=excluirelem"		;
static const char IR_INICIO_CMD           [] = "=irinicio"			;
static const char IR_FIM_CMD              [] = "=irfinal"			;
static const char IR_INDICE_CMD           [] = "=irindice"			;
static const char AVANCAR_ELEM_CMD        [] = "=avancarelem"		;
static const char SETAR_VALOR_CMD_INT	  [] = "=marcarvalor.int"	;
static const char PROCURAR_VALOR_CMD      [] = "=procurarvalor"	    ;

#define TRUE  1
#define FALSE 0

#define VAZIO     0
#define NAO_VAZIO 1

#define DIM_VT_LISTA   10
#define DIM_VT_PTR    100
#define DIM_VALOR     100
#define DIM_VALOR_INT	2               

LIS_tppLista vtListas[DIM_VT_LISTA];
void *storedPtr[DIM_VT_PTR];
int storedPtrIndex = 1;

/***** Protótipos das funções encapsuladas no módulo *****/

static void DestruirValor(void * pValor);
static int ValidarInxLista(int inxLista, int modo);
static int ValidarInxStoredPtr(int inxStoredPtr);

/*****  Código das funções exportadas pelo módulo  *****/


/***********************************************************************
*
*  $FC Função: TLIS &Testar lista
*
*  $ED Descrição da função
*     Podem ser criadas até 10 listas, identificadas pelos í­ndices 0 a 10
*
*     Comandos disponíveis:
*
*     =resetteste
*           - anula o vetor de listas. Provoca vazamento de memória
*     =criarlista                   inxLista
*     =destruirlista                inxLista
*     =esvaziarlista                inxLista
*     =inselemantes                 inxLista  string  CondRetEsp
*	  =inselemantes.int             inxLista  int	  int			CondRetEsp
*     =inselemapos                  inxLista  string  CondRetEsp
*	  =inselemapos.int  			inxLista  int	  int			CondRetEsp
*     =obtervalorelem               inxLista  string  CondretPonteiro
*	  =obtervalorelem.int			inxLista  int	  int			CondRetEsp
*     =excluirelem                  inxLista  CondRetEsp
*     =irinicio                     inxLista
*     =irfinal                      inxLista
*     =irindice						inxLista  int	  CondRetEsp
*	  =avancarelem                  inxLista  numElem CondRetEsp
*	  =marcarvalor.int				inxLista  int     int			CondRetEsp
*     =procurarvalor                inxLista  inxPtr  CondRetEsp
***********************************************************************/

TST_tpCondRet TST_EfetuarComando(char * ComandoTeste)
{
    int inxLista  = -1, numLidos   = -1, CondRetEsp = -1;

    TST_tpCondRet CondRet;

    char   StringDado[DIM_VALOR];
    char * pDado;

    int IntDado[DIM_VALOR_INT];
    int* pDadoInt;

    int ValEsp = -1;
    int i;
    int numElem = -1;

    int inxStoredPtr;

    storedPtr[0] = NULL;
    StringDado[0] = 0;

    /* Efetuar reset de teste de lista */
    if(strcmp(ComandoTeste, RESET_LISTA_CMD) == 0) {
        for(i = 0; i < DIM_VT_LISTA; i++)
            vtListas[i] = NULL;

        storedPtrIndex = 0;
        return TST_CondRetOK;

    } /* fim ativa: Efetuar reset de teste de lista */

    /* Testar CriarLista */
    else if(strcmp(ComandoTeste, CRIAR_LISTA_CMD) == 0) {
        numLidos = LER_LerParametros("i", &inxLista);

        if((numLidos != 1) || (!ValidarInxLista(inxLista, VAZIO)))
            return TST_CondRetParm;

        vtListas[inxLista] = LIS_CriarLista(DestruirValor);

        return TST_CompararPonteiroNulo(1, vtListas[inxLista], "Erro em ponteiro de nova lista.");
    } /* fim ativa: Testar CriarLista */

    /* Testar Esvaziar lista lista */
    else if(strcmp(ComandoTeste, ESVAZIAR_LISTA_CMD) == 0) {
        numLidos = LER_LerParametros("i", &inxLista);

        if((numLidos != 1) || (!ValidarInxLista(inxLista, NAO_VAZIO)))
            return TST_CondRetParm;

        LIS_EsvaziarLista(vtListas[inxLista]);
        return TST_CondRetOK;

    } /* fim ativa: Testar Esvaziar lista lista */

    /* Testar Destruir lista */
    else if(strcmp(ComandoTeste, DESTRUIR_LISTA_CMD) == 0) {
        numLidos = LER_LerParametros("i", &inxLista);

        if((numLidos != 1) || (!ValidarInxLista(inxLista, NAO_VAZIO)))
            return TST_CondRetParm;

        LIS_DestruirLista(vtListas[inxLista]);
        vtListas[inxLista] = NULL;
        return TST_CondRetOK;

    } /* fim ativa: Testar Destruir lista */

    /* Testar inserir elemento antes */
    else if(strcmp(ComandoTeste, INS_ELEM_ANTES_CMD) == 0) {
        numLidos = LER_LerParametros("isi", &inxLista, StringDado, &CondRetEsp);

        if((numLidos != 3) || (!ValidarInxLista(inxLista, NAO_VAZIO)))
            return TST_CondRetParm;

        if(!ValidarInxStoredPtr(storedPtrIndex))
            return TST_CondRetMemoria;

        pDado = (char *) malloc(strlen(StringDado) + 1);
        if(pDado == NULL)
            return TST_CondRetMemoria;

        storedPtr[storedPtrIndex++] = pDado;
        strcpy(pDado, StringDado);

        CondRet = LIS_InserirElementoAntes(vtListas[inxLista], pDado);
        if(CondRet != LIS_CondRetOK)
            free(pDado);

        return TST_CompararInt(CondRetEsp, CondRet, "Condicao de retorno errada ao inserir antes.");
    } /* fim ativa: Testar inserir elemento antes */

    /* Testar inserir elemento antes INTEIRO */
    else if(strcmp(ComandoTeste, INS_ELEM_ANTES_CMD_INT) == 0) {
        numLidos = LER_LerParametros("iiii", &inxLista, &IntDado[0], &IntDado[1], &CondRetEsp);

        if((numLidos != 4) || (!ValidarInxLista(inxLista, NAO_VAZIO)))
            return TST_CondRetParm;

        if(!ValidarInxStoredPtr(storedPtrIndex))
            return TST_CondRetMemoria;

        pDadoInt = (int *) malloc(DIM_VALOR_INT*sizeof(int));
        if(pDadoInt == NULL)
            return TST_CondRetMemoria;

        storedPtr[storedPtrIndex++] = pDadoInt;
        for(i=0;i<DIM_VALOR_INT;i++)
            pDadoInt[i]=IntDado[i];

        CondRet = LIS_InserirElementoAntes(vtListas[inxLista], pDadoInt);
        if(CondRet != LIS_CondRetOK)
            free(pDadoInt);

        return TST_CompararInt(CondRetEsp, CondRet, "Condicao de retorno errada ao inserir antes.");
    } /* fim ativa: Testar inserir elemento antes INTEIRO*/

    /* Testar inserir elemento apos */
    else if(strcmp(ComandoTeste, INS_ELEM_APOS_CMD) == 0) {
        numLidos = LER_LerParametros("isi", &inxLista, StringDado, &CondRetEsp);

        if((numLidos != 3) || (!ValidarInxLista(inxLista, NAO_VAZIO)))
            return TST_CondRetParm;

        if(!ValidarInxStoredPtr(storedPtrIndex))
            return TST_CondRetMemoria;

        pDado = (char*)malloc(strlen(StringDado) + 1);
        if(pDado == NULL)
            return TST_CondRetMemoria;

        storedPtr[storedPtrIndex++] = pDado;
        strcpy(pDado, StringDado);

        CondRet = LIS_InserirElementoApos(vtListas[inxLista], pDado);
        if(CondRet != LIS_CondRetOK)
            free(pDado);

        return TST_CompararInt(CondRetEsp, CondRet, "Condicao de retorno errada ao inserir apos.");
    } /* fim ativa: Testar inserir elemento apos */

    /* Testar inserir elemento apos INTEIRO*/
    else if(strcmp(ComandoTeste, INS_ELEM_APOS_CMD_INT) == 0) {
        numLidos = LER_LerParametros("iiii", &inxLista, &IntDado[0], &IntDado[1], &CondRetEsp);

        if((numLidos != 4) || (!ValidarInxLista(inxLista, NAO_VAZIO)))
            return TST_CondRetParm;

        if(!ValidarInxStoredPtr(storedPtrIndex))
            return TST_CondRetMemoria;

        pDadoInt = (int *) malloc(DIM_VALOR_INT * sizeof(int));
        if(pDadoInt == NULL)
            return TST_CondRetMemoria;

        storedPtr[storedPtrIndex++] = pDadoInt;
        for(i=0;i<DIM_VALOR_INT;i++)
            pDadoInt[i]=IntDado[i];

        CondRet = LIS_InserirElementoApos(vtListas[inxLista], pDadoInt);

        if(CondRet != LIS_CondRetOK)
            free(pDadoInt);

        return TST_CompararInt(CondRetEsp, CondRet, "Condicao de retorno errada ao inserir apos.");
    } /* fim ativa: Testar inserir elemento apos INTEIRO*/

    /* Testar excluir simbolo */
    else if(strcmp(ComandoTeste, EXC_ELEM_CMD) == 0) {
        numLidos = LER_LerParametros("ii", &inxLista, &CondRetEsp);

        if((numLidos != 2) || (!ValidarInxLista(inxLista, NAO_VAZIO)))
            return TST_CondRetParm;

        return TST_CompararInt(CondRetEsp, LIS_ExcluirElemento(vtListas[inxLista]),
                               "CondiÃ§Ã£o de retorno errada ao excluir.");
    } /* fim ativa: Testar excluir simbolo */

    /* Testar obter valor do elemento corrente */
    else if(strcmp(ComandoTeste, OBTER_VALOR_CMD) == 0) {
        numLidos = LER_LerParametros("isi", &inxLista, StringDado, &ValEsp);

        if((numLidos != 3) || (!ValidarInxLista(inxLista, NAO_VAZIO)))
            return TST_CondRetParm;

        pDado = (char *) LIS_ObterValor(vtListas[inxLista]);

        if(ValEsp == 0)
            return TST_CompararPonteiroNulo(0, pDado, "Valor nÃ£o deveria existir.");

        if(pDado == NULL)
            return TST_CompararPonteiroNulo(1, pDado, "Dado tipo um deveria existir.");

        return TST_CompararString(StringDado, pDado, "Valor do elemento errado.");
    } /* fim ativa: Testar obter valor do elemento corrente */

    /* Testar obter valor do elemento corrente INTEIRO*/
    else if(strcmp(ComandoTeste, OBTER_VALOR_CMD_INT) == 0) {
        numLidos = LER_LerParametros("iiii", &inxLista, &IntDado[0], &IntDado[1], &ValEsp);

        if((numLidos != 4) || (!ValidarInxLista(inxLista, NAO_VAZIO)))
            return TST_CondRetParm;

        pDadoInt = (int *)LIS_ObterValor(vtListas[inxLista]);

        if(ValEsp == 0)
            return TST_CompararPonteiroNulo(0, pDadoInt, "Valor nÃ£o deveria existir.");

        if(pDadoInt == NULL)
            return TST_CompararPonteiroNulo(1, pDadoInt, "Dado tipo um deveria existir.");

        return TST_CompararEspaco(IntDado, pDadoInt, DIM_VALOR_INT * sizeof(int),
                                  "Valor do elemento errado.");
    } /* fim ativa: Testar obter valor do elemento corrente INTEIRO*/

    /* Testar ir para o elemento inicial */
    else if(strcmp(ComandoTeste, IR_INICIO_CMD) == 0) {
        numLidos = LER_LerParametros("i", &inxLista);

        if((numLidos != 1) || (!ValidarInxLista(inxLista, NAO_VAZIO)))
            return TST_CondRetParm;

        LIS_IrInicioLista(vtListas[inxLista]);
        return TST_CondRetOK;
    } /* fim ativa: Testar ir para o elemento inicial */

    /* LIS  &Ir para o elemento final */
    else if(strcmp(ComandoTeste, IR_FIM_CMD) == 0) {
        numLidos = LER_LerParametros("i", &inxLista);

        if((numLidos != 1) || (!ValidarInxLista(inxLista, NAO_VAZIO)))
            return TST_CondRetParm;

        LIS_IrFinalLista(vtListas[inxLista]);
        return TST_CondRetOK;
    } /* fim ativa: LIS  &Ir para o elemento final */

    /* LIS  &Avançar elemento */
    else if(strcmp(ComandoTeste, AVANCAR_ELEM_CMD) == 0) {
        numLidos = LER_LerParametros("iii", &inxLista, &numElem, &CondRetEsp);

        if((numLidos != 3) || (!ValidarInxLista(inxLista, NAO_VAZIO)))
            return TST_CondRetParm;

        return TST_CompararInt(CondRetEsp,
                               LIS_AvancarElementoCorrente(vtListas[inxLista], numElem),
                               "Condicao de retorno errada ao avancar");

    } /* fim ativa: LIS  &Avançar elemento */

    /* Testar Ir Indice */
    else if(strcmp(ComandoTeste, IR_INDICE_CMD) == 0) {
        numLidos = LER_LerParametros("iii", &inxLista, &numElem, &CondRetEsp);
        if((numLidos != 3) || (!ValidarInxLista(inxLista, NAO_VAZIO)))
            return TST_CondRetParm;

        return TST_CompararInt(CondRetEsp, LIS_IrIndice(vtListas[inxLista], numElem),
                               "Condicao de retorno errada ao ir para o índice");
    } /* fim ativa: Testar Ir Indice */

    /* Testar Setar Valor INTEIRO*/
    else if(strcmp(ComandoTeste, SETAR_VALOR_CMD_INT) == 0) {
        numLidos = LER_LerParametros("iiii", &inxLista, &IntDado[0], &IntDado[1], &CondRetEsp);
        if((numLidos != 4) || (!ValidarInxLista(inxLista, NAO_VAZIO)))
            return TST_CondRetParm;

        return TST_CompararInt(CondRetEsp, LIS_SetarValor(vtListas[inxLista], IntDado),
                               "Condicao de retorno errada ao ir marcar o valor");
    } /* fim ativa: LIS  Setar Valor INTEIRO*/

    /* Testar Procurar Valor */
    else if(strcmp(ComandoTeste, PROCURAR_VALOR_CMD) == 0) {
        numLidos = LER_LerParametros("iii", &inxLista, &inxStoredPtr, &CondRetEsp);
        if((numLidos != 3) || (!ValidarInxLista(inxLista, NAO_VAZIO)))
            return TST_CondRetParm;

        if(!ValidarInxStoredPtr(inxStoredPtr))
            return TST_CondRetParm;

        return TST_CompararInt(CondRetEsp, LIS_ProcurarValor(vtListas[inxLista], storedPtr[inxStoredPtr]),
                               "Condicao de retorno errada ao procurar valor");
    } /* fim ativa: LIS Procurar Valor */

    return TST_CondRetNaoConhec;
} /* Fim função: TLIS &Testar lista */


/*****  Código das funções encapsuladas no módulo  *****/


/***********************************************************************
*
*  $FC Função: TLIS -Destruir valor
*
***********************************************************************/

void DestruirValor(void * pValor)
{
    free(pValor);
} /* Fim função: TLIS -Destruir valor */


/***********************************************************************
*
*  $FC Função: TLIS -Validar indice de lista
*
***********************************************************************/

int ValidarInxLista(int inxLista, int modo)
{
    if((inxLista <  0) || (inxLista >= DIM_VT_LISTA))
        return FALSE;

    if(modo == VAZIO) {
        if(vtListas[inxLista] != 0)
            return FALSE;
    }
    else {
        if(vtListas[inxLista] == 0)
            return FALSE;
    }
    return TRUE;
} /* Fim função: TLIS -Validar indice de lista */

/***********************************************************************
*
*  $FC Função: TLIS -Validar indice de ponteiros
*
***********************************************************************/

int ValidarInxStoredPtr(int inxStoredPtr)
{
    return (inxStoredPtr >= 0 && inxStoredPtr < DIM_VT_PTR) ? TRUE : FALSE;
} /* Fim função: TLIS -Validar indice de ponteiros */

/********** Fim do módulo de implementação: TLIS Teste lista de sí­mbolos **********/
