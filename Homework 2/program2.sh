#!/bin/bash

# Tomasz Brauntsch
# CS 288-007
# Professor Ding

declare -A people
while read -r line
do
    if [[ `echo $line | cut -d "," -f 3 | sed -E "s@^\s+@@g" | grep -E "^.*\s+.*"` ]] #checks if the city has two or more words
    then
        personName=`echo $line | cut -d "," -f 1`
        personAge=$((2023-`echo $line | cut -d "," -f 2 | sed -E "s@^\s+@@g" | sed -E "s@^(.*)(\-).*\2.*@\1@g"`))
        people[${#people[@]}]=$personName","$personAge
    fi
done < "test2_2.txt"

printf '%s\n' "${people[@]}" | sort -r -t"," -k2 | sed -E "s@,@ is @g" # sorts and prints out the names and ages in the correct format