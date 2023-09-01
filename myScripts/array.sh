#!/bin/bash

myArray=(1 2 3 "Sanket" "Disale")

echo "Array Value at 3rd  location : ${myArray[2]}"

# All values from Array

echo "Values : ${myArray[*]}"

# Length of Array : 
echo "Lenght : ${#myArray[*]}"


# Adding Values into the array
myArray+=("New" 40 50 60)

echo "Upadated Array : ${myArray[*]}"

