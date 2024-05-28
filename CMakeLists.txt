cmake_minimum_required(VERSION 3.20.0)

project(Gem LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)

# 设置 VS 启动项目
if (MSVC)
	set_property(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT Sandbox)
endif()

# 指定 Windows SDK 版本
# set(CMAKE_SYSTEM_VERSION 10.0.22621.0)

# 设置构建类型
set(CMAKE_CONFIGURATION_TYPES "Debug;Release")

# # 优化设置
if (CMAKE_BUILD_TYPE MATCHES Debug)
    set(CMAKE_CXX_FLAGS "-g")
elseif (CMAKE_BUILD_TYPE MATCHES Release)
    set(CMAKE_CXX_FLAGS "-O3")
endif ()

add_subdirectory(Gem)
add_subdirectory(Sandbox)