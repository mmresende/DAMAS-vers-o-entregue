
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
*     2       hs/mr/rh   17/junho/2014    implementação completa do jogo
*
*
***************************************************************************/

#include    <string.h>
#include    <stdio.h>
#include    <malloc.h>

#include    <tst_espc.h>
#include    <generico.h>
#include    <lerparm.h>
#include    "cespdin.h"

#include    "tabuleiro.h"
#include    "peca.h"

static const char RESET_TABULEIRO_CMD      [] = "=resetteste";
static const char CRIAR_TABULEIRO_CMD      [] = "=criartabuleiro";
static const char DESTRUIR_TABULEIRO_CMD   [] = "=destruirtabuleiro";
static const char INICIALIZAR_TABULEIRO_CMD[] = "=inicializartabuleiro";
static const char OBTER_CASA_CMD           [] = "=obtercasa";
static const char SETAR_CASA_CMD           [] = "=setarcasa";
static const char REMOVER_PECA_CMD         [] = "=removerpeca";

/* os comandos a seguir somente operam em modo _DEBUG */
#ifdef _DEBUG
static const char VER_LISTA_CMD			   [] = "=verificar";
static const char DETURPAR_CMD			   [] = "=deturpar";
static const char VER_MEMORIA_CMD		   [] = "=verificarmemoria";
static const char POSICIONAR_CMD		   [] = "=posicionar";
#endif

#define TRUE  1
#define FALSE 0

#define VAZIO     0
#define NAO_VAZIO 1
#define INDIFERENTE 2

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
*     =destruirtabuleiro         inxLista  CondRet
*     =inicializartabuleiro      inxLista
*     =obterpeca                 inxLista  linha  coluna  ret
*     =setarcasa				 inxlista  linha  coluna  CondRet
*     =removerpeca				 inxlista  linha  coluna
*
*	Estes comandos somente podem ser executados se o modulo tiver sido
*     compilado com _DEBUG ligado
*
*     =verificar				inxLista  CondRet
*     =deturpar					inxLista  ModoDeturparTAB
*	  =deturpar					inxlista  ModoDeturparTAB  ModoDeturparLIS  linha
*	  =deturpar					inxlista  ModoDeturparTAB  ModoDeturparLIS  linha   coluna
*	  =verificarmemoria			inxlista  CondRetEsp
*     =posicionar				inxlista  linha   coluna
***********************************************************************/

