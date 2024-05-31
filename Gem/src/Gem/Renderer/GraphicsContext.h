#pragma once

#include "Gem/Core/Core.h"

namespace Gem
{
	class GEM_API GraphicsContext
	{
	public:
		virtual void Init() = 0;
		virtual void SwapBuffers() = 0;
	};

}