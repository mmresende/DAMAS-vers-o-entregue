@ECHO OFF
REM executa os testes de lista, peca e tabuleiro

cls

if exist ..\ferramnt\exbestat goto estatistica

..\produto\TESTELISTA		/s..\scripts\TesteLista		/l..\produto\TesteLista		/a..\scripts\estatisticas
..\produto\TESTEPECA  		/s..\scripts\Testepeca    	/l..\produto\TestePeca  	/a..\scripts\estatisticas
..\produto\TESTETABULEIRO  	/s..\scripts\Testetabuleiro	/l..\produto\TesteTabuleiro   	/a..\scripts\estatisticas

goto sai

:estatistica

del ..\scripts\estatisticas.estat

..\produto\TESTELISTA		/s..\scripts\TesteLista		/l..\produto\TesteLista		/a..\scripts\estatisticas
..\produto\TESTEPECA  		/s..\scripts\Testepeca    	/l..\produto\TestePeca  	/a..\scripts\estatisticas
..\produto\TESTETABULEIRO  	/s..\scripts\Testetabuleiro	/l..\produto\TesteTabuleiro   	/a..\scripts\estatisticas

..\ferramnt\exbestat /e..\scripts\estatisticas

:sai