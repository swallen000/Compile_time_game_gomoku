#!/usr/bin/env bash



clear
IFS=
keyboard='Empty'

chr() {
  [ "$1" -lt 256 ] || return 1
  printf "\\$(printf '%03o' "$1")"
}

while :
do
    g++ -O3 -std=c++2a main.cpp -DInput=$keyboard -o main
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