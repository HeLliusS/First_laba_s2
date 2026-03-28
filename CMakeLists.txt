cmake_minimum_required(VERSION 4.0)
project(FirstLaba C)

set(CMAKE_C_STANDARD 11)

set(COMMON_SOURCES
        matrix_type.c
        integer_type.c
        double_type.c
        matrix_functions.c
)


add_executable(matrix_app main.c ${COMMON_SOURCES})

add_executable(matrix_tests tests.c ${COMMON_SOURCES})

