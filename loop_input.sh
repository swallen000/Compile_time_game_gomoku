#!/usr/bin/env bash

clear
IFS=
keyboard='Empty'

# change here to see different moves and esults (input-*.txt)
filename='input.txt'

while read value; do 
    g++ -O3 -std=c++2a main.cpp -DInput=$value -o main
    ./main
    res=$?
    if [ $res -ne 0 ]; then
        clear
        echo "      ---------------------------"
        echo "      -                         -"
        if [ $res -eq 12 ]; then
            echo "      -        DRAW!            -"
        fi
        if [ $res -eq 1 ]; then
            echo "      -        O WIN!           -"
        fi
        if [ $res -eq 2 ]; then
            echo "      -        @ WIN!           -"
        fi
        echo "      -                         -"
        echo "      ---------------------------"
        break
    fi
    var="R\"(\n"
    var+=$(./main)
    var+="\n)\""
    echo -e "$var" > current.txt
done < $filename
