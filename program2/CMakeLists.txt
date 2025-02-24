cmake_minimum_required(VERSION 3.10)
project(program2)

# Указываем стандарт C++
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Подключаем библиотеку
#add_subdirectory(../lib lib)
include_directories(../lib/include)

# Основной исполняемый файл
add_executable(program2 src/main.cpp)
target_link_libraries(program2 mylib pthread)