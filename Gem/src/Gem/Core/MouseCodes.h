#pragma once

#include <iostream>

namespace Gem
{
	typedef enum class MouseCode : uint16_t
	{
		// From glfw3.h
		Button0 = 0,
		Button1 = 1,
		Button2 = 2,
		Button3 = 3,
		Button4 = 4,
		Button5 = 5,
		Button6 = 6,
		Button7 = 7,

		ButtonLast = Button7,
		ButtonLeft = Button0,
		ButtonRight = Button1,
		ButtonMiddle = Button2
	} Mouse;

	inline std::ostream& operator<<(std::ostream& os, MouseCode mouseCode)
	{
		os << static_cast<int32_t>(mouseCode);
		return os;
	}
}

#define GEM_MOUSE_BUTTON_0      ::Gem::Mouse::Button0
#define GEM_MOUSE_BUTTON_1      ::Gem::Mouse::Button1
#define GEM_MOUSE_BUTTON_2      ::Gem::Mouse::Button2
#define GEM_MOUSE_BUTTON_3      ::Gem::Mouse::Button3
#define GEM_MOUSE_BUTTON_4      ::Gem::Mouse::Button4
#define GEM_MOUSE_BUTTON_5      ::Gem::Mouse::Button5
#define GEM_MOUSE_BUTTON_6      ::Gem::Mouse::Button6
#define GEM_MOUSE_BUTTON_7      ::Gem::Mouse::Button7
#define GEM_MOUSE_BUTTON_LAST   ::Gem::Mouse::ButtonLast
#define GEM_MOUSE_BUTTON_LEFT   ::Gem::Mouse::ButtonLeft
#define GEM_MOUSE_BUTTON_RIGHT  ::Gem::Mouse::ButtonRight
#define GEM_MOUSE_BUTTON_MIDDLE ::Gem::Mouse::ButtonMiddle