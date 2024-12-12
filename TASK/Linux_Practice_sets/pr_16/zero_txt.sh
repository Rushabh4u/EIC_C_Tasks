#!/bin/bash
# This script checks if there are any .txt files and counts them.
count=$(ls *.txt 2>/dev/null | wc -l)
if [ $count -eq 0 ]; then
    echo "No .txt files found."
else
    echo "Number of .txt files: $count"
fi

