cmake_minimum_required(VERSION 3.10)
project(mylib)

# Указываем стандарт C++
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Динамическая библиотека
add_library(mylib SHARED src/mylib.cpp)
target_include_directories(mylib PUBLIC include)