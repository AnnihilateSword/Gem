cmake_minimum_required(VERSION 3.20.0)

project(glad LANGUAGES CXX)

file(GLOB_RECURSE gladSources src/*.c)

# 生成静态库
add_library(glad
STATIC
${gladSources}
)

# 编译设置
if(MSVC)
    target_compile_options(${PROJECT_NAME} PRIVATE
        $<$<CONFIG:Release>:/MT>
        $<$<CONFIG:Debug>:/MTd>
    )
endif()

# include 目录
target_include_directories(${PROJECT_NAME}
PRIVATE
${CMAKE_CURRENT_LIST_DIR}/include
)