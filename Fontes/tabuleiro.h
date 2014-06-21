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
*
*  $HA Histórico de evolução: 
*     Versão  Autor    Data     Observações
*      2       hs/mr/rh   17/junho/2014    implementação completa do jogo
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
*  $TC Tipo de dados: TAB Condições de retorno
*
*
*  $ED Descrição do tipo
*     Condições de retorno das funções do tabuleiro
*
***********************************************************************/

typedef enum _TAB_tpCondRet {
	TAB_CondRetOK, /* Concluiu corretamente */
	TAB_CondRetTabuleiroInexistente, /* o tabuleiro não existe */
	TAB_CondRetLinhaInexistente, /* linha fora dos limites do tabuleiro */
	TAB_CondRetColunaInexistente, /*coluna fora dos limites do tabuleiro */
	TAB_CondRetPecaInexistente, /*peca nao existe no tabuleiro */
	TAB_CondRetPecaNaoPertenceJogador, /*a peca nao pertence ao jogador */
	TAB_CondRetPosDestOcupada, /* a posicao de destino ja esta ocupada por outra peca */
	TAB_CondRetErroEstrutura  /* Estrutura do tabuleiro está errada */
} TAB_tpCondRet;

/***********************************************************************
*
*  $TC Tipo de dados: TAB Modos de deturpar
*
*  $ED Descrição do tipo
*     Seleciona a opcao de deturpar o tipo TAB_Tabuleiro ou as listas primaria
*	  (lista de lista) ou secundaria (lista de pecas)
*
***********************************************************************/

#ifdef _DEBUG

typedef enum {
	// Muda tipo tabuleiro
	TAB_DeturpaTipoTabuleiro,
	// Deturpa elemento da lista principal
	TAB_DeturparListaPrimaria,
	// Deturpa elemento da lista secundaria
	TAB_DeturparListaSecundaria,
} TAB_tpModosDeturpacao;

#endif
/***********************************************************************
*
*  $TC Tipo de dados: TAB Modos de deturpar lista
*  
*  $ED Descrição do tipo
*     Seleciona o modo de deturpacao da lista. As opcoes são as mesmas
*	  daquelas definids no módulo lista.h. Para maiores explicações sobre
*	  o que cada um faz, veja o referido módulo
*
***********************************************************************/
#ifdef _DEBUG

typedef enum{
	TAB_EliminarElemento,
    TAB_DeturpaProximoNulo,
    TAB_DeturpaAnteriorNulo,
    TAB_DeturpaProximoLixo,
    TAB_DeturpaAnteriorLixo,
    TAB_DeturpaConteudoNulo,
    TAB_DeturpaTipoNo,
    TAB_LiberaSemFree,
    TAB_PonteiroCorrenteNulo,
    TAB_PonteiroOrigemNulo,
    TAB_PonteiroFimNulo,
	TAB_NumeroElementosNegativo,
	TAB_NumeroElementosNulo,
	TAB_DeturpaNumeroElementos
} TAB_tpModosDeturpacaoLista;

#endif

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
*                O valor retornado é um ponteiro para um tabuleiro 8 por 8, com 
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
*       $P Tabuleiro *tabuleiro - um ponteiro para tabuleiro (lista de lista, 8 por 8)
*
*  $FV Valor retornado 
*
*        retorna TAB_tpCondRetOK, se não houver tabuleiro retorna
*        TAB_tpCondRetTabuleiroInexistente.
*
*
***********************************************************************/
TAB_tpCondRet TAB_destruir(Tabuleiro *tabuleiro);

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
*        $P Tabuleiro *tabuleiro - um ponteiro para tabuleiro (lista de lista, 8 por 8)
*
*  $FV Valor retornado 
*
*        não retorna, simplesmente inicializa o tabuleiro
*        com as pecas nas posições adequadas para um jogo de damas.
*
*
*
***********************************************************************/
void TAB_inicializar(Tabuleiro *tabuleiro, char idJogador1, char idJogador2);

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
*       $P Tabuleiro *tabuleiro - um ponteiro para tabuleiro (lista de lista, 8 por 8)
*
*  $FV Valor retornado 
*
*        Não retorna um valor, imprime na tela de execução o tabuleiro
*        com suas coordenadas de coluna e de linha.
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
*       $P Tabuleiro *tabuleiro - um ponteiro para tabuleiro (lista de lista, 8 por 8)
*       $P int linha - a coordenada da linha no tabuleiro
*       $P int coluna - a coordenada da coluna no tabuleiro
*
*  $FV Valor retornado 
*
*        Utilizando as funções de manipulação do módulo lista retorna
*        o valor associado as entradas de tabuleiro e coordenadas do
*        mesmo. Se a casa especificada não existir, retorna NULL. Isso
*        pode ocorrer devido a linha ou coluna especificadas como
*        parâmetros estarem vazias (criação inadequada de tabuleiro)
*        ou não estarem de acordo com o tamanho do tabuleiro (exemplo:
*        foi passado como parâmetro a linha 9)
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
*      dentro das dimensões do tabuleiro (8x8), a função coloca a peça
*      recebida como parâmetro na casa especificada.  Caso contrário,
*      faz nada.  Também é usada para retirar uma peca de determinada
*      casa, passando O parâmetro NULL.
*
*  $EP Parâmetros
*       $P Tabuleiro *tabuleiro - um ponteiro para tabuleiro (lista de lista, 8 por 8)
*       $P int linha - a coordenada da linha no tabuleiro
*       $P int coluna - a coordenada da coluna no tabuleiro
*       $P Peca *peca - O parametro peca pode ser NULL, caso em que a funcao destruirá a peca
*		        localizada na casa epecificada. Se nao houver peca nessa casa, faz nada.
*                        Se não for NULL substitui o valor no tabuleiro pelo valor de peca
* $FV Valor retornado 
*
*       retorna TAB_tpCondRetOK. Se o tabuleiro for NULL retorna
*       TAB_tpCondRetTabuleiroInexistente. Caso a linha esteja fora do
*       limite do tabuleiro retorna TAB_tpCondRetLinhaInexistente e
*       caso a coluna esteja fora do limite do tabuleiro retorna
*       TAB_tpCondRetColunaInexistente.
*
***********************************************************************/
TAB_tpCondRet TAB_setarCasa(Tabuleiro *tabuleiro, int linha, char coluna, Peca *peca, int limpar);

