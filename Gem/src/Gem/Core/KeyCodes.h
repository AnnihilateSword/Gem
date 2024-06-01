#pragma once

namespace Gem
{
	typedef enum class KeyCode : uint16_t
	{
		// From glfw3.h
		Space = 32,
		Apostrophe = 39, /* ' */
		Comma = 44, /* , */
		Minus = 45, /* - */
		Period = 46, /* . */
		Slash = 47, /* / */

		D0 = 48, /* 0 */
		D1 = 49, /* 1 */
		D2 = 50, /* 2 */
		D3 = 51, /* 3 */
		D4 = 52, /* 4 */
		D5 = 53, /* 5 */
		D6 = 54, /* 6 */
		D7 = 55, /* 7 */
		D8 = 56, /* 8 */
		D9 = 57, /* 9 */

		Semicolon = 59, /* ; */
		Equal = 61, /* = */

		A = 65,
		B = 66,
		C = 67,
		D = 68,
		E = 69,
		F = 70,
		G = 71,
		H = 72,
		I = 73,
		J = 74,
		K = 75,
		L = 76,
		M = 77,
		N = 78,
		O = 79,
		P = 80,
		Q = 81,
		R = 82,
		S = 83,
		T = 84,
		U = 85,
		V = 86,
		W = 87,
		X = 88,
		Y = 89,
		Z = 90,

		LeftBracket = 91,  /* [ */
		Backslash = 92,  /* \ */
		RightBracket = 93,  /* ] */
		GraveAccent = 96,  /* ` */

		World1 = 161, /* non-US #1 */
		World2 = 162, /* non-US #2 */

		/* Function keys */
		Escape = 256,
		Enter = 257,
		Tab = 258,
		Backspace = 259,
		Insert = 260,
		Delete = 261,
		Right = 262,
		Left = 263,
		Down = 264,
		Up = 265,
		PageUp = 266,
		PageDown = 267,
		Home = 268,
		End = 269,
		CapsLock = 280,
		ScrollLock = 281,
		NumLock = 282,
		PrintScreen = 283,
		Pause = 284,
		F1 = 290,
		F2 = 291,
		F3 = 292,
		F4 = 293,
		F5 = 294,
		F6 = 295,
		F7 = 296,
		F8 = 297,
		F9 = 298,
		F10 = 299,
		F11 = 300,
		F12 = 301,
		F13 = 302,
		F14 = 303,
		F15 = 304,
		F16 = 305,
		F17 = 306,
		F18 = 307,
		F19 = 308,
		F20 = 309,
		F21 = 310,
		F22 = 311,
		F23 = 312,
		F24 = 313,
		F25 = 314,

		/* Keypad */
		KP0 = 320,
		KP1 = 321,
		KP2 = 322,
		KP3 = 323,
		KP4 = 324,
		KP5 = 325,
		KP6 = 326,
		KP7 = 327,
		KP8 = 328,
		KP9 = 329,
		KPDecimal = 330,
		KPDivide = 331,
		KPMultiply = 332,
		KPSubtract = 333,
		KPAdd = 334,
		KPEnter = 335,
		KPEqual = 336,

		LeftShift = 340,
		LeftControl = 341,
		LeftAlt = 342,
		LeftSuper = 343,
		RightShift = 344,
		RightControl = 345,
		RightAlt = 346,
		RightSuper = 347,
		Menu = 348
	} Key;

	inline std::ostream& operator<<(std::ostream& os, KeyCode keyCode)
	{
		os << static_cast<int32_t>(keyCode);
		return os;
	}
}

