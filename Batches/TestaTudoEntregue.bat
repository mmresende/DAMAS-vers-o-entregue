@ECHO OFF
REM executa os testes de lista, peca e tabuleiro

cls

if exist ..\ferramnt\exbestat goto estatistica

..\produto\testeLista		/s..\scripts\TesteLista		/l..\produto\TesteLista		/a..\scripts\estatisticas
..\produto\TESTEPECA  		/s..\scripts\Testepeca    	/l..\produto\TestePECA  	/a..\scripts\estatisticas
..\produto\TESTETABULEIRO  	/s..\scripts\Testetabuleiro	/l..\produto\Testetabuleiro   	/a..\scripts\estatisticas

goto sai

:estatistica

del ..\scripts\estatisticas.estat

..\produto\testeLista		/s..\scripts\TesteLista		/l..\produto\TesteLista		/a..\scripts\estatisticas
..\produto\TESTEPECA  		/s..\scripts\Testepeca    	/l..\produto\TestePECA  	/a..\scripts\estatisticas
..\produto\TESTETABULEIRO  	/s..\scripts\Testetabuleiro	/l..\produto\Testetabuleiro   	/a..\scripts\estatisticas

..\ferramnt\exbestat /e..\scripts\estatisticas

:sai