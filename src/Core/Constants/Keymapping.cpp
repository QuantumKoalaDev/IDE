#include "Keymap.h"

static 	std::unordered_map<int, std::string> internalToStringMap =
{
	{ Keymapping::ID_A, "a" },
	{ Keymapping::ID_B, "b" },
	{ Keymapping::ID_C, "c" },
	{ Keymapping::ID_D, "d" },
	{ Keymapping::ID_E, "e" },
	{ Keymapping::ID_F, "f" },
	{ Keymapping::ID_G, "g" },
	{ Keymapping::ID_H, "h" },
	{ Keymapping::ID_I, "i" },
	{ Keymapping::ID_J, "j" },
	{ Keymapping::ID_K, "k" },
	{ Keymapping::ID_L, "l" },
	{ Keymapping::ID_M, "m" },
	{ Keymapping::ID_N, "n" },
	{ Keymapping::ID_O, "o" },
	{ Keymapping::ID_P, "p" },
	{ Keymapping::ID_Q, "q" },
	{ Keymapping::ID_R, "r" },
	{ Keymapping::ID_S, "s" },
	{ Keymapping::ID_T, "t" },
	{ Keymapping::ID_U, "u" },
	{ Keymapping::ID_V, "v" },
	{ Keymapping::ID_W, "w" },
	{ Keymapping::ID_X, "x" },
	{ Keymapping::ID_Y, "y" },
	{ Keymapping::ID_Z, "z" },

	// Zahlen
	{ Keymapping::ID_1, "1" },
	{ Keymapping::ID_2, "2" },
	{ Keymapping::ID_3, "3" },
	{ Keymapping::ID_4, "4" },
	{ Keymapping::ID_5, "5" },
	{ Keymapping::ID_6, "6" },
	{ Keymapping::ID_7, "7" },
	{ Keymapping::ID_8, "8" },
	{ Keymapping::ID_9, "9" },
	{ Keymapping::ID_0, "0" },

	// Steuerzeichen
	{ Keymapping::ID_SPACE, "SPACE" },
	{ Keymapping::ID_TAB, "TAB" },
	{ Keymapping::ID_ENTER, "ENTER" },
	{ Keymapping::ID_BACKSPACE, "BACKSPACE" },
	{ Keymapping::ID_ESC, "ESC" },

	{ Keymapping::ID_SHIFT, "LSHIFT" },
	{ Keymapping::ID_CTRL, "CTRL" },
	{ Keymapping::ID_ALT, "ALT" },
};


std::string Keymapping::InternalToString(int keycode) {
	auto it = internalToStringMap.find(keycode);
	return (it != internalToStringMap.end()) ? it->second : "Not Found";
}


#ifdef _WIN32
static std::unordered_map<int, int> vkToInternalKeyMap =
{
	{ 'A', Keymapping::ID_A },
	{ 'B', Keymapping::ID_B },
	{ 'C', Keymapping::ID_C },
	{ 'D', Keymapping::ID_D },
	{ 'E', Keymapping::ID_E },
	{ 'F', Keymapping::ID_F },
	{ 'G', Keymapping::ID_G },
	{ 'H', Keymapping::ID_H },
	{ 'I', Keymapping::ID_I },
	{ 'J', Keymapping::ID_J },
	{ 'K', Keymapping::ID_K },
	{ 'L', Keymapping::ID_L },
	{ 'M', Keymapping::ID_M },
	{ 'N', Keymapping::ID_N },
	{ 'O', Keymapping::ID_O },
	{ 'P', Keymapping::ID_P },
	{ 'Q', Keymapping::ID_Q },
	{ 'R', Keymapping::ID_R },
	{ 'S', Keymapping::ID_S },
	{ 'T', Keymapping::ID_T },
	{ 'U', Keymapping::ID_U },
	{ 'V', Keymapping::ID_V },
	{ 'W', Keymapping::ID_W },
	{ 'X', Keymapping::ID_X },
	{ 'Y', Keymapping::ID_Y },
	{ 'Z', Keymapping::ID_Z },

	{ '0', Keymapping::ID_0 },
	{ '1', Keymapping::ID_1 },
	{ '2', Keymapping::ID_2 },
	{ '3', Keymapping::ID_3 },
	{ '4', Keymapping::ID_4 },
	{ '5', Keymapping::ID_5 },
	{ '6', Keymapping::ID_6 },
	{ '7', Keymapping::ID_7 },
	{ '8', Keymapping::ID_8 },
	{ '9', Keymapping::ID_9 },

	{ VK_NUMPAD0, Keymapping::ID_0 },
	{ VK_NUMPAD1, Keymapping::ID_1 },
	{ VK_NUMPAD2, Keymapping::ID_2 },
	{ VK_NUMPAD3, Keymapping::ID_3 },
	{ VK_NUMPAD4, Keymapping::ID_4 },
	{ VK_NUMPAD5, Keymapping::ID_5 },
	{ VK_NUMPAD6, Keymapping::ID_6 },
	{ VK_NUMPAD7, Keymapping::ID_7 },
	{ VK_NUMPAD8, Keymapping::ID_8 },
	{ VK_NUMPAD9, Keymapping::ID_9 },

	{ VK_SPACE, Keymapping::ID_SPACE },
	{ VK_TAB, Keymapping::ID_TAB },
	{ VK_RETURN, Keymapping::ID_ENTER },
	{ VK_BACK, Keymapping::ID_BACKSPACE },
	{ VK_ESCAPE, Keymapping::ID_ESC },
	{ VK_SHIFT, Keymapping::ID_SHIFT },
	{ VK_CONTROL, Keymapping::ID_CTRL },
	{ VK_MENU, Keymapping::ID_ALT },

	{ VK_UP, Keymapping::ID_ARROW_UP },
	{ VK_DOWN, Keymapping::ID_ARROW_DOWN },
	{ VK_RIGHT, Keymapping::ID_ARROW_RIGHT },
	{ VK_LEFT, Keymapping::ID_ARROW_LEFT },
};

int Keymapping::MapVirtualKeyToInternal(UINT vkCode)
{
	auto it = vkToInternalKeyMap.find(vkCode);
	return (it != vkToInternalKeyMap.end()) ? it->second : -1;
}


#endif