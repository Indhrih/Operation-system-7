cmake_minimum_required(VERSION 3.10)
project(system_info_tool C)

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)

find_package(PkgConfig)
# Исходные файлы
set(SOURCES
    main.c
    args_parser.c
    users.c
    processes.c
    help.c
    file_utils.c
)

# Исполняемый файл
add_executable(system_info_tool ${SOURCES})
