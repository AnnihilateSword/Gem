#include "gempch.h"
#include "OpenGLContext.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

namespace Gem
{

	OpenGLContext::OpenGLContext(GLFWwindow* windowHandle)
		: m_WindowHandle(windowHandle)
	{
		GEM_CORE_ASSERT(windowHandle, "Window handle is null!")
	}

	void OpenGLContext::Init()
	{
		glfwMakeContextCurrent(m_WindowHandle);
		// ¼ÓÔØ OpenGL º¯Êý
		int status = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
		GEM_CORE_ASSERT(status, "Failed to initialize Glad!");

		GEM_CORE_INFO("OpenGL Info:");
		GEM_CORE_INFO("  Vendor: {0}", (const char*)glGetString(GL_VENDOR));
		GEM_CORE_INFO("  Renderer: {0}", (const char*)glGetString(GL_RENDERER));
		GEM_CORE_INFO("  Version: {0}", (const char*)glGetString(GL_VERSION));
	}

	void OpenGLContext::SwapBuffers()
	{
		glfwSwapBuffers(m_WindowHandle);
	}

}