## Raytracer

## Setup
From the root of the project:
```bash
cmake -B build -S .
cmake --build build
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