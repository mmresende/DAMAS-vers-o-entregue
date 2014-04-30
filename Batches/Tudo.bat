@ECHO  OFF
REM  Gera, Compila e testa os módulos lista, peca e tabuleiro

if exist TestaTudo.bat goto faz
rem >>> esta' no diretorio ilegal
goto sai

:faz

Cls

Call  Limpatudo
Call  Geratudo
Call  Compilatudo
Call  TestaTudo

:sai