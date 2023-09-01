#!/bin/bash

# Script to show how to use variables
name="Sanket"
age="20"
echo "My name : $name and Age : $age"


# Var to store the ouptut of a command
HOSTNAME=$(hostname)
echo "Name of this machine is : $HOSTNAME "


# Const variable
readonly clg="VIT,Pune"
echo "My college : $clg "


