# **Wordle**

Wordle is a simple guessing game where the player has to guess a five-letter word chosen by the computer. The player has six attempts to guess the word correctly.

## Getting Started
To play the game, you need to have ncurses installed on your system. If you don't have it, you can install it by running the following command:

    sudo apt-get install libncurses5-dev libncursesw5-dev

Once you have ncurses installed, you can compile and run the game using the following commands:

    gcc -o wordle wordle.c -lncurses
    ./wordle

## How to Play
When you run the game, you will see a window with five boxes, each representing a letter in the word you have to guess. You will also see a log window that shows your previous guesses and their results.

To make a guess, type in a five-letter word and press Enter. The game will then show you how many letters in your guess are in the correct position (colored green), how many are in the wrong position (colored yellow), and how many are not in the word at all (colored black). You have six attempts to guess the word correctly.

If you guess the word correctly, you win the game. If you run out of attempts without guessing the word, you lose the game.

## Customization
The game comes with a default list of 27 words that it can choose from. If you want to add or remove words from this list, you can modify the "cuvinte" array in the source code.

## Acknowledgements
The game was created by an anonymous individual and gained popularity on Twitter in 2021.
