cmake_minimum_required(VERSION 2.8)

project(tables)
include_directories(include gtest)

# BUILD
add_subdirectory(samples)
add_subdirectory(test)
add_subdirectory(gtest)
add_subdirectory(polynoms)