#!/bin/bash

echo "Enter no.of clients"
read N

for ((i=1; i <= N; i++ ))
 do    
    gnome-terminal --	./multiClient 127.0.0.1 5000 &  
done  
