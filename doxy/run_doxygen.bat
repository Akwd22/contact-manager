@echo off
:loop
	cls
	doxygen logic.cfg
	doxygen storage.cfg
	doxygen test_logic.cfg
	doxygen ui.cfg
	echo Appuyez sur une touche pour reg‚n‚rer la documentation...
	pause >NUL
goto loop