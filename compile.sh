#!/bin/bash
mkdir -p ./output
g++ ./test_SkipList.cpp -std=c++0x -g -o ./output/test_SkipList.o;
g++ ./timing_SkipList.cpp -std=c++0x -g -o ./output/timing_SkipList.o;
g++ ./test_ExponentialDistribution.cpp -g -o ./output/test_ExponentialDistribution.o -std=c++0x;
g++ ./test_UniformDistribution.cpp -std=c++0x -g -o ./output/test_UniformDistribution.o;
g++ ./test_Randomizer.cpp -std=c++0x -g -o ./output/test_Randomizer.o;
g++ ./test_containment.cpp -std=c++0x -g -o ./output/test_containment.o;
