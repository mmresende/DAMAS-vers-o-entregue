/***************************************************************************
*  $MCI Módulo de implementação: LIS  Lista duplamente encadeada
*
*  Arquivo gerado:              LISTA.c
*  Letras identificadoras:      LIS
*  
*  Projeto: damas
*  Arquivo: damas\Fontes\lista.c   
*
*  Autores: hs - Henrique Santiago
*	    mr - Marcelo Resende
*	    rh - Rafael Haeusler
*
*  $HA Histórico de evolução: 
*     Versão  Autor    Data     Observações
*       2       hs/mr/rh   17/junho/2014    implementação completa do jogo
*    
*  $CRE Créditos
*    Arndt von Staa. Programa AutoTest - Arcabouço para a automação de testes de 
*		 programas redigidos em C; módulo Lista Duplamente Encadeada
***************************************************************************/

#include <stdio.h>
#include <string.h>
#include <memory.h>
#include <malloc.h>
#include <assert.h>

#define LISTA_OWN
#include "lista.h"
#undef LISTA_OWN

#ifdef _DEBUG
#include "conta.h"
#include "cespdin.h"
#include "generico.h"
#include "tipos.h"
#endif

/***********************************************************************
*
*  $TC Tipo de dados: LIS Elemento da lista
*
***********************************************************************/

typedef struct tagElemLista {
#ifdef _DEBUG
    LIS_tppLista pCabeca;
    /* Ponteiro para cabeca
    *
    * $ED Descrição
    *   Todos os nós da lista devem apontar para a respectiva cabeça.
    *   Esse ponteiro corresponde a um identificador da lista para fins
    *   de verificação da integridade. */
#endif
    /* Ponteiro para o valor contido no elemento */
    void *pValor;
    /* Ponteiro para o elemento antecessor */
    struct tagElemLista *pAnt;
    /* Ponteiro para o elemento sucessor */
    struct tagElemLista *pProx;
} tpElemLista;

/***********************************************************************
*
*  $TC Tipo de dados: LIS Descritor da cabeça de lista
*
***********************************************************************/

typedef struct LIS_tagLista {
    tpElemLista *pOrigemLista;
    /* Ponteiro para a origem da lista */
    tpElemLista *pFimLista;
    /* Ponteiro para o final da lista */
    tpElemLista *pElemCorr;
    /* Ponteiro para o elemento corrente da lista */
    int numElem;
    /* Número de elementos da lista */
    void (*ExcluirValor)(void *pValor);
    /* Ponteiro para a função de destruição do valor contido em um elemento */
} LIS_tpLista;

/***** Protótipos das funções encapuladas no módulo *****/

static void LiberarElemento(LIS_tppLista pLista, tpElemLista *pElem);
static tpElemLista * CriarElemento(LIS_tppLista pLista, void *pValor);
static void LimparCabeca(LIS_tppLista pLista);
#ifdef _DEBUG
static LIS_tpCondRet LIS_VerificarCabeca(LIS_tppLista pCabeca);
static LIS_tpCondRet LIS_VerificarEncadeamento(tpElemLista* pElem);
#endif
/*****  Código das funções exportadas pelo módulo  *****/

/***************************************************************************
*
*  Função: LIS  &Criar lista
*  ****/

LIS_tppLista LIS_CriarLista(void (*ExcluirValor)(void *pDado))
{
    LIS_tpLista *pLista = NULL;
    pLista = (LIS_tpLista*)malloc(sizeof(LIS_tpLista));
    if(pLista == NULL)
        return NULL;
#ifdef _DEBUG
    CED_DefinirTipoEspaco(pLista, LIS_TipoEspacoCabeca);
#endif
    LimparCabeca(pLista);
    pLista->ExcluirValor = ExcluirValor;
    return pLista;
} /* Fim função: LIS  &Criar lista */

/***************************************************************************
*
*  Função: LIS  &Destruir lista
*  ****/

