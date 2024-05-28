cmake_minimum_required(VERSION 3.20.0)

project(Gem LANGUAGES CXX)

if (WIN32)
	# 生成动态库时，Windows 平台加上这段代码才会输出 lib
	set(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS ON)
elseif()
	# TODO
endif()

# 递归查找 src 目录下所有 .cpp 和 .h
file(GLOB_RECURSE GemSources src/*.cpp src/*.h)

# 生成动态库
add_library(${PROJECT_NAME} SHARED ${GemSources})

# 编译设置
if(MSVC)
    target_compile_options(${PROJECT_NAME} PRIVATE
        $<$<CONFIG:Release>:/MD>
        $<$<CONFIG:Debug>:/MDd>
    )
endif()

# 添加预定义
if (WIN32)
add_compile_definitions(GEM_PLATFORM_WINDOWS
GEM_BUILD_DLL)
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
)

# ---------------------------------------------------------------------------------------------------------------
# 拷贝 DLL 操作
# ---------------------------------------------------------------------------------------------------------------
if (WIN32)
    # 创建文件夹（如果不存在后面的复制命令会有报错，例如：Debug 模式下不会生成 Release 目录，复制 Release 目录中的文件时会报错）
    execute_process(COMMAND ${CMAKE_COMMAND} -E make_directory ${PROJECT_BINARY_DIR}/Debug)
    execute_process(COMMAND ${CMAKE_COMMAND} -E make_directory ${PROJECT_BINARY_DIR}/Release)

    # 原文件路径
    set(ORIGFILE_DEBUG ${PROJECT_BINARY_DIR}/Debug/${PROJECT_NAME}.dll)
    set(ORIGFILE_RELEASE ${PROJECT_BINARY_DIR}/Release/${PROJECT_NAME}.dll)
    # 目标文件路径
    set(TARGET_FOLDER_NAME "Sandbox")
    set(TARGETFILE_DEBUG ${CMAKE_SOURCE_DIR}/${TARGET_FOLDER_NAME}/Debug/${PROJECT_NAME}.dll)
    set(TARGETFILE_RELEASE ${CMAKE_SOURCE_DIR}/${TARGET_FOLDER_NAME}/Release/${PROJECT_NAME}.dll)

    # 添加生成前创建两个 dll 文件（如果不存在，下面复制命令会有报错）
    add_custom_command(TARGET ${PROJECT_NAME} PRE_BUILD
        COMMAND ${CMAKE_COMMAND} -E touch "${ORIGFILE_DEBUG}"
    )
    add_custom_command(TARGET ${PROJECT_NAME} PRE_BUILD
        COMMAND ${CMAKE_COMMAND} -E touch "${ORIGFILE_RELEASE}"
    )

    # 添加生成后事件复制 DLL 到主程序下
    add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E
        copy ${ORIGFILE_DEBUG} ${TARGETFILE_DEBUG}
    )
    add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E 
        copy ${ORIGFILE_RELEASE} ${TARGETFILE_RELEASE}
    )
endif()
# ---------------------------------------------------------------------------------------------------------------