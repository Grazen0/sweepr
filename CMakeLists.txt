cmake_minimum_required(VERSION 3.29)
project(sweepr)
set(CMAKE_CXX_STANDARD 20)

# https://stackoverflow.com/questions/3201154/automatically-add-all-files-in-a-folder-to-a-target-using-cmake
file(GLOB_RECURSE SOURCE_FILES CONFIGURE_DEPENDS "src/*.h" "src/*.cpp")

add_executable(sweepr ${SOURCE_FILES})

# https://stackoverflow.com/questions/2368811/how-to-set-warning-level-in-cmake
if(MSVC)
  target_compile_options(sweepr PRIVATE /W4)
else()
  target_compile_options(sweepr PRIVATE -Wall -Wextra -Wpedantic)
endif()
