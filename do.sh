#!/bin/bash
# use backticks " ` ` " to execute shell command
echo `uname -o`
# executing bash command without backticks
echo uname -o 
echo `gcc ATM.c -w -lm -o atm`
echo `gcc DBeditor.c -lm -w  -o editor`
echo `gcc DBserver.c -lm -w -o server`
#x-terminal-emulator -e ./server
#xterm -hold -e './server' & 
#xterm -hold -e './atm' & 
