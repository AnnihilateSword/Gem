#pragma once
#include "Application.h"

#ifdef GEM_PLATFORM_WINDOWS

extern Gem::Application* Gem::CreateApplication();

void main(int argc, char** argv)
{
	Gem::Log::Init();
	GEM_CORE_WARN("Initialized Log!");
	int a = 528;
	GEM_INFO("Hello! var={0}", a);

	auto app = Gem::CreateApplication();
	app->Run();
	delete app;
}

#endif