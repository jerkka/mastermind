#pragma once
#include "stdafx.h";

namespace mastermind_utils{
	class Console {
	public:
		HANDLE hstdin;
		HANDLE hstdout;
		CONSOLE_SCREEN_BUFFER_INFO csbi;
		int tColor = 15;
		int bColor;
	public:
		enum COLOR {
			BLACK = 0,
			DARK_BLUE = 1,
			DARK_GREEN = 2,
			DARK_AQUA = 3,
			DARK_RED = 4,
			DARK_PURPLE = 5,
			DARK_YELLOW = 6,
			DARK_WHITE = 7,
			GRAY = 8,
			BLUE = 9,
			GREEN = 10,
			AQUA = 11,
			RED = 12,
			PURPLE = 13,
			YELLOW = 14,
			WHITE = 15,
			BACKGROUND_WHITE = 0xF6
		};
		Console(int width = 500, int height = 500);
		void color(int color);
		void textColor(int color);
		void backColor(int color);
		void resetTextColor();
		void resetBackColor();
	};
}