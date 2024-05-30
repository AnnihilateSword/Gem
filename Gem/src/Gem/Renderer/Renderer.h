#pragma once
#include "Gem/Core.h"

#include "RenderCommand.h"

namespace Gem
{
	class GEM_API Renderer
	{
	public:
		static void BeginScene();
		static void EndScene();

		static void Submit(const std::shared_ptr<VertexArray>& vertexArray);

		inline static RendererAPI::API GetAPI() { return RendererAPI::GetAPI(); }
	};
}