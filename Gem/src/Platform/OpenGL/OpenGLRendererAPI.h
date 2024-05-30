#pragma once

#include "Gem/Renderer/RendererAPI.h"

namespace Gem
{
	class OpenGLRendererAPI : public RendererAPI
	{
	public:
		virtual void SetClearColor(const glm::vec4& color) override;
		virtual void Clear() override;

		virtual void DrawIndexed(const Gem::Ref<VertexArray>& vertexArray) override;
	};
}