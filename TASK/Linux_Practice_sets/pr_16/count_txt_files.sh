#!/bin/bash
# This script counts the number of .txt files in the current directory.
count=$(ls *.txt 2>/dev/null | wc -l)
echo "Number of .txt files: $count"

