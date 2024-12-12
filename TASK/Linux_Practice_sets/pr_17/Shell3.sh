#!/bin/bash

# Prompt for a filename
read -p "Enter the filename: " filename

# Check if the file exists
if [ ! -e "$filename" ]; then
    echo "File '$filename' does not exist."
    exit 1
fi

# Check if the user owns the file
if [ ! -O "$filename" ]; then
    echo "You do not own the file '$filename'."
    exit 1
fi

# Check if the file is writable
if [ -w "$filename" ]; then
    echo "The file '$filename' is already writable."
else
    echo "The file '$filename' is not writable. Making it writable..."
    chmod u+w "$filename"
    if [ $? -eq 0 ]; then
        echo "The file '$filename' is now writable."
    else
        echo "Failed to make the file '$filename' writable."
    fi
fi

