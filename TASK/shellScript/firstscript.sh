#!/bin/bash

read -p 'Enter a number : ' n 
if [ $n -gt 0 ]; then
	echo "$n is a positive number."
elif [ $n -lt 0 ]; then
	echo "$n is a nagetive number."
elif [ $n -eq 0 ]; then
	echo "$n is zero."
else
	echo "Oops! $n is not a number"
fi
