#pragma once
#include "stdafx.h"
#include "mastermind.h"

using namespace mastermind;

int main() {
	Game masterMind = Game(4, 10);
	masterMind.run();
}