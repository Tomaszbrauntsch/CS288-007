#!/bin/bash

# Tomasz Brauntsch
# CS 288-007
# Professor Ding

declare -a unsortedDates
declare -a sortedDates

touch tmpfile.txt # creates a tmp file that will be used for sorting)
IFS=' '
while read -r line 
do
    extracted[${#extracted[@]}]=`echo $line | sed "s/^.*:\s//g" | grep "^[0-9]" | sed "s/,/ /g" | sed "s/.$//g"` # filters ,'s' and .'s from dates (to make it easier to work with) then pumps into an array 
done < "test2-1.txt"

for x in ${extracted[@]}
do
    unsortedDates[${#unsortedDates[@]}]=$x
done


for currDate in $sortedText
do
    sortedDates[${#sortedDates[@]}]=$currDate
done

for x in ${unsortedDates[@]}
do
    echo $x | sed -E "s@(\.|\-)@/@g" >> tmpfile.txt # inserts the unsorted dates into the tmpfile.txt made previously
done

IFS="
"
for text in $(sort -n -t"/" -k3 -k1 -k2 tmpfile.txt)
do
    sortedDates[${#sortedDates[@]}]=$text
done

# for loop to change the sortedDates' format into the correct format
for((i=0;i<${#unsortedDates[@]};i++))
do
    for((j=0;j<${#unsortedDates[@]};j++))
    do
        if [[ $(echo ${sortedDates[$i]} | sed -E "s@\/@@g") == $(echo ${unsortedDates[$j]} | sed -E "s@(\.|\-)@@g") ]]
        then
            sortedDates[$i]=${unsortedDates[$j]}
        fi
    done
done

#prints out all dates in a sorted manner
for dates in ${sortedDates[@]}
do
    echo $dates
done

rm tmpfile.txt