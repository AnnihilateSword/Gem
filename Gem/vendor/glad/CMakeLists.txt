cmake_minimum_required(VERSION 3.20.0)

project(glad LANGUAGES CXX)

file(GLOB_RECURSE gladSources src/*.c)

# 生成静态库
add_library(glad
STATIC
${gladSources}
)

# include 目录
target_include_directories(${PROJECT_NAME}
PRIVATE
${CMAKE_CURRENT_LIST_DIR}/include
)