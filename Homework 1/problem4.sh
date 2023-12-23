#!/bin/bash

# Tomasz Brauntsch
# CS 288-007
# Professor Ding
# September 25, 2023

declare -A binCount
for binary in `ls /bin | grep "^[a-z].*"`
do
    binCount[${binary:0:1}]=$((binCount[${binary:0:1}] + 1))
done

# the sort is needed because by default it prints z - a and not a - z
(for x in ${!binCount[@]}; do echo $x ${binCount[$x]}; done) | sort