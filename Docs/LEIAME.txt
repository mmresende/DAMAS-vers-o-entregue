Damas
=====

Jogo de damas desenvolvido para a disciplina Programação Modular da PUC-RIO.

Desenvolvido por:

- Henrique Santiago
- Marcelo Resende
- Rafael Haeusler


Prof. Alessandro Garcia, e-mail: afgarcia@inf.puc-rio.br

Assistente Danyllo Albuquerque, e-mail: dwalbuquerque@inf.puc-rio.br

Assistente Willian Oizumi, e-mail: woizumi@inf.puc-rio.br


Apresentação
===============================================================================
Esse texto descreve o conteúdo do arquivo INF1301-Trab2-HSMRRH.zip, que contém 
os arquivos necessários para a implementação e teste dos módulos lista, peça e 
tabuleiro de um jogo de damas.



Instalação
===============================================================================
Crie um diretório no qual você deseja instalar o arquivo. Dezipe o arquivo 
INF1301-Trab2-HSMRRH.zip assegurando que sejam gerados os sub-diretórios contidos
no arquivo.zip. Isto criará a estrutura de diretórios utilizada e copiará:

-os códigos fonte dos módulos;
-os códigos fonte das funções de controle de teste específicas de cada módulo; 
-os scripts de teste dos módulos desenvolvidos;
-os arquivos batch (.bat) que auxiliam na compilação e teste dos construtos;
-os scripts de composição (.comp), de make e arquivos script .build para o linker
gerados pelo utilitário GMAKE;
-os programas executáveis TesteLista.exe, TestePeca.exe e TesteTabuleiro.exe
-arquivos .pdf com modelo físico da estrutura completa e a arquitetura do programa;
-arquivos .txt com os relatórios de cada componente do grupo.


Estrutura de diretórios
================================================================================
Os seguintes diretórios são gerados ao dezipar:

-Batches: contém arquivos .bat que auxiliam na realização dos testes e na (re)compilação
	  dos construtos.

-Composicao: contém os arquivos .comp com os scripts de composição e .make com os scripts
	     de make dos módulos. Arquivos do formato .list também aparecerão aqui caso
 	     sejam rodados os batches corretos.

-Docs: contém arquivos .pdf e .txt, com os relatórios dos componentes do grupo, modelo fí-
       sico da estrutura implementada, seu exemplo físico, a arquitetura do programa de
       damas e sua especificação. Além deste documento (LEIAME).

-Fontes: contém os arquivos de código fonte (.c e .h) do programa

-Objetos: contém arquivos script .build para o linker. Arquivos do formato .obj também apa-
          recerão aqui caso sejam rodados os batches corretos.

-Produto: contém os executáveis gerados após a compilação dos módulos. Eles implementam os
	  testes dos módulos. Os resultados dos testes (arquivos .txt e .err) irão aparecer
	  aqui depois que os testes forem rodados.

-Scripts: contém os scripts de teste (.script). O arquivo estatisticas (.estat) será gerado
    	  aqui após a execução dos testes.


Documentação
=================================================================================
A pasta Docs contém os seguintes documentos:

-modelo_fisico.pdf: contém o modelo físico da estrutura completa (Lista, tabuleiro e peças).

-exemplo_modelo_físico.pdf: contém o exemplo físico da estrutura completa.

-especificacao.pdf: contém a especificação de requisitos do Programa Jogo de Damas

-Arquitetura_damas.pdf: contém a arquitetura do Programa Jogo de Damas

-LEIAME.txt: o presente documento

-relatorio-nome.txt: o relatório de cada membro do grupo


Execução dos Testes
=================================================================================
Os testes devem ser executados a partir da janela de linha de comando do Windows (CMD).
É provável que seja necessário alterar parâmetros de ambiente requeridos pelo compilador.
O batch vsvars32.bat, disponibilizado pelo visual studio deve ser executado antes de executar
os batches.
Há duas formas de executar os testes:

1. Na pasta Produto (onde estão os executáveis), execute o comando:    TESTE*.exe/S..scripts\Teste*.script.
   TESTE*.exe e Teste*.script devem corresponder aos arquivos .exe que se quer testar e seu       respectivo script de teste, existente na pasta script.
   
   EXEMPLO: TESTEPECA/s..\scripts\Testepeca

2. Execute o batch TestaTudo da pasta batches. Ele executará os testes dos módulos lista, peca 
   e tabuleiro a partir dos scripts testelista.script, testepeca.script e testetebuleiro.script, 
   respectivamente. Também irá gerar:
   - o arquivo estatisticas.estat na pasta Scripts;
   - os relatórios dos testes (.txt) respectivos: TesteLista.txt, TestePECA.txt e Testetabuleiro.txt
     na pasta Produto;
   - ????? os error log (.err) respectivos: TesteLista.err, TestePECA.err e Testetabuleiro.err, 
     além de tudo.err, que mostra o resultado da compilação de todos os construtos na pasta Produto.
     ??????


(Re)compilação através dos batches
==================================================================================
A pasta batches possui diversos batches que auxiliam na (re)compilação e utilização
do arquivo. Ao (re)compilar o programa usando os batches, é necessário usar certos 
arquivos fornecidos pelo Arcabouço de Apoio ao Teste Automatizado para Programas Re-
digidos em C (Autotest). Os passos a seguir elucidam esse processo:

-Na pasta Objetos, coloque a biblioteca do arcabouço: ArcaboucoTeste.lib

-Na pasta Fontes, coloque os arquivos header(.h): TST_ESPC.h, LERPARM.h e GENERICO.h. 

-Na pasta Composicao, coloque o arquivo Gmake.parm ????????????????????????

-Crie no diretório uma pasta de nome "ferramnt" (tudo minúsculo) e nela coloque os 
 executáveis Gmake.exe, Compilebanner.exe e exbestat.exe

Os batches disponibilizados são os seguintes:

-Compila.bat:
-CompilaTudo.bat:
-GeraMake.bat:
-GeraTudo.bat:
-LimpaTudo.bat:
-TestaTudo.bat:
-Tudo.bat: