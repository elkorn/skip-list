#!/bin/bash
mkdir -p ./output
for file in $(ls test/test_*.cpp)
do
    out=$(echo "$file" | sed 's/test\///' | sed 's/\.cpp/\.o/g');
    g++ "./$file" -std=c++0x -g -o $(echo "./output/$out");
    echo $out
# g++ ./timing_SkipList.cpp -std=c++0x -g -o ./output/timing_SkipList.o;
# g++ ./test_ExponentialDistribution.cpp -g -o ./output/test_ExponentialDistribution.o -std=c++0x;
# g++ ./test_UniformDistribution.cpp -std=c++0x -g -o ./output/test_UniformDistribution.o;
# g++ ./test_Randomizer.cpp -std=c++0x -g -o ./output/test_Randomizer.o;
# g++ ./test_containment.cpp -std=c++0x -g -o ./output/test_containment.o;
# g++ ./test_creation.cpp -std=c++0x -g -o ./output/test_creation.o;
done