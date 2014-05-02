@ECHO  OFF
REM  Verifica se os arquivos do Arcabouç de Teste foram alocados corretamente 

pushd  .

if exist ..\ferramnt goto next1
echo Falta pasta ferramnt

:next1
if exist ..\ferramnt\exbestat.exe goto next2
echo Falta exbestat.exe

:next2
if exist ..\ferramnt\Gmake.exe goto next3
echo Falta Gmake.exe

:next3
if exist ..\ferramnt\Compilebanner.exe goto next4
echo Falta Compilebanner.exe

:next4
if exist ..\Objetos\ArcaboucoTeste.lib goto next5
echo Falta ArcaboucoTeste.lib

:next5
if exist ..\Fontes\TST_ESPC.h goto next6
echo Falta TST_ESPC.h

:next6
if exist ..\Fontes\GENERICO.h goto next7
echo Falta Generico.h

:next7
if exist ..\Fontes\LERPARM.h  goto next8
echo Falta LERPARM.h

:next8
if exist ..\Composicao\Gmake.parm goto next9
echo Falta Gmake.parm
goto sai

:next9
echo Arquivos alocados de forma correta
goto sai

:sai
