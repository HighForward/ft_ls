cmake_minimum_required(VERSION 3.10)
project(ft_ls C)

set(CMAKE_C_STANDARD 11)

add_executable(ft_ls srcs/main.c srcs/error.c srcs/format.c srcs/utils.c)
