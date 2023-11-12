#!/bin/bash

num_processes=10
for ((i=1; i <= num_processes; i++))
do
    sleep 100 &
    echo $i > proven_processes.txt
done

sleep 3600