void LIS_DestruirLista(LIS_tppLista pLista)
{
#ifdef _DEBUG
    assert(pLista != NULL);
#endif

    LIS_EsvaziarLista(pLista);
    free(pLista);
} /* Fim função: LIS  &Destruir lista */

/***************************************************************************
*
*  Função: LIS  &Esvaziar lista
*  ****/

void LIS_EsvaziarLista(LIS_tppLista pLista)
{
    tpElemLista *pElem;
    tpElemLista *pProx;

#ifdef _DEBUG
    assert(pLista != NULL);
#endif

    pElem = pLista->pOrigemLista;
    while(pElem != NULL) {
        pProx = pElem->pProx;
        LiberarElemento(pLista , pElem);
        pElem = pProx;
    }

    LimparCabeca(pLista);
}  /* Fim função: LIS  &Esvaziar lista */

/***************************************************************************
*
*  Função: LIS  &Inserir elemento antes
*  ****/

LIS_tpCondRet LIS_InserirElementoAntes(LIS_tppLista pLista, void *pValor)
{
    tpElemLista *pElem;

#ifdef _DEBUG
    assert(pLista != NULL);
#endif

    pElem = CriarElemento(pLista , pValor);
    if(pElem == NULL)
        return LIS_CondRetFaltouMemoria;

    if(pLista->pElemCorr == NULL) {
        pLista->pOrigemLista = pElem;
        pLista->pFimLista = pElem;
    }
    else {
        if(pLista->pElemCorr->pAnt != NULL) {
            pElem->pAnt = pLista->pElemCorr->pAnt;
            pLista->pElemCorr->pAnt->pProx = pElem;
        }
        else
            pLista->pOrigemLista = pElem;

        pElem->pProx = pLista->pElemCorr;
        pLista->pElemCorr->pAnt = pElem;
    }

    pLista->pElemCorr = pElem;
    return LIS_CondRetOK;
} /* Fim função: LIS  &Inserir elemento antes */

/***************************************************************************
*
*  Função: LIS  &Inserir elemento após
*  ****/

LIS_tpCondRet LIS_InserirElementoApos(LIS_tppLista pLista , void *pValor)
{
    tpElemLista * pElem;

#ifdef _DEBUG
    assert(pLista != NULL);
#endif

    pElem = CriarElemento(pLista , pValor);
    if(pElem == NULL)
        return LIS_CondRetFaltouMemoria;
    if(pLista->pElemCorr == NULL) {
        pLista->pOrigemLista = pElem;
        pLista->pFimLista = pElem;
    }
    else {
        if(pLista->pElemCorr->pProx != NULL) {
            pElem->pProx = pLista->pElemCorr->pProx;
            pLista->pElemCorr->pProx->pAnt = pElem;
        } else
            pLista->pFimLista = pElem;

        pElem->pAnt = pLista->pElemCorr;
        pLista->pElemCorr->pProx = pElem;
    }

    pLista->pElemCorr = pElem;
    return LIS_CondRetOK;
} /* Fim função: LIS  &Inserir elemento após */

/***************************************************************************
*
*  Função: LIS  &Excluir elemento
*  ****/

LIS_tpCondRet LIS_ExcluirElemento(LIS_tppLista pLista)
{
    tpElemLista * pElem;

#ifdef _DEBUG
    assert(pLista != NULL);
#endif

    if(pLista->pElemCorr == NULL)
        return LIS_CondRetListaVazia;

    pElem = pLista->pElemCorr;

    if(pElem->pAnt != NULL) {
        pElem->pAnt->pProx = pElem->pProx;
        pLista->pElemCorr = pElem->pAnt;
    }
    else {
        pLista->pElemCorr = pElem->pProx;
        pLista->pOrigemLista = pLista->pElemCorr;
    }

    if(pElem->pProx != NULL)
        pElem->pProx->pAnt = pElem->pAnt;
    else
        pLista->pFimLista = pElem->pAnt;

    LiberarElemento(pLista , pElem);
    return LIS_CondRetOK;
} /* Fim função: LIS  &Excluir elemento */

