#include "stdafx.h"
#include "console.h"

namespace mastermind_utils {
	Console::Console(int width, int height) {
		Console::hstdin = GetStdHandle(STD_INPUT_HANDLE);
		Console::hstdout = GetStdHandle(STD_OUTPUT_HANDLE);
		if (!GetConsoleScreenBufferInfo(Console::hstdout, &csbi)) {
			throw runtime_error("You must be attached to a human.");
		}
		COORD dummy;
		SetConsoleDisplayMode(Console::hstdout, CONSOLE_FULLSCREEN_MODE, &dummy);
		CONSOLE_FONT_INFOEX font;
		GetCurrentConsoleFontEx(Console::hstdout, false, &font);
		font.dwFontSize.X = 10;
		font.dwFontSize.Y = 18;
		SetCurrentConsoleFontEx(Console::hstdout, false, &font);
	}
	void Console::color(int color) {
		SetConsoleTextAttribute(Console::hstdout, color);
	}
	void Console::textColor(int color) {
		Console::tColor = color;
		Console::color(Console::tColor + Console::bColor * 16);
	}
	void Console::backColor(int color) {
		Console::bColor = color;
		Console::color(Console::tColor + Console::bColor * 16);
	}
	void Console::resetTextColor() {
		Console::tColor = COLOR::WHITE;
		Console::color(Console::tColor + Console::bColor * 16);
	}
	void Console::resetBackColor() {
		Console::bColor = 0;
		Console::color(Console::tColor + Console::bColor * 16);
	}
}