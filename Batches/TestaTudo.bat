@ECHO OFF
REM executa os testes de lista, peca e tabuleiro

cls

if exist ..\ferramnt\exbestat.exe goto estatistica

..\produto\TESTELISTA			/s..\scripts\TesteLista			/l..\produto\TesteLista		
..\produto\TESTEPECA  			/s..\scripts\Testepeca    		/l..\produto\TestePeca  	
..\produto\TESTETABULEIRO  		/s..\scripts\Testetabuleiro		/l..\produto\TesteTabuleiro   
..\produto\TESTETABULEIRODEBUG  	/s..\scripts\Testetabuleiro		/l..\produto\TesteTabuleiroDEBUG
..\produto\TESTETABULEIRODEBUG 		/s..\scripts\TestetabuleiroSemDeturpacoes	/l..\produto\TesteTabuleiroSemDeturpacoes
..\produto\TESTETABULEIRODEBUG 		/s..\scripts\TestetabuleiroComDeturpacoes	/l..\produto\TesteTabuleiroComDeturpacoes

notepad ..\produto\RegistroContadoresComDeturpacoes
goto sai

:estatistica

del ..\scripts\estatisticas.estat

..\produto\TESTELISTA		/s..\scripts\TesteLista		/l..\produto\TesteLista			/a..\scripts\estatisticas
..\produto\TESTEPECA  		/s..\scripts\Testepeca    	/l..\produto\TestePeca  		/a..\scripts\estatisticas
..\produto\TESTETABULEIRO  	/s..\scripts\Testetabuleiro	/l..\produto\TesteTabuleiro   		/a..\scripts\estatisticas
..\produto\TESTETABULEIRODEBUG 	/s..\scripts\Testetabuleiro	/l..\produto\TesteTabuleiroDEBUG   	/a..\scripts\estatisticas
..\produto\TESTETABULEIRODEBUG 	/s..\scripts\TestetabuleiroSemDeturpacoes	/l..\produto\TesteTabuleiroSemDeturpacoes   /a..\scripts\estatisticas
..\produto\TESTETABULEIRODEBUG 	/s..\scripts\TestetabuleiroComDeturpacoes	/l..\produto\TesteTabuleiroComDeturpacoes   	/a..\scripts\estatisticas

..\ferramnt\exbestat /e..\scripts\estatisticas

notepad ..\produto\RegistroContadoresComDeturpacoes

:sai