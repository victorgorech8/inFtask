cmake_minimum_required(VERSION 3.10)
project(CppProject)

# Явное включение политики CMP0002
if(POLICY CMP0002)
  cmake_policy(SET CMP0002 NEW)
endif()

# Указываем стандарт C++
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Подключаем библиотеку
add_subdirectory(lib)

# Подключаем программу №1
add_subdirectory(program1)

# Подключаем программу №2
add_subdirectory(program2)