#!/bin/bash

CXX=clang++ cmake -B build/build-clang
cmake --build build/build-clang
./build/build-clang/raytracer > raytracer.ppm