/***************************************************************************
*
*  Função: LIS  &Obter referência para o valor contido no elemento
*  ****/

void * LIS_ObterValor(LIS_tppLista pLista)
{
#ifdef _DEBUG
    assert(pLista != NULL);
#endif

    if(pLista->pElemCorr == NULL)
        return NULL;
    return pLista->pElemCorr->pValor;
} /* Fim função: LIS  &Obter referência para o valor contido no elemento */

/***************************************************************************
*
*  Função: LIS  &Setar valor do elemento corrente
*  ****/

LIS_tpCondRet LIS_SetarValor(LIS_tppLista pLista, void *pValor)
{
#ifdef _DEBUG
    assert(pLista != NULL);
#endif

    if(pLista->pElemCorr == NULL)
        return LIS_CondRetListaVazia;
    pLista->pElemCorr->pValor = pValor;
    return LIS_CondRetOK;
} /* Fim função: LIS  &Setar valor do elemento corrente */

/***************************************************************************
*
*  Função: LIS  &Ir para o elemento inicial
*  ****/

void LIS_IrInicioLista(LIS_tppLista pLista)
{
#ifdef _DEBUG
    assert(pLista != NULL);
#endif

    pLista->pElemCorr = pLista->pOrigemLista;
} /* Fim função: LIS  &Ir para o elemento inicial */

/***************************************************************************
*
*  Função: LIS  &Ir para o elemento final
*  ****/

void LIS_IrFinalLista(LIS_tppLista pLista)
{
#ifdef _DEBUG
    assert(pLista != NULL);
#endif

    pLista->pElemCorr = pLista->pFimLista;
} /* Fim função: LIS  &Ir para o elemento final */

/***************************************************************************
*
*  Função: LIS  &Ir para o elemento de indíce i
*  ****/

LIS_tpCondRet LIS_IrIndice(LIS_tppLista pLista, int i)
{
#ifdef _DEBUG
    assert(pLista != NULL);
#endif

    LIS_IrInicioLista(pLista);
    return LIS_AvancarElementoCorrente(pLista, i);
} /* Fim função: LIS  &Ir para o elemento de indíce i */

/***************************************************************************
*
*  Função: LIS  &Avançar elemento
*  ****/

LIS_tpCondRet LIS_AvancarElementoCorrente(LIS_tppLista pLista , int numElem)
{
    int i;

    tpElemLista * pElem;

#ifdef _DEBUG
    assert(pLista != NULL);
#endif

    if(pLista->pElemCorr == NULL)
        return LIS_CondRetListaVazia;

    if(numElem > 0) {
        pElem = pLista->pElemCorr;
        for(i = numElem; i > 0; i--) {
            if(pElem == NULL)
                break;
            pElem = pElem->pProx;
        }

        if(pElem != NULL) {
            pLista->pElemCorr = pElem;
            return LIS_CondRetOK;
        }

        pLista->pElemCorr = pLista->pFimLista;
        return LIS_CondRetFimLista;
    }
    else if(numElem < 0) {
        pElem = pLista->pElemCorr;
        for(i = numElem ; i < 0 ; i++) {
            if(pElem == NULL)
                break;
            pElem = pElem->pAnt;
        }

        if(pElem != NULL) {
            pLista->pElemCorr = pElem;
            return LIS_CondRetOK;
        }

        pLista->pElemCorr = pLista->pOrigemLista;
        return LIS_CondRetFimLista;

    }
    return LIS_CondRetOK;
} /* Fim função: LIS  &Avançar elemento */

/***************************************************************************
*
*  Função: LIS  &Procurar elemento contendo valor
*  ****/

