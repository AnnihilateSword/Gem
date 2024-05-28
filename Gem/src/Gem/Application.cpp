#include "gempch.h"
#include "Application.h"

#include "Gem/Events/ApplicationEvent.h"
#include "Gem/Log.h"

namespace Gem
{
	Application::Application()
	{
	}

	Application::~Application()
	{
	}

	void Application::Run()
	{
		WindowResizeEvent e(1280, 720);
		if (e.IsInCategory(EventCategoryApplication))
		{
			GEM_TRACE(e.ToString());
		}
		if (e.IsInCategory(EventCategoryInput))
		{
			GEM_TRACE(e.ToString());
		}

		while (true);
	}
}