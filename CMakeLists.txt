cmake_minimum_required(VERSION 3.15)
project(Raytracer VERSION 0.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# ====== Executables ======
add_executable(raytracer src/main.cpp)
target_include_directories(raytracer PRIVATE include)

# ====== Examples ======
add_executable(render_ppm examples/render_ppm.cpp)
target_include_directories(render_ppm PRIVATE include)

# ====== Tests ======
