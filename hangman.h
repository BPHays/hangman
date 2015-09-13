#ifndef HANGMAN_H
#define HANGMAN_H

#define DEFAULT_WORDLIST "test.txt"
#define MAX_WORD_LEN 100
#define DEFAULT_WORDLIST_SIZE 1024
#define DEFAULT_MISSES_ALLOWED 7
#define ALPHABET_SIZE 26

class Hangman {
	private:
		// the word bank to choose from
		char ** _wordlist;
		int _max;
		int _current;

		// number of wins and losses
		int _wins;
		int _losses;

		// number of wrong guesses
		int _missed;
		int _missesAllowed;

		// letters that the player has guessed
		char * _guesses;
		// the word that is trying to be guessed
		char * _word;
		char * _hiddenWord;

		// read words into the wordlist from a file
		bool readWords(char * wordlist);

	public:
		Hangman();
		Hangman(char * wordlist);
		~Hangman();

		// check if a letter is in the word
		int guess(char c);

		// start a new game with a new word
		void newGame();

		// check if the game is still being played or if it has ended
		int getStatus();

		int getWins();
		int getLosses();
		int getMissed();
		int getMissesAllowed();
		const char * getGuesses();
		const char * getHiddenWord();
};

#endif
