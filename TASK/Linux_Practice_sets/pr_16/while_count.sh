#!/bin/bash
# This script counts from 3 to 7 using a while loop.
i=3
while [ $i -le 7 ]; do
    echo $i
    ((i++))
done

