cmake_minimum_required(VERSION 3.19)
project(Raytracer VERSION 0.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

if(CMAKE_CXX_COMPILER_ID STREQUAL "Clang")
    message(STATUS "Using Clang")
    set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
elseif(CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
    message(STATUS "Using GCC")
endif()

add_compile_options(-Wall -Wextra -Wpedantic)

# ====== Header-Only Library ======
# INTERFACE libraries do not produce any build output (no .lib/.so/.dll).
# They only propagate usage requirements (like include directories).
add_library(RaytracerCore INTERFACE)

# Any target linking to RaytracerCore will get 'include' added to its include paths.
target_include_directories(RaytracerCore INTERFACE include)


# ====== Executables ======
add_executable(raytracer src/main.cpp)
target_link_libraries(raytracer PRIVATE RaytracerCore)

# ====== Examples ======
add_executable(render_ppm examples/render_ppm.cpp)
target_link_libraries(render_ppm PRIVATE RaytracerCore)

# ====== Tests ======
enable_testing()
add_subdirectory(tests)