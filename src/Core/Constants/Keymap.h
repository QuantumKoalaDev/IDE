#pragma once

#include <string>
#include <unordered_map>

namespace Keymapping
{
	constexpr int ID_A = 201;
	constexpr int ID_B = 202;
	constexpr int ID_C = 203;
	constexpr int ID_D = 204;
	constexpr int ID_E = 205;
	constexpr int ID_F = 206;
	constexpr int ID_G = 207;
	constexpr int ID_H = 208;
	constexpr int ID_I = 209;
	constexpr int ID_J = 210;
	constexpr int ID_K = 211;
	constexpr int ID_L = 212;
	constexpr int ID_M = 213;
	constexpr int ID_N = 214;
	constexpr int ID_O = 215;
	constexpr int ID_P = 216;
	constexpr int ID_Q = 217;
	constexpr int ID_R = 218;
	constexpr int ID_S = 219;
	constexpr int ID_T = 220;
	constexpr int ID_U = 221;
	constexpr int ID_V = 222;
	constexpr int ID_W = 223;
	constexpr int ID_X = 224;
	constexpr int ID_Y = 225;
	constexpr int ID_Z = 226;

	constexpr int ID_1 = 301;
	constexpr int ID_2 = 302;
	constexpr int ID_3 = 303;
	constexpr int ID_4 = 304;
	constexpr int ID_5 = 305;
	constexpr int ID_6 = 306;
	constexpr int ID_7 = 307;
	constexpr int ID_8 = 308;
	constexpr int ID_9 = 309;
	constexpr int ID_0 = 310;

	constexpr int ID_SPACE = 401;  // Leerzeichen
	constexpr int ID_TAB = 402;  // Tabulator
	constexpr int ID_ENTER = 403;  // Enter
	constexpr int ID_BACKSPACE = 404;  // Rückschritt
	constexpr int ID_ALT = 405;  // Alt-Taste
	constexpr int ID_SHIFT = 406;  // Shift-Taste
	constexpr int ID_CTRL = 407;  // Steuerungstaste
	constexpr int ID_ESC = 408;  // Escape
	constexpr int ID_CAPSLOCK = 409;  // Caps Lock

	// Satzzeichen und Sonderzeichen (ASCII 33–47)
	constexpr int ID_EXCLAMATION = 501; // !
	constexpr int ID_QUOTE = 502; // "
	constexpr int ID_HASH = 503; // #
	constexpr int ID_DOLLAR = 504; // $
	constexpr int ID_PERCENT = 505; // %
	constexpr int ID_AMPERSAND = 506; // &
	constexpr int ID_APOSTROPHE = 507; // '
	constexpr int ID_LEFT_PAREN = 508; // (
	constexpr int ID_RIGHT_PAREN = 509; // )
	constexpr int ID_ASTERISK = 510; // *
	constexpr int ID_PLUS = 511; // +
	constexpr int ID_COMMA = 512; // ,
	constexpr int ID_MINUS = 513; // -
	constexpr int ID_PERIOD = 514; // .
	constexpr int ID_SLASH = 515; // /

	// Sonderzeichen ASCII 58–64
	constexpr int ID_COLON = 516; // :
	constexpr int ID_SEMICOLON = 517; // ;
	constexpr int ID_LESS_THAN = 518; // <
	constexpr int ID_EQUAL = 519; // =
	constexpr int ID_GREATER_THAN = 520; // >
	constexpr int ID_QUESTION = 521; // ?
	constexpr int ID_AT = 522; // @

	// Sonderzeichen ASCII 91–96
	constexpr int ID_LEFT_BRACKET = 523; // [
	constexpr int ID_BACKSLASH = 524; // '\'
	constexpr int ID_RIGHT_BRACKET   = 525; // ]
	constexpr int ID_CARET = 526; // ^
	constexpr int ID_UNDERSCORE = 527; // _
	constexpr int ID_GRAVE = 528; // `

	// Sonderzeichen ASCII 123–126
	constexpr int ID_LEFT_BRACE = 529; // {
	constexpr int ID_PIPE = 530; // |
	constexpr int ID_RIGHT_BRACE = 531; // }
	constexpr int ID_TILDE = 532; // ~

	// Umlaute & Sonderzeichen (UTF-8 erweitert)
	constexpr int ID_A_UMLAUT = 601; // Ä
	constexpr int ID_O_UMLAUT = 602; // Ö
	constexpr int ID_U_UMLAUT = 603; // Ü
	constexpr int ID_A_UMLAUT_SMALL = 604; // ä
	constexpr int ID_O_UMLAUT_SMALL = 605; // ö
	constexpr int ID_U_UMLAUT_SMALL = 606; // ü
	constexpr int ID_SHARP_S = 607; // ß

