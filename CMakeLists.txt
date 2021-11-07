cmake_minimum_required(VERSION 3.20)
project(multithreaded_merge_sort C)

set(CMAKE_C_STANDARD 99)

add_executable(multithreaded_merge_sort main.c)
set(THREADS_PREFER_PTHREAD_FLAG ON)
find_package(Threads REQUIRED)
