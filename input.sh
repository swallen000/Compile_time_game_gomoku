#!/usr/bin/env bash

clear
IFS=
keyboard='Empty'

while :
do
    g++ -O3 -std=c++2a main.cpp -DInput=$keyboard -o main
    echo $(./main)
    while :
    do
        read -rsn1 input
        if [[ $input == $'\E' ]]; then
            read -rsn2 input # read 2 more chars
        fi
        if [ $input == '[A' ]
        then
            keyboard='Top'
        elif [ $input == '[B' ]
        then
            keyboard='Down'
        elif [ $input == '[C' ]
        then
            keyboard='Right'
        elif [ $input == '[D' ]
        then
            keyboard='Left'
        elif [ $input = " " ] 
        then
            keyboard='Space'
        else
            keyboard='None'
        fi

        if [ $keyboard != 'None' ]
        then
            #echo $keyboard
            break
        fi
    done
    echo $(./main) > current.txt
done