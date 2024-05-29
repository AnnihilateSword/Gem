#pragma once

#include "Gem/Renderer/GraphicsContext.h"

struct GLFWwindow;

namespace Gem
{
	class GEM_API OpenGLContext : public GraphicsContext
	{
	public:
		OpenGLContext(GLFWwindow* windowHandle);

		virtual void Init() override;
		virtual void SwapBuffers() override;
	private:
		GLFWwindow* m_WindowHandle;
	};
}