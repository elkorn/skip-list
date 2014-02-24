#!/bin/bash
mkdir -p ./output
for file in $(ls test/test_*.cpp)
do
    out=$(echo "$file" | sed 's/test\///' | sed 's/\.cpp/\.o/g');
    echo "Starting $file..."
    ($(g++ "./$file" -std=c++0x -g -o $(echo "./output/$out")) &&  echo "$out created!") &
done
echo "Compilation in progress. Please wait for ending messages."