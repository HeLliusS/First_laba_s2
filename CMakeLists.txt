cmake_minimum_required(VERSION 4.0)
project(FirstLaba C)

set(CMAKE_C_STANDARD 11)

add_executable(FirstLaba
        main.c
        integer_type.c
        double_type.c
        matrix_type.c
        matrix_functions.c
        tests.c
)
