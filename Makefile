all : hangman.o main.o gui.o
	g++ -g -o hangman hangman.o gui.o main.o `pkg-config gtkmm-3.0 --cflags --libs`

main.o : main.cc hangman.h
	g++ -c main.cc -g `pkg-config gtkmm-3.0 --cflags --libs`

hangman.o : hangman.cc hangman.h
	g++ -c hangman.cc -g

gui.o : gui.cc gui.h
	g++ -c gui.cc -g  `pkg-config gtkmm-3.0 --cflags --libs`

clean :
	rm hangman hangman.o main.o gui.o