LIS_tpCondRet LIS_ProcurarValor(LIS_tppLista pLista , void * pValor)
{
    tpElemLista * pElem;

#ifdef _DEBUG
    assert(pLista != NULL);
#endif

    if(pLista->pElemCorr == NULL)
        return LIS_CondRetListaVazia;

    for(pElem = pLista->pElemCorr; pElem != NULL; pElem = pElem->pProx) {
        if(pElem->pValor == pValor) {
            pLista->pElemCorr = pElem;
            return LIS_CondRetOK;
        }
    }

    return LIS_CondRetNaoAchou;
} /* Fim função: LIS  &Procurar elemento contendo valor */

#ifdef _DEBUG

/***************************************************************************
*
*  Função: LIS  &Verificar a estrutura lista
*  ****/

LIS_tpCondRet LIS_VerificarLista(LIS_tppLista pCabeca)
{
    LIS_tpCondRet ret;
    tpElemLista* pElem;
    int numElementos = 0;

    ret = LIS_VerificarCabeca(pCabeca);
    if(ret != LIS_CondRetOK)
        return ret;

    /*Percorre Lista, verificando cada no*/
    for(pElem = pCabeca->pOrigemLista; pElem; pElem = pElem->pProx) {
        if(TST_CompararInt(LIS_TipoEspacoNo, CED_ObterTipoEspaco(pElem),
                           "Tipo do espaço de dados não é no de lista.") != TST_CondRetOK) {
            CNT_CONTAR("Elemento da lista nao eh no");
            return LIS_CondRetErroEstrutura ;
        }
		CNT_CONTAR("Tipo espaco eh no");
		CED_MarcarEspacoAtivo(pElem);
        if(pElem->pCabeca != pCabeca) {
            CNT_CONTAR("Referencia do elemento de lista errada");
            TST_NotificarFalha("elemento da lista nao aponta para respectiva cabeca");
			return LIS_CondRetErroEstrutura;
		}
		CNT_CONTAR("Referencia do elemento de lista correta");

        /*Verifica encadeamento da lista, sua origem e final*/
		ret = LIS_VerificarEncadeamento(pElem);
        if(ret != LIS_CondRetOK) {
            CNT_CONTAR("Encadeamento errado");
            return ret;
        }
        numElementos++;
    }
    if(pCabeca->numElem!=numElementos) {
        CNT_CONTAR("Numero de elementos na cabeca diferente do real");
        TST_NotificarFalha("Numero de elementos indicado na cabeça difere do real");
        return LIS_CondRetErroEstrutura;
    }
    CNT_CONTAR("Lista de listas OK");
    return LIS_CondRetOK;
}

#endif

#ifdef _DEBUG
/***************************************************************************
*
*  Função: LIS  &Deturpar lista
*  ****/

void LIS_Deturpar(LIS_tppLista pLista, LIS_tpModosDeturpacao ModoDeturpar)
{
    tpElemLista *pElem;

    if(!pLista)
        return;

    switch(ModoDeturpar) {
    case LIS_EliminarElemento:
    {
        LIS_ExcluirElemento(pLista);
        break;
    }
    case LIS_DeturpaProximoNulo:
    {
        pLista->pElemCorr->pProx = NULL;
        break;
    }
    case LIS_DeturpaAnteriorNulo:
    {
        pLista->pElemCorr->pAnt = NULL;
        break;
    }
    case LIS_DeturpaProximoLixo:
    {
        pLista->pElemCorr->pProx = (tpElemLista*)pLista + 123;
        break;
    }
    case LIS_DeturpaAnteriorLixo:
    {
        pLista->pElemCorr->pAnt = (tpElemLista*)pLista + 123;
        break;
    }
    case LIS_DeturpaConteudoNulo:
    {
        LIS_SetarValor(pLista, NULL);
        break;
    }
    case LIS_DeturpaTipoNo:
    {
        CED_DefinirTipoEspaco(pLista->pElemCorr, CED_ID_TIPO_VALOR_NULO);
        break;
    }
    case LIS_LiberaSemFree:
    {
        pElem = pLista->pElemCorr;

        if(pElem->pAnt != NULL) {
            pElem->pAnt->pProx = pElem->pProx;
            pLista->pElemCorr = pElem->pAnt;
        }
        else {
            pLista->pElemCorr = pElem->pProx;
            pLista->pOrigemLista = pLista->pElemCorr;
        }

        if(pElem->pProx != NULL)
            pElem->pProx->pAnt = pElem->pAnt;
        else
            pLista->pFimLista = pElem->pAnt;

        break;
    }
    case LIS_PonteiroCorrenteNulo:
    {
        pLista->pElemCorr = NULL;
        break;
    }
    case LIS_PonteiroOrigemNulo:
    {
        pLista->pOrigemLista = NULL;
        break;
    }
    case LIS_PonteiroFimNulo:
    {
        pLista->pFimLista = NULL;
        break;
    }
	case LIS_NumeroElementosNegativo:
	{
		pLista->numElem=-1;
		break;
    }
	case LIS_NumeroElementosNulo:
	{
		pLista->numElem=0;
		break;
    }
	case LIS_DeturpaNumeroElementos:
		{
			pLista->numElem++;
			break;
		}
}
}
#endif

