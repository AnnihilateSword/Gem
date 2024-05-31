cmake_minimum_required(VERSION 3.20.0)

project(Gem LANGUAGES CXX)

if (WIN32)
	# 生成动态库时，Windows 平台加上这段代码才会输出 lib
	set(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS ON)
elseif()
	# TODO
endif()

# 递归查找 src 目录下所有 .cpp 和 .h
file(GLOB_RECURSE GemSources src/*.cpp src/*.h
vendor/stb_image/stb_image.h
vendor/stb_image/stb_image.cpp)

# 生成静态库
add_library(${PROJECT_NAME} STATIC ${GemSources})

# 编译设置
if(MSVC)
    target_compile_options(${PROJECT_NAME} PRIVATE
        $<$<CONFIG:Release>:/MT>
        $<$<CONFIG:Debug>:/MTd>
    )
endif()

# 添加预定义
if (WIN32)
add_compile_definitions(
#GEM_PLATFORM_WINDOWS
# 抑制警告
#_SILENCE_STDEXT_ARR_ITERS_DEPRECATION_WARNING
)
endif()

# 根据构建配置添加预定义
target_compile_definitions(${PROJECT_NAME} PRIVATE
# 生成器扩展
$<$<CONFIG:Debug>:GEM_DEBUG>
)
target_compile_definitions(${PROJECT_NAME} PRIVATE
$<$<CONFIG:Release>:GEM_RELEASE>
)

# 设置预编译头
target_precompile_headers(${PROJECT_NAME} PRIVATE ${CMAKE_CURRENT_LIST_DIR}/src/gempch.h)

# include 目录
target_include_directories(${PROJECT_NAME}
PUBLIC
${CMAKE_CURRENT_LIST_DIR}/src
${CMAKE_CURRENT_LIST_DIR}/vendor/spdlog/include
${CMAKE_CURRENT_LIST_DIR}/vendor/glfw/include
${CMAKE_CURRENT_LIST_DIR}/vendor/glad/include
${CMAKE_CURRENT_LIST_DIR}/vendor/imgui
${CMAKE_CURRENT_LIST_DIR}/vendor/glm
${CMAKE_CURRENT_LIST_DIR}/vendor/stb_image
)

# 添加子目录
# glfw
add_subdirectory(${CMAKE_CURRENT_LIST_DIR}/vendor/glfw)

# glad
add_subdirectory(${CMAKE_CURRENT_LIST_DIR}/vendor/glad)

# imgui
add_subdirectory(${CMAKE_CURRENT_LIST_DIR}/vendor/imgui)

# 如果是项目会优先引用项目，如果不是则链接库
target_link_libraries(${PROJECT_NAME} glfw opengl32 glad imgui)