#pragma once
// 由客户端包含，可以看到在 Gem 文件夹之外

#include "Gem/Application.h"
#include "Gem/Layer.h"
#include "Gem/Log.h"

#include "Gem/Core/Timestep.h"

#include "Gem/Input.h"
#include "Gem/KeyCodes.h"
#include "Gem/MouseButtonCodes.h"

#include "Gem/ImGui/ImGuiLayer.h"

// ---Renderer------------------------
#include "Gem/Renderer/Renderer.h"
#include "Gem/Renderer/RenderCommand.h"

#include "Gem/Renderer/Buffer.h"
#include "Gem/Renderer/Shader.h"
#include "Gem/Renderer/Texture.h"
#include "Gem/Renderer/VertexArray.h"

#include "Gem/Renderer/OrthographicCamera.h"
// -----------------------------------

// ---入口点-----------------
#include "Gem/EntryPoint.h"
//--------------------------