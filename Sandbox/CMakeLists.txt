cmake_minimum_required(VERSION 3.20.0)

project(Sandbox LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)

# 递归查找 src 目录下所有 .cpp 和 .h
file(GLOB_RECURSE SandboxSources src/*.cpp src/*.h)

# 生成可执行文件
add_executable(${PROJECT_NAME} ${SandboxSources})

# 编译设置
if(MSVC)
    target_compile_options(${PROJECT_NAME} PRIVATE
        $<$<CONFIG:Release>:/MD>
        $<$<CONFIG:Debug>:/MDd>
    )
endif()

# 添加预定义
if (WIN32)
    add_compile_definitions(GEM_PLATFORM_WINDOWS)
endif()

target_compile_definitions(${PROJECT_NAME} PRIVATE
# 生成器扩展
$<$<CONFIG:Debug>:GEM_DEBUG>
)
target_compile_definitions(${PROJECT_NAME} PRIVATE
$<$<CONFIG:Release>:GEM_RELEASE>
)

# include 目录
target_include_directories(${PROJECT_NAME}
PUBLIC
${CMAKE_SOURCE_DIR}/Gem/src)

# 如果是项目会优先引用项目，如果不是则链接库
target_link_libraries(${PROJECT_NAME} Gem)