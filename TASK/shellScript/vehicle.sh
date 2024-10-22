#!/bin/bash
if [ -z $1 ]; then
	rental="*** Unknown vehicle ***"
elif [ -n $1 ]; then
	rental=$1
fi
case $rental in
	"car") echo "For $rental rent is Rs.150 per km/hr.";;
	"van") echo "For $rental rent is Rs.100 per km/hr.";;
	"jeep") echo "For $rental rent is Rs.200 per km/hr.";;
	"bicycle") echo "For $rental rent is Rs.10 per km/hr.";;
	"enfield") echo "For $rental rent is Rs.450 per km/hr.";;
	"thunderbird") echo "For $rental rent is Rs.500 per km/hr.";;
	"*") echo "Sorry, I can not get a $rental rental for you!";;
esac
