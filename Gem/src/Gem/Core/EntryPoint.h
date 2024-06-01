#pragma once
#include "Application.h"

#ifdef GEM_PLATFORM_WINDOWS

extern Gem::Application* Gem::CreateApplication();

int main(int argc, char** argv)
{
	Gem::Log::Init();

	GEM_PROFILE_BEGIN_SESSION("Startup", "GemProfile-Startup.json");
	auto app = Gem::CreateApplication();
	GEM_PROFILE_END_SESSION();

	GEM_PROFILE_BEGIN_SESSION("Runtime", "GemProfile-Runtime.json");
	app->Run();
	GEM_PROFILE_END_SESSION();

	GEM_PROFILE_BEGIN_SESSION("Shutdown", "GemProfile-Shutdown.json");
	delete app;
	GEM_PROFILE_END_SESSION();
}

#endif