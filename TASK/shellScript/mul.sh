#!/bin/bash

read -p 'Enter a number : ' n

for i in 1 2 3 4 5 6 7 8 9 10
do
	echo "$n * $i = $(($n * $i))"
done
