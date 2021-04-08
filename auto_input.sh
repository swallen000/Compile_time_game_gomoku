#!/usr/bin/env bash



clear
#keyboard='Empty'
IFS=$'\n' read -d '' -r -a lines < input.txt

for i in 0 1 ;

# while :
do
    g++ -O3 -std=c++2a main.cpp -DInput=${lines[i]} -o main
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
    # while :
    # do
    #     read -rsn1 input
    #     if [[ $input == $'\E' ]]; then
    #         read -rsn2 input # read 2 more chars
    #     fi
    #     if [ $input == '[A' ]
    #     then
    #         keyboard='Top'
    #     elif [ $input == '[B' ]
    #     then
    #         keyboard='Down'
    #     elif [ $input == '[C' ]
    #     then
    #         keyboard='Right'
    #     elif [ $input == '[D' ]
    #     then
    #         keyboard='Left'
    #     elif [ $input = " " ] 
    #     then
    #         keyboard='Space'
    #     else
    #         keyboard='None'
    #     fi

    #     if [ $keyboard != 'None' ]
    #     then
    #         break
    #     fi

    # done
    keyboard=${lines[$i]}
    echo ${lines[$i]}
    echo $(./main) > current.txt ;
done