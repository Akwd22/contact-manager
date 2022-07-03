#!/bin/sh

while true
do
	clear
	doxygen logic.cfg
	doxygen storage.cfg
	doxygen test_logic.cfg
	doxygen ui.cfg
	echo Appuyez sur une touche pour regénérer la documentation...
	read NONE
done