// From glfw3.h
#define GEM_KEY_SPACE           ::Gem::Key::Space
#define GEM_KEY_APOSTROPHE      ::Gem::Key::Apostrophe    /* ' */
#define GEM_KEY_COMMA           ::Gem::Key::Comma         /* , */
#define GEM_KEY_MINUS           ::Gem::Key::Minus         /* - */
#define GEM_KEY_PERIOD          ::Gem::Key::Period        /* . */
#define GEM_KEY_SLASH           ::Gem::Key::Slash         /* / */
#define GEM_KEY_0               ::Gem::Key::D0
#define GEM_KEY_1               ::Gem::Key::D1
#define GEM_KEY_2               ::Gem::Key::D2
#define GEM_KEY_3               ::Gem::Key::D3
#define GEM_KEY_4               ::Gem::Key::D4
#define GEM_KEY_5               ::Gem::Key::D5
#define GEM_KEY_6               ::Gem::Key::D6
#define GEM_KEY_7               ::Gem::Key::D7
#define GEM_KEY_8               ::Gem::Key::D8
#define GEM_KEY_9               ::Gem::Key::D9
#define GEM_KEY_SEMICOLON       ::Gem::Key::Semicolon     /* ; */
#define GEM_KEY_EQUAL           ::Gem::Key::Equal         /* = */
#define GEM_KEY_A               ::Gem::Key::A
#define GEM_KEY_B               ::Gem::Key::B
#define GEM_KEY_C               ::Gem::Key::C
#define GEM_KEY_D               ::Gem::Key::D
#define GEM_KEY_E               ::Gem::Key::E
#define GEM_KEY_F               ::Gem::Key::F
#define GEM_KEY_G               ::Gem::Key::G
#define GEM_KEY_H               ::Gem::Key::H
#define GEM_KEY_I               ::Gem::Key::I
#define GEM_KEY_J               ::Gem::Key::J
#define GEM_KEY_K               ::Gem::Key::K
#define GEM_KEY_L               ::Gem::Key::L
#define GEM_KEY_M               ::Gem::Key::M
#define GEM_KEY_N               ::Gem::Key::N
#define GEM_KEY_O               ::Gem::Key::O
#define GEM_KEY_P               ::Gem::Key::P
#define GEM_KEY_Q               ::Gem::Key::Q
#define GEM_KEY_R               ::Gem::Key::R
#define GEM_KEY_S               ::Gem::Key::S
#define GEM_KEY_T               ::Gem::Key::T
#define GEM_KEY_U               ::Gem::Key::U
#define GEM_KEY_V               ::Gem::Key::V
#define GEM_KEY_W               ::Gem::Key::W
#define GEM_KEY_X               ::Gem::Key::X
#define GEM_KEY_Y               ::Gem::Key::Y
#define GEM_KEY_Z               ::Gem::Key::Z
#define GEM_KEY_LEFT_BRACKET    ::Gem::Key::LeftBracket   /* [ */
#define GEM_KEY_BACKSLASH       ::Gem::Key::Backslash     /* \ */
#define GEM_KEY_RIGHT_BRACKET   ::Gem::Key::RightBracket  /* ] */
#define GEM_KEY_GRAVE_ACCENT    ::Gem::Key::GraveAccent   /* ` */
#define GEM_KEY_WORLD_1         ::Gem::Key::World1        /* non-US #1 */
#define GEM_KEY_WORLD_2         ::Gem::Key::World2        /* non-US #2 */

