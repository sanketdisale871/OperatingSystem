#!/bin/bash


read -p "Enter Your Name : " name
echo "Your name : $name"

num1=5
num2=4

# By storing variable values 

let mult=$num1*$num2
echo "Multiplication :$mult"

# By doing itself
echo "Multiplication :$(($num1*$num2)) "

