#!/bin/bash

read -p "Enter you age : " age
read -p "Enter your country : " country

if [[ $age -ge 18 ]] && [[ $country == "India" ]]
then
	echo "You can vote"
elif [[ age -ge 18 ]]
then
	echo "For voting you must be Indian"
else
	echo "Wait for age 18+"
fi

