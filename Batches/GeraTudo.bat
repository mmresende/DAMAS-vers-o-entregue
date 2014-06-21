 @ECHO OFF
REM Gera script de make de lista, peca, tabuleiro e damas

cls

pushd.

cd ..\ferramnt

gmake/cTESTEPECA		/b..\Composicao	/pgmake
gmake/cTESTETABULEIRO		/b..\Composicao	/pgmake
gmake/cTESTELISTA		/b..\Composicao	/pgmake
gmake/cTESTETABULEIRODEBUG	/b..\Composicao	/pgmake
gmake/cDAMAS			/b..\Composicao	/pgmake
gmake/cDAMASDEBUG		/b..\Composicao	/pgmake

popd