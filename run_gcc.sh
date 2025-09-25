#!/bin/bash

CXX=g++ cmake -B build/build-gcc
cmake --build build/build-gcc
./build/build-gcc/raytracer > raytracer.ppm