	// Zusätzliche Tasten
	constexpr int ID_F1 = 701;
	constexpr int ID_F2 = 702;
	constexpr int ID_F3 = 703;
	constexpr int ID_F4 = 704;
	constexpr int ID_F5 = 705;
	constexpr int ID_F6 = 706;
	constexpr int ID_F7 = 707;
	constexpr int ID_F8 = 708;
	constexpr int ID_F9 = 709;
	constexpr int ID_F10 = 710;
	constexpr int ID_F11 = 711;
	constexpr int ID_F12 = 712;

	constexpr int ID_INSERT = 713;
	constexpr int ID_DELETE = 714;
	constexpr int ID_HOME = 715;
	constexpr int ID_END = 716;
	constexpr int ID_PAGE_UP = 717;
	constexpr int ID_PAGE_DOWN = 718;

	constexpr int ID_ARROW_UP = 719;
	constexpr int ID_ARROW_DOWN = 720;
	constexpr int ID_ARROW_LEFT = 721;
	constexpr int ID_ARROW_RIGHT = 722;


#ifdef _WIN32
#include <Windows.h>
	int MapVirtualKeyToInternal(UINT vkCode);
#endif

#ifdef __linux__
#include <X11/keysym.h>

	std::unordered_map<KeySym, int> x11KeySymToInternalMap = {
		// Buchstaben
		{ XK_a, Keymapping::ID_A },
		{ XK_b, Keymapping::ID_B },
		{ XK_c, Keymapping::ID_C },
		{ XK_d, Keymapping::ID_D },
		{ XK_e, Keymapping::ID_E },
		{ XK_f, Keymapping::ID_F },
		{ XK_g, Keymapping::ID_G },
		{ XK_h, Keymapping::ID_H },
		{ XK_i, Keymapping::ID_I },
		{ XK_j, Keymapping::ID_J },
		{ XK_k, Keymapping::ID_K },
		{ XK_l, Keymapping::ID_L },
		{ XK_m, Keymapping::ID_M },
		{ XK_n, Keymapping::ID_N },
		{ XK_o, Keymapping::ID_O },
		{ XK_p, Keymapping::ID_P },
		{ XK_q, Keymapping::ID_Q },
		{ XK_r, Keymapping::ID_R },
		{ XK_s, Keymapping::ID_S },
		{ XK_t, Keymapping::ID_T },
		{ XK_u, Keymapping::ID_U },
		{ XK_v, Keymapping::ID_V },
		{ XK_w, Keymapping::ID_W },
		{ XK_x, Keymapping::ID_X },
		{ XK_y, Keymapping::ID_Y },
		{ XK_z, Keymapping::ID_Z },

		// Zahlen
		{ XK_1, Keymapping::ID_1 },
		{ XK_2, Keymapping::ID_2 },
		{ XK_3, Keymapping::ID_3 },
		{ XK_4, Keymapping::ID_4 },
		{ XK_5, Keymapping::ID_5 },
		{ XK_6, Keymapping::ID_6 },
		{ XK_7, Keymapping::ID_7 },
		{ XK_8, Keymapping::ID_8 },
		{ XK_9, Keymapping::ID_9 },
		{ XK_0, Keymapping::ID_0 },

		// Steuerzeichen
		{ XK_space,     Keymapping::ID_SPACE },
		{ XK_Tab,       Keymapping::ID_TAB },
		{ XK_Return,    Keymapping::ID_ENTER },
		{ XK_BackSpace, Keymapping::ID_BACKSPACE },
		{ XK_Escape,    Keymapping::ID_ESC },

		{ XK_Shift_L,   Keymapping::ID_SHIFT },
		{ XK_Shift_R,   Keymapping::ID_SHIFT },
		{ XK_Control_L, Keymapping::ID_CTRL },
		{ XK_Control_R, Keymapping::ID_CTRL },
		{ XK_Alt_L,     Keymapping::ID_ALT },
		{ XK_Alt_R,     Keymapping::ID_ALT },
	};

	int MapKeySymToInternal(KeySym ks) {
		auto it = x11KeySymToInternalMap.find(ks);
		return (it != x11KeySymToInternalMap.end()) ? it->second : -1;
	}
#endif


	std::string InternalToString(int keycode);

}

