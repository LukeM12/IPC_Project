#!/bin/bash
# use backticks " ` ` " to execute shell command
echo `uname -o`
# executing bash command without backticks
echo uname -o 
echo `gcc ATM.c -o atm`
echo `gcc DBeditor.c -o editor`
echo `gcc DBserver.c -o server`
