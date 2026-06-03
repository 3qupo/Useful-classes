cmake_minimum_required(VERSION 3.10)
project(UsefulClasses)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

include_directories(${CMAKE_SOURCE_DIR}/include)

set(SRC_DIR ${CMAKE_SOURCE_DIR}/src)

# Файлы библиотеки (без main)
set(LIB_SOURCES
    ${SRC_DIR}/LongNumber.cpp
    ${SRC_DIR}/Matrix.cpp
    ${SRC_DIR}/Graph.cpp
    ${SRC_DIR}/BinarySearchTree.cpp
    ${SRC_DIR}/rsa.cpp
    ${SRC_DIR}/md5.cpp
    ${SRC_DIR}/sha256.cpp
    ${SRC_DIR}/fermat_factorization.cpp
    ${SRC_DIR}/utils.cpp
    ${SRC_DIR}/Generator.cpp
    ${SRC_DIR}/tests.cpp
)

# Отдельно main
add_executable(main ${CMAKE_SOURCE_DIR}/main.cpp ${LIB_SOURCES})