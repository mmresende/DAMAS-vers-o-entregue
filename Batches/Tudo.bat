@ECHO  OFF
REM  Gera, Compila e testa os m�dulos lista, peca e tabuleiro, al�m do programa execut�vel DAMAS.exe

if exist TestaTudo.bat goto faz
rem >>> esta' no diretorio ilegal
goto sai

:faz

cls

if exist ..\ferramnt goto Compila&Testa 

Call  Limpa
Call  TestaTudo

goto sai

:Compila&Testa

Call  Limpa
Call  Geratudo
Call  Compilatudo
Call  TestaTudo

:sai