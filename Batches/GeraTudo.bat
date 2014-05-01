 @ECHO OFF
REM Gera script de make de lista, peca e tabuleiro

cls

pushd.

cd ..\ferramnt

gmake/cTESTEPECA	/b..\Composicao	/pgmake
gmake/cTESTETABULEIRO	/b..\Composicao	/pgmake
gmake/cTESTELISTA	/b..\Composicao	/pgmake

popd