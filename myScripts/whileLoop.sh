#!/bin/bash

cnt=0
limit=10

while [[ cnt -le limit ]]
do
	echo "Val : ${cnt}"
	let cnt++
done

