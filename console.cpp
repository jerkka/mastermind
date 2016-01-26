#include "stdafx.h"
#include "console.h"

namespace mastermind_utils {
	Console::Console() {
		Console::hstdin = GetStdHandle(STD_INPUT_HANDLE);
		Console::hstdout = GetStdHandle(STD_OUTPUT_HANDLE);
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