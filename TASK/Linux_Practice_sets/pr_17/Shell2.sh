file1=$1
file2=$2

if test -e "${file1}";
 then
echo "${file1}  exists."
else
	echo " ${file1}  is Not  Exist"
fi

if test -e "${file2}";
 then
echo "${file2}  exists."
else
	echo " ${file2}  is Not  Exist"
fi

