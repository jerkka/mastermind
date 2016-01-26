#pragma once
#include "stdafx.h"
#include "console.h"

using namespace mastermind_utils;

namespace mastermind {
	const int HELP_LINES = 18;
	const int COLOR_POSSIBILITIES = 8;
	const float BREAK = 0.123;
	const string TAB = "   ";
	
	class Game {
	private:
		char* secretCode;
		char** tray;
		char** result;
		int codeLength;
		int totalTrial;
		int stepIndex;
		bool hack;		
		Console console;
		string help[HELP_LINES] = {
			"         _____ __ __           __",
			"|\\/| /\\ (_  | |_ |__)|\\/|||\\ ||  \\",
			"|  |/--\\__) | |__| \\ |  ||| \\||__/",
			"",
			"Commands:",
			"   - <A..H>: your code :).",
			"   - quit: to exit the game.",
			"   - level <level>: Swap to an another level (easy, medium, hard).",
			"   - new: Start a new game with new options.",
			"   - restart: Start a new game.",
			"   - <secret>: show the secret code :P.",
			"Rules:",
			"   - X mean that you have found a char and his position",
			"   but you dunno who is it.",
			"   - O mean that you have found a char but at a wrong",
			"   position.",
			"Current level:",
			"<level>"
		};
		void updateLevel(int level = 2);
		void doState(int state);
		void breakRun();
		void init(int codeLength, int totalTrial);
		void generateCode();
		void printRow(int index, int rowCount);
		void printColor(char letter);
		void removeChar(char letter);
		void handleInput(string input);
		void match(string from);
		string readLine();
	public:
		enum STATE {
			PRINT = 0,
			INPUT = 1,
			STOPPED = 2
		};
		enum LEVEL {
			EASY = 0,
			MEDIUM = 1,
			HARD = 2
		};
		enum MATCH_CODE {
			X = 'X',
			O = 'O'
		};
		Game(int codeLength = 4, int retriesCount = 10);
		void startNew();
		void run();
		void stop();
		void print();
		bool running;
		int level = LEVEL::HARD;
	};
}