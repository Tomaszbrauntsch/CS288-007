#!/bin/bash

# Tomasz Brauntsch
# CS 288-007
# Professor Ding
# September 26, 2023

read -p "Please enter a directory name: " dirName
if [ ! -d $dirName ]
then
    echo "ERROR: Invalid Directory was entered, please try again!"
    exit 1
else
    cd $dirName
fi
PS3="Please select a file: "
select file in `ls -p | grep -v /`
do
    selectedFile=$file
    break
done


lineNum=`wc -l < $selectedFile`
lineNum=$(( $lineNum - 10 ))
tail -n -10 $selectedFile
read -p "Would you like to display more lines? yes or no: " userInput
while ([[ $userInput = "yes" ]] && [[ $lineNum -gt 0 ]])
do
    head -n $lineNum $selectedFile | tail -n -10
    lineNum=$(($lineNum - 10))
    if !([[ $lineNum -lt 0 ]])
    then
        read -p "Would you like to display more lines? Yes or No: " userInput
    fi  
done
exit 1