include(FetchContent)
FetchContent_Declare(
  googletest
  GIT_REPOSITORY https://github.com/google/googletest.git
  GIT_TAG        v1.17.0
)
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

# # Now, find_package should work because GTest's configuration files are available
# find_package(GTest REQUIRED)

enable_testing()

add_executable(run_all_tests
    test_color.cpp
    test_ray.cpp
)

# Link Google Test libraries AND your RaytracerCore (header-only) library
target_link_libraries(run_all_tests PRIVATE
    GTest::gtest_main
    RaytracerCore 
)

include(GoogleTest)
gtest_discover_tests(run_all_tests)