/*****  Código das funções encapsuladas no módulo  *****/

/***********************************************************************
*
*  $FC Função: LIS  -Liberar elemento da lista
*
*  $ED Descrição da função
*     Elimina os espaços apontados pelo valor do elemento e o
*     próprio elemento.
*
***********************************************************************/

void LiberarElemento(LIS_tppLista pLista, tpElemLista *pElem)
{
    if((pLista->ExcluirValor != NULL) && (pElem->pValor != NULL))
        pLista->ExcluirValor(pElem->pValor);

    free(pElem);
    pLista->numElem--;
} /* Fim função: LIS  -Liberar elemento da lista */

/***********************************************************************
*
*  $FC Função: LIS  -Criar o elemento
*  $ED Descrição da função
*     Cria os espaços apontados pelo valor do elemento e o
*     próprio elemento.
*
***********************************************************************/

tpElemLista * CriarElemento(LIS_tppLista pLista, void * pValor)
{
    tpElemLista * pElem;

    pElem = (tpElemLista *)malloc(sizeof(tpElemLista));
    if(!pElem)
        return NULL;
#ifdef _DEBUG
    CED_DefinirTipoEspaco(pElem, LIS_TipoEspacoNo);
    pElem->pCabeca = pLista;
#endif
    pElem->pValor = pValor;
    pElem->pAnt = NULL;
    pElem->pProx = NULL;
    pLista->numElem++;
    return pElem;

} /* Fim função: LIS  -Criar o elemento */

/***********************************************************************
*
*  $FC Função: LIS  -Limpar a cabeça da lista
*  $ED Descrição da função
*     
*     Elimina os todos os espaços apontados pelo elemento de tipo
*     estruturado LIS_tppLista.
*
***********************************************************************/

void LimparCabeca(LIS_tppLista pLista)
{
    pLista->pOrigemLista = NULL;
    pLista->pFimLista = NULL;
    pLista->pElemCorr = NULL;
    pLista->numElem = 0;
} /* Fim função: LIS  -Limpar a cabeça da lista */

