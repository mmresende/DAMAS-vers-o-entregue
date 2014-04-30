@ECHO OFF
REM executa os testes de listaInt, peca e tabuleiro

cls

del ..\scripts\estatisticasInt.estat

..\produto\testeLista		/s..\scripts\TesteListaint	/l..\produto\TesteListaInt	/a..\scripts\estatisticasInt
..\produto\TESTEPECA  		/s..\scripts\Testepeca    	/l..\produto\TestePECA  	/a..\scripts\estatisticasInt
..\produto\TESTETABULEIRO  	/s..\scripts\Testetabuleiro	/l..\produto\Testetabuleiro   	/a..\scripts\estatisticasInt

..\ferramnt\exbestat /e..\scripts\estatisticasInt
