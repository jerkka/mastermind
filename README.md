#MASTERMIND C++

> Mastermind or Master Mind is a code-breaking game for two players. The modern game with pegs was invented in 1970 by Mordecai Meirowitz, an Israeli postmaster and telecommunications expert. It resembles an earlier pencil and paper game called Bulls and Cows that may date back a century or more.

from: https://en.wikipedia.org/wiki/Mastermind_(board_game)

##RULES
- The computer picks a sequence of colors. The number of colors is the code length. The default code length is 4 but it can be changed when starting a new game.
- The objective of the game is to guess the exact positions of the colors in the computer's sequence.
- By default, a color can be used only once in a code sequence.
- After filling a line with your guesses and pressing 'ENTER', the computer responses with the result of your guess.
- For each color in your guess that is in the correct color and correct position in the code sequence, the computer display a X on the right side of the current guess.
- For each color in your guess that is in the correct color but is NOT in the correct position in the code sequence, the computer display a O on the right side of the current guess.
- You win the game when you manage to guess all the colors in the code sequence and when they all in the right position.
- You lose the game if you use all attempts without guessing the computer code sequence.
