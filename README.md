## Raytracer

## Setup
From the root of the project, build with gcc:
```bash
CXX=g++ cmake -B build/build-gcc
cmake --build build/build-gcc
```

From the root of the project, build with clang:
```bash
CXX=clang++ cmake -B build/build-clang
cmake --build build/build-clang
```

## Usage
### Generate a PPM Image
```
./build/render_ppm > gradient.ppm
```

### Run The Raytracer
```
./build/raytracer > raytracer.ppm
```

### Run Tests
```
./build/tests/run_all_tests
```

or 

```
cd ./build/tests
ctest
```