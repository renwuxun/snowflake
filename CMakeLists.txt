cmake_minimum_required(VERSION 3.12)
project(snowflake C)

set(CMAKE_C_STANDARD 99)

add_library(snowflake snowflake.c snowflake.h)