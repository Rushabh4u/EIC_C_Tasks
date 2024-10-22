#!/bin/bash
clear
echo -e "Current date is \c";date
echo -e "      calender"
cal
read -s -p "Enter Password : " my_password
echo
echo "Your password - $my_password"
exit 0
