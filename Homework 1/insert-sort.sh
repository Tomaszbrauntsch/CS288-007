#!/bin/bash

# Tomasz Brauntsch
# CS 288-007
# Professor Ding
# September 25, 2023

function sorting(){
    # bubble sort is being used
    for ((i=0; i<${#args[@]} - 1; i++))
    do
        for ((j=0; j<${#args[@]} - $i - 1; j++))
        do
            if [[ $((${args[$j]})) -gt $((${args[(($j + 1))]} )) ]]
            then
                temp=${args[$j]}
                args[$j]=${args[(($j + 1))]}
                args[(($j + 1))]=$temp
            fi
        done
    done
}

for arg in "$@"
do
    args[${#args[@]}]=$arg
done
sorting
echo ${args[@]}