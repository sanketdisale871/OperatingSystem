#!/bin/bash

for i in Sanket Disale
do
	echo "$i"
done


for i in {1..20}
do
	echo "$i"
done

FILE="names.txt"

for name in $(cat $FILE)
do
	echo $name
done

# Array Using Loop
myArray=( 1 2 3 45 Sanket Disale )
len=${#myArray[*]}

for ((i=0;i<$len;i++))
do
	echo "${myArray[$i]}"
done