/***********************************************************************
*
*  $FC Função: TAB  &Verifica o vencedor
*
*  $ED Descrição da função Função verifica se algum jogador ja ganhou
*     o jogo de damas ou não, isso ocorre pela verificação de peças de
*     cada jogador em jogo, se as pecas de algum jogador não existe
*     mais então ele perdeu.
*
*  $EP Parâmetros
*       $P Tabuleiro *tabuleiro - um ponteiro para tabuleiro (lista de lista, 8 por 8)
*       $P Char idJogador1 - representa um identificar do jogador 1  
*       $P Char idJogador2 - representa um identificar do jogador 2
*      

*
***********************************************************************/
int TAB_verificaVencedor(Tabuleiro *tabuleiro, char idJogador1, char idJogador2);

#ifdef _DEBUG
/***********************************************************************
*
*  $FC Função: TAB  &Verificar o tabuleiro
*
*  $ED Descrição da função
*     Função da interface de teste.
*     Verifica completamente a estrutura de tabuleiro, sendo ela uma lista de listas.
*     Também marca todos os espaços por ela ocupados.
*
*  $EP Parâmetros
*       $P Tabuleiro *tabuleiro - um ponteiro para tabuleiro (lista de lista, 8 por 8)
*
*  $FV Valor retornado
*	  Retorna TAB_CondRetOK, caso não encontre falhas na estrutura, ou
*     TAB_CondRetErroEstrutura, caso contrário
*
***********************************************************************/
TAB_tpCondRet TAB_VerificarTabuleiro(Tabuleiro *tabuleiro);

/***********************************************************************
*
*  $FC Função: TAB  &Deturpar tabuleiro
*
*  $ED Descrição da função
*	  Função da interface de teste.
*     Corrompe elementos específicos da estrutura do tabuleiro.
*     Essa função destina-se a preparar os cenários de teste dos
*     casos de teste utilizados ao testar os verificadores estruturais
*     do tabuleiro.
*     Esta função não tem proteção contra erros de uso, consequentemente
*     poderá levar o programa a ser cancelado pelo sistema operacional.
*     Caso a deturpação seja referente ao tipo TAB_tabuleiro
*	  os parâmetros linha, coluna e ModoDeturparLista devem ser 
*	  inicializados com qualquer valor, pois serão ignorados.
*	  Caso a deturpação seja referente a lista primária (que é a lista de
*	  listas) o parâmetro coluna deve ser inicializado com qualquer valor, 
*	  pois será ignorado.
*	  Caso contrário, os parâmetros linha, coluna e ModoDeturparLista
*	  identificam como a deturpação da lista secundária (lista de peças) 
*	  deve ser feita.
*
*  $EP Parâmetros
*     $P tabuleiro    - tabuleiro a ser deturpado 
*     $P ModoDeturpar - identifica como deve ser feita a deturpação
*                       TAB_tpModosDeturpacao identifica os modos de
*                       deturpação conhecidos
*     $P linha        - identifica a linha do tabuleiro onde dee ser feita 
*						a deturpação
*						Será ignorado caso a deturpação seja referente ao tipo
*						TAB_Tabuleiro, e não a uma lista
*     $P coluna		  - identifica a coluna do tabuleiro onde dee ser feita 
*						a deturpação
*						Será ignorado caso a deturpação seja referente ao tipo
*						TAB_Tabuleiro ou a lista primária, e não a uma lista
*						secundária
*     $P ModoDeturparLista - Caso a deturpação seja referente a alguma das 
*							 listas (primária ou secundária) identifica como
* 							 deve ser feita a deturpação
*							 TAB_tpModosDeturpacaoLista identifica os modos de
*							 deturpação conhecidos
*							 Será ignorado caso a deturpação seja referente ao tipo
*							 TAB_Tabuleiro, e não a uma lista
***********************************************************************/
void TAB_Deturpar(Tabuleiro *tabuleiro, TAB_tpModosDeturpacao ModoDeturpar, int linha, char coluna, TAB_tpModosDeturpacaoLista ModoDeturparLista);

/***************************************************************************
*
*  Função: TAB  &Posicionar Elemento Corrente
*
*  $ED Descrição da função
*	  Função da interface de teste.
*     Posiciona o elemento Corrente da lista de listas (tabuleiro)
*	  na casa desejada pelo usuário.
*     Essa função destina-se a preparar os cenários de teste dos
*     casos de teste utilizados ao testar os verificadores estruturais
*     do tabuleiro.
*
*  $EP Parâmetros
*     $P tabuleiro    - ponteiro para o tabuleiro
*     $P linha e coluna - identificam a casa do tabuleiro onde se
*	     deseja que fique posicionado o elemento corrente
*  ****/
void PosicionarElementoCorrente(Tabuleiro *tabuleiro, int linha, char coluna);

#endif

#endif
