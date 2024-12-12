echo "-----Parameter In Reverse Order------"
i=4
while [ $i -gt 0 ]; 
do
	echo ${!i}
    ((i--))
done

