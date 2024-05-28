cmake_minimum_required(VERSION 3.20.0)

project(imgui LANGUAGES CXX)

file(GLOB_RECURSE ImGuiSources
imconfig.h
imgui.h
imgui.cpp
imgui_draw.cpp
imgui_internal.h
imgui_widgets.cpp
imstb_rectpack.h
imstb_textedit.h
imstb_truetype.h
imgui_demo.cpp
imgui_tables.cpp
)

add_library(${PROJECT_NAME} STATIC ${ImGuiSources})
