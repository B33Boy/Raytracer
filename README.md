# Raytracer

## Build & Run 

To build and run the project in one step, use the provided scripts:
```bash
./run_clang.sh

./run_gcc.sh
```

If you prefer to build manually (without running), see the setup instructions below.

---

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
### Generate a basic gradient image
```bash
./build/render_ppm > gradient.ppm
```

### Render the scene
```bash
./build/raytracer > raytracer.ppm
```

### Run tests
```bash
./build/tests/run_all_tests
```

or 

```bash
cd ./build/tests
ctest
```