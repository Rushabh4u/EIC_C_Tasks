#!/bin/bash
# This script counts down from 8 to 4 using an until loop.
i=8
until [ $i -lt 4 ]; do
    echo $i
    ((i--))
done

