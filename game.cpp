#include "stdafx.h";
#include "game.h"

namespace mastermind {
	Game::Game(int codeLength, int totalTrial) {
		Game::console = Console(500, 500);
		Game::init(codeLength, totalTrial);
	}
	void Game::breakRun() {
		throw BREAK;
	}
	void Game::doState(int state) {
		switch (state) {
		case STATE::INPUT: {
			try {
				string input = Game::readLine();
				Game::handleInput(input);
			}
			catch (float f) {
				if (f != BREAK) {
					throw exception("Unknown exception code");
				}
			}
			catch (std::exception& e) {
				cerr << e.what() << '\n';
				doState(STATE::INPUT);
			}
			break;
		}
		case STATE::PRINT: {
			Game::print();
			break;
		}
		case STATE::STOPPED: {
			system("PAUSE");
			cout << "Game is stoped, do you want to restart ? [Y]\n";
			string input;
			cin >> input;
			cin.clear();
			cin.ignore(10000, '\n');
			if (input == "Y") {
				Game::init(Game::codeLength, Game::totalTrial);
				Game::run();
			}
			else {
				Game::stop();
			}
			break;
		}
		default:
			break;
		}
	}
	void Game::generateCode() {
		char* dataRange = (char*)malloc(sizeof(char) * COLOR_POSSIBILITIES);
		for (int i = 0; i < COLOR_POSSIBILITIES; i++) {
			dataRange[i] = 'A' + i;
		}
		srand(time(NULL));
		Game::secretCode = (char*)malloc(sizeof(char) * Game::codeLength);
		int* temp = (int*)malloc(sizeof(int) * COLOR_POSSIBILITIES);
		for (int i = 0; i < Game::codeLength; i++) {
			int randomIndex = rand() % COLOR_POSSIBILITIES;
			while (temp[randomIndex] == true) {
				randomIndex = rand() % COLOR_POSSIBILITIES;
			}
			temp[randomIndex] = true;
			Game::secretCode[i] = dataRange[randomIndex];
			Game::tray[Game::totalTrial][i] = Game::secretCode[i];
		}
		temp = NULL;
	}
	void Game::handleInput(string input) {
		if (input == "quit") {
			Game::stop();
		}
		else if (input == "new") {
			Game::startNew();
		}
		else if (input == "restart") {
			Game::init(Game::codeLength, Game::totalTrial);
		}
		else if (input == "level easy") {
			Game::updateLevel(LEVEL::EASY);
		}
		else if (input == "level medium") {
			Game::updateLevel(LEVEL::MEDIUM);
		}
		else if (input == "level hard") {
			Game::updateLevel(LEVEL::HARD);
		}
		else if (input == "hack") {
			Game::hack = !Game::hack;
		}
		else if (Game::running) {
			Game::match(input);
		}
		else {
			Game::doState(STATE::STOPPED);
		}
	}
	void Game::init(int codeLength, int totalTrial) {
		if (codeLength % 2 != 0) {
			throw invalid_argument("The code lenght must be even number");
		}
		if (codeLength < 4 || codeLength > 8) {
			throw invalid_argument("The code lenght must be between 4 & 8 (include)");
		}
		if (totalTrial < 10 || totalTrial > 20) {
			throw invalid_argument("The retries count must be between 10 & 20 (include)");
		}
		Game::stepIndex = 0;
		Game::codeLength = codeLength;
		Game::totalTrial = totalTrial;
		Game::tray = (char**)malloc(sizeof(char*) * (Game::totalTrial + 1));
		for (int i = 0; i < Game::totalTrial + 1; i++) {
			*(Game::tray + i) = (char*)malloc(sizeof(char) * Game::codeLength);
			for (int j = 0; j < Game::codeLength; j++) {
				Game::tray[i][j] = NULL;
			}
		}
		Game::result = (char**)malloc(sizeof(char*) * Game::totalTrial);
		for (int i = 0; i < Game::totalTrial; i++) {
			*(Game::result + i) = (char*)malloc(sizeof(char) * Game::codeLength);
			for (int j = 0; j < Game::codeLength; j++) {
				Game::result[i][j] = NULL;
			}
		}
		Game::generateCode();
		Game::updateLevel(Game::level);
	}
	void Game::match(string from) {
		int length = from.size();
		if (length != Game::codeLength) {
			string msg = "Input must contains ";
			msg.append(to_string(Game::codeLength));
			msg.append(" char !");
			throw invalid_argument(msg);
		}
		int win = 0;
		for (int i = 0; i < Game::codeLength; i++) {
			char at = from.at(i);
			at = toupper(at);
			if (at < 'A' || at >= 'A' + COLOR_POSSIBILITIES) {
				for (int j = i; j >= 0; j--) {
					Game::tray[Game::stepIndex][j] = NULL;
					Game::result[Game::stepIndex][j] = NULL;
				}
				throw invalid_argument("Invalid input char, every char must be an uper char btw A & H");
			}
			Game::tray[Game::stepIndex][i] = at;
			char match = '_';
			if (at == Game::secretCode[i]) {
				match = MATCH_CODE::X;
			}
			else {
				for (int j = 0; j < Game::codeLength; j++) {
					if (at == Game::secretCode[j]) {
						match = MATCH_CODE::O;
						break;
					}
				}
			}
			if (match == MATCH_CODE::X) {
				win++;
			}
			Game::result[Game::stepIndex][i] = match;
		}
		if (win == Game::codeLength) {
			cout << "YOU WIN !\n";
			cout << "after " << (Game::stepIndex + 1) << " trials\n";
			Game::doState(STATE::STOPPED);
		}
		Game::stepIndex++;
	}
	void Game::print() {
		system("cls");
		int rowCount = 0;
		int totalRow = Game::hack ? Game::totalTrial : Game::totalTrial - 1;
		cout << "\n";
		for (int i = totalRow; i >= 0; i--) {
			Game::printRow(i, rowCount);
			rowCount+= 2;
		}
		cout << TAB;
		for (int i = 0; i < Game::codeLength; i++) {
			cout << "+---";
		}
		cout << "+\n\n" << TAB << " ";
		for (int i = 0; i < COLOR_POSSIBILITIES; i++) {
			if (i == (COLOR_POSSIBILITIES / 2)) {
				cout << "\n" << TAB << " ";
			}
			char letter = 'A' + i;
			Game::printColor(letter);
		}
		cout << "\n\n";
	}
	void Game::printColor(char letter) {
		Game::console.backColor(letter - 'A');
		cout << " " << letter << " ";
		Game::console.resetBackColor();
		cout << " ";
	}
	void Game::printRow(int stepIndex, int rowCount) {
		char* row = Game::tray[stepIndex];
		cout << TAB;
		for (int i = 0; i < Game::codeLength; i++) {
			cout << "+---";
		}
		cout << "+";
		for (int i = 0; i < Game::codeLength; i++) {
			cout << " ";
		}
		if (rowCount < HELP_LINES) {
			cout << "     " << Game::help[rowCount];
			rowCount++;
		}
		cout << "\n";
		cout << TAB;
		for (int i = 0; i < Game::codeLength; i++) {
			cout << "|";
			if (row[i] != NULL) {
				Game::console.backColor(row[i] - 'A');
				cout << " " << row[i] << " ";
				Game::console.resetBackColor();
			}
			else {
				cout << "   ";
			}
		}
		cout << "|";
		int count = 0;
		if (stepIndex < Game::totalTrial) {
			char* match = Game::result[stepIndex];
			if (match[0] != NULL) {
				cout << " ";
				if (Game::level == LEVEL::HARD) {
					int xCount = 0;
					int oCount = 0;
					for (int i = 0; i < Game::codeLength; i++) {
						if (Game::result[stepIndex][i] == MATCH_CODE::X) {
							xCount++;
						}
						else if (Game::result[stepIndex][i] == MATCH_CODE::O) {
							oCount++;
						}
					}
					for (int i = 0; i < xCount; i++) {
						cout << (char)MATCH_CODE::X;
						count++;
					}
					for (int i = 0; i < oCount; i++) {
						cout << (char)MATCH_CODE::O;
						count++;
					}
				}
				else {
					for (int i = 0; i < Game::codeLength; i++) {
						if (Game::level == LEVEL::EASY || match[i] != '_') {
							cout << match[i];
							count++;
						}
					}
				}
			}
		}
		for (int i = 0; i < Game::codeLength - count; i++) {
			cout << " ";
		}
		if (rowCount < HELP_LINES) {
			cout << "     " << Game::help[rowCount];
			rowCount++;
		}
		cout << "\n";
	}
	string Game::readLine() {
		string input = string();
		int count = 0;
		char c = 0;
		while ((c = _getch()) != '\r') {
			if (c == 27) {
				Game::stop();
			}
			else if (c == 32) {
				cout << " ";
				input.insert(count, 1, c);
				count++;
			}
			else if (c == -32) {
				switch (_getch()) {
				case 72:
					if (Game::stepIndex > 0) {
						while (count > 0) {
							count--;
							char iChar = input.at(count);
							if (iChar >= 'A' && iChar < 'A' + 8) {
								for (int i = 0; i < 4; i++) {
									cout << '\b' << " " << '\b';
								}
							}
							else {
								cout << '\b' << " " << '\b';
							}
						}
						input.clear();
						char* lastInput = Game::tray[Game::stepIndex - 1];
						count = Game::codeLength;
						for (int i = 0; i < count; i++) {
							Game::printColor(lastInput[i]);
							input.insert(i, 1, lastInput[i]);
						}
					}
				}
			}
			else if (c == 127 || c == 8) {
				if (count > 0) {
					count--;
					char iChar = input.at(count);
					if (iChar >= 'A' && iChar < 'A' + 8) {
						for (int i = 0; i < 4; i++) {
							cout << '\b' << " " << '\b';
						}
					}
					else {
						cout << '\b' << " " << '\b';
					}
					input.pop_back();
				}
			}
			else if (c >= 'A' && c < 'A' + COLOR_POSSIBILITIES) {
				Game::printColor(c);
				input.insert(count, 1, c);
				count++;
			}
			else if (c >= 'A' && c <= 'z') {
				cout << c;
				input.insert(count, 1, c);
				count++;
			}
			c = 0;
		}
		cout << "\n";
		return input;
	}
	void Game::run() {
		Game::running = true;
		while (Game::running && Game::stepIndex < Game::totalTrial) {
			for (int state = 0; state <= STATE::INPUT; state++) {
				Game::doState(state);
			}
		}
		if (Game::stepIndex >= Game::totalTrial) {
			Game::doState(STATE::PRINT);
			cout << "YOU LOOSE !\n";
			Game::doState(STATE::STOPPED);
		}
	}
	void Game::startNew() {
		cout << "code length: [4, 6, 8]\n";
		int codeLenght;
		cin >> codeLenght;
		cout << "total trials: [10;20]\n";
		int totalTrials;
		cin >> totalTrials;
		cin.clear();
		cin.ignore(10000, '\n');
		Game::init(codeLenght, totalTrials);
		Game::breakRun();
	}
	void Game::stop() {
		if (Game::running) {
			Game::running = false;
			Game::breakRun();
		}
	}
	void Game::updateLevel(int level) {
		string levelStr = TAB;
		switch (level) {
		case LEVEL::EASY:
			levelStr.append("EASY");
			break;
		case LEVEL::MEDIUM:
			levelStr.append("MEDIUM");
			break;
		case LEVEL::HARD:
			levelStr.append("HARD");
			break;
		default:
			break;
		}
		Game::level = level;
		Game::help[HELP_LINES - 1] = levelStr;
	}
}