TST_tpCondRet TST_EfetuarComando(char *ComandoTeste)
{
    int inxLista  = -1;
    int numLidos   = -1;
    int CondRetEsp = -1;
    void *retPtr;
    char StringDado[DIM_VALOR];
    int i;
    int CondRet;
    int linha = -1;
    int coluna = -1;
    Peca *peca;
#ifdef _DEBUG                                                          
	int  ModoDeturparTAB= -1;
	int  ModoDeturparLIS=-1;
#endif
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
        numLidos = LER_LerParametros("ii", &inxLista, &CondRetEsp);

        if((numLidos != 2) || (!ValidarInxTabuleiro(inxLista, INDIFERENTE)))
            return TST_CondRetParm;

        CondRet = TAB_destruir(vtTabuleiros[inxLista]);
        vtTabuleiros[inxLista] = NULL;

        return TST_CompararInt(CondRetEsp, CondRet, "Condicao de retorno errada ao destruir o tabuleiro.");
    } /* fim ativa: Testar Destruir tabuleiro */

    /* Testar Inicializar tabuleiro*/
    else if(strcmp(ComandoTeste, INICIALIZAR_TABULEIRO_CMD) == 0) {
        numLidos = LER_LerParametros("i", &inxLista);

        if((numLidos != 1) || (!ValidarInxTabuleiro(inxLista, NAO_VAZIO)))
            return TST_CondRetParm;

        TAB_inicializar(vtTabuleiros[inxLista], 'x', 'o');
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
        numLidos = LER_LerParametros("iisi", &inxLista, &linha, StringDado,&CondRetEsp);

        if((numLidos != 4) || (!ValidarInxTabuleiro(inxLista, INDIFERENTE)))
            return TST_CondRetParm;

        coluna = StringDado[0];
        peca = PEC_criar(PecaNormal, 'r');
        CondRet = TAB_setarCasa(vtTabuleiros[inxLista], linha, coluna, peca, 1);

        return TST_CompararInt(CondRetEsp, CondRet, "Condicao de retorno errada ao setar peça");
    } /* fim ativa: Testar Setar casa */

    /* Testar Remover peca*/
    else if(strcmp(ComandoTeste, REMOVER_PECA_CMD) == 0) {
        numLidos = LER_LerParametros("iis", &inxLista, &linha, StringDado);

        if((numLidos != 3) || (!ValidarInxTabuleiro(inxLista, NAO_VAZIO)))
            return TST_CondRetParm;

        coluna = StringDado[0];
        TAB_setarCasa(vtTabuleiros[inxLista], linha, coluna, NULL, 1);
        return TST_CondRetOK;
    } /* fim ativa: Testar Remover peca */

	/* Testar verificador de lista de listas */
	#ifdef _DEBUG

	      else if ( strcmp( ComandoTeste , VER_LISTA_CMD ) == 0 )
         {

            numLidos = LER_LerParametros( "ii" , &inxLista, &CondRetEsp ) ;
            if ( ( numLidos !=2  ) || !ValidarInxTabuleiro( inxLista, INDIFERENTE ))   ////////////////////////////////////////////////////////////////////////////////////77
            {
               return TST_CondRetParm ;
            } 

            return TST_CompararInt(CondRetEsp, TAB_VerificarTabuleiro( vtTabuleiros[ inxLista ] ),"Numero de falhas diferente do esperado") ;

         } /* fim ativa: Testar verificador de lista de listas*/
	#endif   

	/*Posicionar elemento Corrente*/
	 #ifdef _DEBUG

	    else if ( strcmp( ComandoTeste , POSICIONAR_CMD ) == 0 )
		{
        numLidos = LER_LerParametros("iis", &inxLista, &linha, StringDado);

        if((numLidos != 3) || (!ValidarInxTabuleiro(inxLista, NAO_VAZIO)))
            return TST_CondRetParm;

        coluna = StringDado[0];
        PosicionarElementoCorrente(vtTabuleiros[inxLista], linha, coluna);
        return TST_CondRetOK;
    } /* fim ativa: Posicionar elemento corrente */
	#endif 

	/* Deturpar um tabuleiro */
      #ifdef _DEBUG

         else if ( strcmp( ComandoTeste , DETURPAR_CMD ) == 0 )
         {

            numLidos = LER_LerParametros( "iiiis" ,
                               &inxLista , &ModoDeturparTAB, &ModoDeturparLIS, &linha, StringDado ) ;

			if ( ModoDeturparTAB==TAB_DeturparListaPrimaria){
				if( (numLidos != 4 ) || !ValidarInxTabuleiro( inxLista, INDIFERENTE )) ////////////////////////////////////////////////////////////////////////////////////////
				{
                   return TST_CondRetParm ;
				}
				TAB_Deturpar( vtTabuleiros[ inxLista ] , ModoDeturparTAB, linha, -1, ModoDeturparLIS); 
				return TST_CondRetOK ;
			}

            if ( ModoDeturparTAB==TAB_DeturparListaSecundaria){
				if( (numLidos != 5 ) || !ValidarInxTabuleiro( inxLista, INDIFERENTE )) ////////////////////////////////////////////////////////////////////////////////////////
				{
				  return TST_CondRetParm ;
				}

				TAB_Deturpar( vtTabuleiros[ inxLista ] , ModoDeturparTAB, linha, coluna, ModoDeturparLIS) ;

	            return TST_CondRetOK ;
			}
			else
			{
				if( (numLidos != 2 ) || !ValidarInxTabuleiro( inxLista, INDIFERENTE  )) ////////////////////////////////////////////////////////////////////////////////////////
				{
                   return TST_CondRetParm ;
				}
				TAB_Deturpar( vtTabuleiros[ inxLista ] , ModoDeturparTAB, -1, -1, -1); 
				return TST_CondRetOK ;
			}
				
         } /* fim ativa: Deturpar um tabuleiro */
		#endif 

		 /* Verificar vazamento de memória */
      #ifdef _DEBUG

         else if ( strcmp( ComandoTeste , VER_MEMORIA_CMD ) == 0 )
         {
			 numLidos = LER_LerParametros("ii", &inxLista, &CondRetEsp);
			 if((numLidos != 2) || (!ValidarInxTabuleiro(inxLista, INDIFERENTE)))
				return TST_CondRetParm;
			CED_MarcarTodosEspacosInativos();
			TAB_VerificarTabuleiro( vtTabuleiros[ inxLista ] );
			return TST_CompararInt(CondRetEsp, CED_ObterNumeroEspacos( CED_ExibirInativos ),"Numero de falhas diferente do esperado") ;

         } /* fim ativa: Verificar vazamento de memória */
      #endif

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
    } else if(Modo == NAO_VAZIO) {
        if(vtTabuleiros[inxLista] == 0)
            return FALSE;
    }
    return TRUE;
} /* Fim função: TTAB -Validar indice de tabuleiro */

/********** Fim do módulo de implementação: Testtabuleiro  Teste do módulo tabuleiro **********/
