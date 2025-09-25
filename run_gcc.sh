#!/bin/bash

CXX=g++ cmake -B build/build-gcc
cmake --build build/build-gcc
./build/raytracer > raytracer.ppm