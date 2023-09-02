#!/bin/bash

read -p "Enter marks : " marks

if [[ $marks -ge 90 ]]
then
	echo "You have A grade"
elif [[ $marks -ge 60 ]]
then
	echo "You have B Grade"
else
	echo "You Fail"
fi

# Switch Case :
echo "Hey choose an option"
echo "a : To see the current date"
echo "b : list all the files in current dir"

read choice

case $choice in
	a) 
		echo "Today Date : "
		date
		;;
	b) ls;;
	*) echo "Non-Valid input"
esac

