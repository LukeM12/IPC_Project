#!/bin/bash
# use backticks " ` ` " to execute shell command
echo `uname -o`
# executing bash command without backticks
echo uname -o 
echo `gcc ATM.c -o atm`
echo `gcc DBeditor.c -o editor`
echo `gcc DBserver.c -o server`
#x-terminal-emulator -e ./server
gnome-terminal -x ./editor
gnome-terminal -x ./server
gnome-terminal -x ./atm
#xterm -hold -e './server' & 
#xterm -hold -e './atm' & 
