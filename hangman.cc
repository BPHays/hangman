#include "hangman.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>

// use the default wordlist
Hangman::Hangman() {
	readWords(DEFAULT_WORDLIST);
	_missesAllowed = DEFAULT_MISSES_ALLOWED;
	_guesses = (char *) calloc(ALPHABET_SIZE + 1, sizeof(char));
	_hiddenWord = new char[MAX_WORD_LEN];
}

// use a given wordlist
Hangman::Hangman(char * wordlist) {
	readWords(wordlist);
	_missesAllowed = DEFAULT_MISSES_ALLOWED;
	_hiddenWord = new char[MAX_WORD_LEN];
}

Hangman::~Hangman() {
	// free all of the words in the word list
	for (int i = 0; i < _current; i++) {
		free(_wordlist[i]);
	}
	free(_wordlist);
	free(_guesses);
}

// read words into the wordlist from a file
bool Hangman::readWords(char * wordlist) {
	_max = DEFAULT_WORDLIST_SIZE;
	_current = 0;
	_wordlist = (char **) malloc(sizeof(char *) * _max);
	
	FILE * fp = fopen(wordlist, "r");
	char * temp = (char *) malloc(MAX_WORD_LEN);
	while (fscanf(fp, " %100[^\n]", temp) != EOF) {
		// if the array is full resize it
		if (_current >= _max) {
			_max *= 2;
			_wordlist = (char **) realloc(_wordlist, sizeof(char *) * _max);
		}

		// add the word to the wordlist
		_wordlist[_current] = strdup(temp);
		_current++;

		printf("%s\n", _wordlist[_current - 1]);
	}
}

// check that the letter has not been guessed and then test if it is in the word
int Hangman::guess(char c) {
	if (strchr(_guesses, c)) return -1;

	// add c to the list of guessed letters
	_guesses[strlen(_guesses)] = c;

	// check if c is in the secret word
	if (strchr(_word, c)){
		for (int i = 0; i < strlen(_word); i++) {
			if (_word[i] == c) {
				_hiddenWord[i] = c;
			}
		}
		return 1;
	} else {
		_missed++;
		return 0;
	}
}

// start a new game with a new word
void Hangman::newGame() {
	_missed = 0;
	
	// generate a random number in the range [0, _max)
	srand(time(NULL));
	int r = (rand() / RAND_MAX) * (_max - 1);

	// select the word to try and guess
	_word = _wordlist[r];

	// clear out the last games guesses
	bzero(_guesses, ALPHABET_SIZE);

	// make a copy of the word with the chars hidden
	int i;
	for (i = 0; i < strlen(_word); i++) {
		_hiddenWord[i] = '_';
	}
	_hiddenWord[i] = '\0';
}

// check if the game was won, lost, or is still in play
int Hangman::getStatus() {
	// check if the user has guessed too many letters wrong
	if (_missed >= _missesAllowed) {
		_losses++;
		return 0;
	} else {
		if (!strcmp(_word, _hiddenWord)) {
			// all of the letters were guessed
			_wins++;
			return 1;
		} else {
			return -1;
		}
	}
}

int Hangman::getWins() {
	return _wins;
}

int Hangman::getLosses() {
	return _losses;
}

int Hangman::getMissed() {
	return _missed;
}

int Hangman::getMissesAllowed() {
	return _missesAllowed;
}

const char * Hangman::getGuesses() {
	return _guesses;
}

const char * Hangman::getHiddenWord() {
	return _hiddenWord;
}
