@ECHO  OFF
REM  Compila os testes de lista, peca e tabuleiro, a partir dos respectivos arquivos make. 
REM  Compila o programa executável damas

pushd .

cd..\ferramnt

del ..\produto\*.err
del ..\produto\*.obj
del ..\produto\TESTELISTA.exe
del ..\produto\TESTEPECA.exe
del ..\produto\TESTETABULEIRO.exe
del ..\produto\TESTETABULEIRODEBUG.exe
del ..\produto\DAMAS.exe
del ..\produto\DAMASDEBUG.exe

REM compila para DEBUG

del ..\objetos\*.obj
nmake /F..\composicao\DAMASDEBUG.make 
nmake /F..\composicao\TESTETABULEIRODEBUG.make 
del ..\objetos\*.obj

REM compila arquivos sem DEBUG

nmake /F..\composicao\TESTELISTA.make  
nmake /F..\composicao\TESTEPECA.make   
nmake /F..\composicao\TESTETABULEIRO.make   
nmake /F..\composicao\DAMAS.make  

copy  ..\produto\*.err ..\produto\tudo.err

notepad ..\produto\tudo.err

popd
