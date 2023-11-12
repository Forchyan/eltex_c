#!/bin/bash

current_processes=$(cat proven_processes.txt)
new_processes=$((current_processes - 3))

if [ $new_processes -lt 0 ]; then
    new_processes=0
fi

echo $new_processes > proven_processes.txt

if [ $current_processes -ge 3 ]; then
    pids=$(pgrep -f "sleep")
    echo "$pids" | head -n 3 | xargs kill
else
    pids=$(pgrep -f "sleep")
    echo "$pids" | head -n $current_processes | xargs kill
fi