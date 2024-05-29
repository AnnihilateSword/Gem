#pragma once
#include "Gem/Core.h"

namespace Gem
{
	// ‰÷»æAPI¿‡–Õ
	enum class GEM_API RendererAPI
	{
		None = 0, OpenGL = 1
	};

	class GEM_API Renderer
	{
	public:
		inline static RendererAPI GetAPI() { return s_RendererAPI; }
	private:
		static RendererAPI s_RendererAPI;
	};
}