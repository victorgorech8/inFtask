cmake_minimum_required(VERSION 3.10)
project(program1)

# Указываем стандарт C++
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Подключаем библиотеку
#add_subdirectory(../lib lib)
include_directories(../lib/include)

# Основной исполняемый файл
add_executable(program1 src/main.cpp)
target_link_libraries(program1 mylib pthread)