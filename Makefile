all: playothello playothello_ai

playothello: othello.o othelloboard.o
	g++ -std=c++14 othello.o othelloboard.o -o playothello

playothello_ai: othello_ai.o othelloboard.o
	g++ -std=c++14 othello_ai.o othelloboard.o -o playothello_ai

othello.o: othello.cpp othelloboard.h
	g++ -c -std=c++14 othello.cpp -o othello.o

othello_ai.o: othello_ai.cpp othelloboard.h
	g++ -c -std=c++14 othello_ai.cpp -o othello_ai.o

othelloboard.o: othelloboard.cpp othelloboard.h
	g++ -c -std=c++14 othelloboard.cpp -o othelloboard.o

clean:
	rm *.o playothello playothello_ai