/* Function keys */
#define GEM_KEY_ESCAPE          ::Gem::Key::Escape
#define GEM_KEY_ENTER           ::Gem::Key::Enter
#define GEM_KEY_TAB             ::Gem::Key::Tab
#define GEM_KEY_BACKSPACE       ::Gem::Key::Backspace
#define GEM_KEY_INSERT          ::Gem::Key::Insert
#define GEM_KEY_DELETE          ::Gem::Key::Delete
#define GEM_KEY_RIGHT           ::Gem::Key::Right
#define GEM_KEY_LEFT            ::Gem::Key::Left
#define GEM_KEY_DOWN            ::Gem::Key::Down
#define GEM_KEY_UP              ::Gem::Key::Up
#define GEM_KEY_PAGE_UP         ::Gem::Key::PageUp
#define GEM_KEY_PAGE_DOWN       ::Gem::Key::PageDown
#define GEM_KEY_HOME            ::Gem::Key::Home
#define GEM_KEY_END             ::Gem::Key::End
#define GEM_KEY_CAPS_LOCK       ::Gem::Key::CapsLock
#define GEM_KEY_SCROLL_LOCK     ::Gem::Key::ScrollLock
#define GEM_KEY_NUM_LOCK        ::Gem::Key::NumLock
#define GEM_KEY_PRINT_SCREEN    ::Gem::Key::PrintScreen
#define GEM_KEY_PAUSE           ::Gem::Key::Pause
#define GEM_KEY_F1              ::Gem::Key::F1
#define GEM_KEY_F2              ::Gem::Key::F2
#define GEM_KEY_F3              ::Gem::Key::F3
#define GEM_KEY_F4              ::Gem::Key::F4
#define GEM_KEY_F5              ::Gem::Key::F5
#define GEM_KEY_F6              ::Gem::Key::F6
#define GEM_KEY_F7              ::Gem::Key::F7
#define GEM_KEY_F8              ::Gem::Key::F8
#define GEM_KEY_F9              ::Gem::Key::F9
#define GEM_KEY_F10             ::Gem::Key::F10
#define GEM_KEY_F11             ::Gem::Key::F11
#define GEM_KEY_F12             ::Gem::Key::F12
#define GEM_KEY_F13             ::Gem::Key::F13
#define GEM_KEY_F14             ::Gem::Key::F14
#define GEM_KEY_F15             ::Gem::Key::F15
#define GEM_KEY_F16             ::Gem::Key::F16
#define GEM_KEY_F17             ::Gem::Key::F17
#define GEM_KEY_F18             ::Gem::Key::F18
#define GEM_KEY_F19             ::Gem::Key::F19
#define GEM_KEY_F20             ::Gem::Key::F20
#define GEM_KEY_F21             ::Gem::Key::F21
#define GEM_KEY_F22             ::Gem::Key::F22
#define GEM_KEY_F23             ::Gem::Key::F23
#define GEM_KEY_F24             ::Gem::Key::F24
#define GEM_KEY_F25             ::Gem::Key::F25

/* Keypad */
#define GEM_KEY_KP_0            ::Gem::Key::KP0
#define GEM_KEY_KP_1            ::Gem::Key::KP1
#define GEM_KEY_KP_2            ::Gem::Key::KP2
#define GEM_KEY_KP_3            ::Gem::Key::KP3
#define GEM_KEY_KP_4            ::Gem::Key::KP4
#define GEM_KEY_KP_5            ::Gem::Key::KP5
#define GEM_KEY_KP_6            ::Gem::Key::KP6
#define GEM_KEY_KP_7            ::Gem::Key::KP7
#define GEM_KEY_KP_8            ::Gem::Key::KP8
#define GEM_KEY_KP_9            ::Gem::Key::KP9
#define GEM_KEY_KP_DECIMAL      ::Gem::Key::KPDecimal
#define GEM_KEY_KP_DIVIDE       ::Gem::Key::KPDivide
#define GEM_KEY_KP_MULTIPLY     ::Gem::Key::KPMultiply
#define GEM_KEY_KP_SUBTRACT     ::Gem::Key::KPSubtract
#define GEM_KEY_KP_ADD          ::Gem::Key::KPAdd
#define GEM_KEY_KP_ENTER        ::Gem::Key::KPEnter
#define GEM_KEY_KP_EQUAL        ::Gem::Key::KPEqual

#define GEM_KEY_LEFT_SHIFT      ::Gem::Key::LeftShift
#define GEM_KEY_LEFT_CONTROL    ::Gem::Key::LeftControl
#define GEM_KEY_LEFT_ALT        ::Gem::Key::LeftAlt
#define GEM_KEY_LEFT_SUPER      ::Gem::Key::LeftSuper
#define GEM_KEY_RIGHT_SHIFT     ::Gem::Key::RightShift
#define GEM_KEY_RIGHT_CONTROL   ::Gem::Key::RightControl
#define GEM_KEY_RIGHT_ALT       ::Gem::Key::RightAlt
#define GEM_KEY_RIGHT_SUPER     ::Gem::Key::RightSuper
#define GEM_KEY_MENU            ::Gem::Key::Menu