#!/bin/bash
mkdir -p ./output
files=$(ls test/*.cpp)
total=$(echo $files | sed -e 's/\s/\n/g' | wc -l)
compiled=0

for file in $files
do
    out=$(echo "$file" | sed 's/test\///' | sed 's/\.cpp/\.o/g');
    ($(g++ "./$file" -std=c++0x $1 -o $(echo "./output/$out")) && echo "$out created.") &
done
echo "Compilation in progress. Please wait for ending messages."