#ifdef _DEBUG
/***********************************************************************
*
*  $FC Função: LIS  -Verificar a cabeça da lista
*  $ED Descrição da função 
*    Verifica algumas das assertivas da cabeça da lista
*  $FV Valor retornado
*	  Retorna LIS_CondRetOK, caso não encontre falhas na estrutura,ou
*     LIS_CondRetErroEstrutura, caso contrário
***********************************************************************/
LIS_tpCondRet LIS_VerificarCabeca(LIS_tppLista pCabeca)
{
    if(!pCabeca) {
        CNT_CONTAR("Cabeca de lista inexistente");
        TST_NotificarFalha("Tentou verificar cabeca inexistente");
        return LIS_CondRetErroEstrutura;
    }
    else
        CNT_CONTAR("Cabeca de lista existente");

    if(!CED_VerificarEspaco(pCabeca, NULL)) {
        CNT_CONTAR("Controle de espaco acusa erro na lista");
        TST_NotificarFalha("Controle do espaço acusou erro.");
        return LIS_CondRetErroEstrutura;
    }
    else
        CNT_CONTAR("Controle de espaco nao acusa erro na lista");

    if(TST_CompararInt(LIS_TipoEspacoCabeca, CED_ObterTipoEspaco(pCabeca),
                       "Tipo do espaço de dados nao e cabeça de lista.") != TST_CondRetOK) {
        CNT_CONTAR("Tipo nao e lista");
        return LIS_CondRetErroEstrutura;
    }
    else
        CNT_CONTAR("Tipo e lista");

    if(pCabeca->numElem < 0) {
        CNT_CONTAR("Numero de elementos menor que zero");
        TST_NotificarFalha("Cabeça acusa numero de elementos menor que zero");
        return LIS_CondRetErroEstrutura;
    }
    else if(pCabeca->numElem == 0) {
        CNT_CONTAR("Cabeca com zero elementos");
        if(pCabeca->pOrigemLista || pCabeca->pFimLista || pCabeca->pElemCorr) {
            CNT_CONTAR("Cabeca com zero elementos e nao vazia");
            TST_NotificarFalha("Cabeça acusa zero elementos, mas lista não está vazia");
            return LIS_CondRetErroEstrutura;
        }
        else
            CNT_CONTAR("Cabeca com zero elementos e vazia");
    }
    CNT_CONTAR("Cabeca de lista correta");
    return LIS_CondRetOK;
}

/***********************************************************************
*
*  $FC Função: LIS  -Verificar Encadeamento da lista
*  $ED Descrição da função
*     Verifica encadeamento, origem e fim da lista
*  $FV Valor retornado
*	  Retorna LIS_CondRetOK, caso não encontre falhas na estrutura,ou
*     LIS_CondRetErroEstrutura, caso contrário
*  
***********************************************************************/

LIS_tpCondRet LIS_VerificarEncadeamento(tpElemLista* pElem)
{	
    if(pElem->pProx != NULL) {
        CNT_CONTAR("Ha mais de um elemento");
        if(!CED_VerificarEspaco(pElem->pProx, NULL) || pElem->pProx->pAnt != pElem) {
            CNT_CONTAR("Encadeamento apos errado");
            TST_NotificarFalha("Encadeamento apos esta errado");
            return LIS_CondRetErroEstrutura;
        }
        else
            CNT_CONTAR("Encadeamento apos correto");
    }
    else if(pElem->pCabeca->pFimLista != pElem) {
        CNT_CONTAR("Cabeca nao aponta para o fim");
        TST_NotificarFalha("A cabeca nao aponta para o fim da lista");
        return LIS_CondRetErroEstrutura;
    }

    if(pElem->pAnt != NULL) {
        if(!CED_VerificarEspaco(pElem->pAnt, NULL) || pElem->pAnt->pProx != pElem) {
            CNT_CONTAR("Encadeamento antes errado");
            TST_NotificarFalha("Encadeamento antes esta errado");
            return LIS_CondRetErroEstrutura;
        }
        else
            CNT_CONTAR("Encadeamento antes correto");
    }
    else if(pElem->pCabeca->pOrigemLista != pElem) {
        CNT_CONTAR("Cabeca nao aponta pra origem");
        TST_NotificarFalha("A cabeca nao aponta para a origem da lista");
        return LIS_CondRetErroEstrutura;
    }

    CNT_CONTAR("Encadeamento Correto");
    return LIS_CondRetOK;
}

#endif


/********** Fim do módulo de implementação: LIS  Lista duplamente encadeada **********/
