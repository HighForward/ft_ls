cmake_minimum_required(VERSION 3.10)
project(ft_ls C)

set(CMAKE_C_STANDARD 11)
FILE(GLOB libft libft/*.c)
FILE(GLOB srcs_files srcs/*.c)
add_executable(ft_ls ${srcs_files} ${libft})