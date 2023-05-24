#!/bin/bash

# A script to count the number of flickers in the Wulf's Electroscope footage 
read -p "Enter the name of the TSV file to save the counts: " filename

count=0
start_time=$(date +%s)

echo -e "Count\tElapsed Time (s)" > "$filename"

while true; do

    read -s -n 1 input

    if [ "$input" == "0" ]; then
        break
    fi

    
    count=$((count + 1))


    elapsed_time=$(( $(date +%s) - start_time ))

    echo -e "$count\t$elapsed_time" >> "$filename"

    echo "Count: $count"
done

echo "Counts and elapsed times saved to $filename"

