#!/bin/bash

# Tomasz Brauntsch
# CS 288-007
# Professor Ding
# September 25, 2023

function reverse(){
    # bubble sort is being used
    for ((i=0; i<${#dirFiles[@]} - 1; i++))
    do
        for ((j=0; j<${#dirFiles[@]} - $i - 1; j++))
        do
            if [[ ${dirFiles[$j]} < ${dirFiles[(($j + 1))]} ]]
            then
                temp=${dirFiles[$j]}
                dirFiles[$j]=${dirFiles[(($j + 1))]}
                dirFiles[(($j + 1))]=$temp
            fi
        done
    done
}

IFS='
'
for file in  `ls $1* | sed "s:^.*$1::g"` # using :'s for sed since the arg contains /'s'
do
    dirFiles[${#dirFiles[@]}]=$file
done
reverse
echo ${dirFiles[@]}