cmake_minimum_required(VERSION 3.10)
project(system_info_tool C)

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)

# Исходные файлы
set(SOURCES
    src/main.c
    src/args_parser.c
    src/users.c
    src/processes.c
    src/help.c
    src/file_utils.c
)

# Исполняемый файл
add_executable(system_info_tool ${SOURCES})
