#!/bin/bash

# Tomasz Brauntsch
# CS 288-007
# Professor Ding
# September 25, 2023

for x in `find $1`
do
    findDupes=`find $1 -type f -name $(basename $x)`
    if [[ `echo $findDupes | grep " "` ]]
    then
        dupes=(`echo ${findDupes}`)
        for index in `seq 1 $((${#dupes[@]}-1))`
        do
            echo "Duplicate File Detected: ${dupes[$index]} is a duplicated of ${dupes[0]}"
            echo "Would you like to deleted the duplicate file? ((y)es or (n)o)"
            read userInt
            if [[ $userInt == "y" ]]
            then
                # echo $userInt ${dupes[$index]}
                rm ${dupes[$index]}
            fi
        done
    fi
done