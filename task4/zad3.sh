#!/bin/bash
script_pid=$(pgrep -f "zad1.sh") 
child_pids=$(pgrep -P $script_pid sleep) 
# Убиваем 3 дочерних процесса с помощью команды kill 
for pid in $child_pids 
do 
    kill $pid 
done