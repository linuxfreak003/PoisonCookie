TARGETS := poisoncookie
FLAGS := -lGL -lGLU -lglut

all: $(TARGETS)

check: $(TARGETS)
	./poisoncookie

poisoncookie: game.o  poisoncookie.o
	g++ -o $(TARGETS) game.o poisoncookie.o $(FLAGS)

game.o: game.cpp
	g++ -c game.cpp $(FLAGS)

poisoncookie.o: poisoncookie.cpp
	g++ -c poisoncookie.cpp

clean:
	-rm -f *~
	-rm -f $(TARGETS)
	-rm -f *.o
