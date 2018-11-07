cmake_minimum_required(VERSION 3.12)
project(vm_prac)

set(CMAKE_CXX_STANDARD 11)

add_subdirectory(ref_count)
add_subdirectory(mark_sweep)
add_subdirectory(mark_copy)