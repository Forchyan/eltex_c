#!/bin/bash

num_processes=10
pids=()
for ((i=0; i < num_processes; i++))
do
    sleep 10 &  
    pids+=($!)  
done

for pid in ${pids[@]}
do
    wait $pid
done

echo ${#pids[@]} > proven_processes.txt
sleep 3600