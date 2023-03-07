SRCS = main.cpp Animation.cpp

all: compile link run

compile:
	g++ -Isrc/include -c *.cpp && mv *.o build

link:
	g++ build/*.o -o build/game -Lsrc/lib -lsfml-graphics -lsfml-window -lsfml-system

run:
	cd build && ./game.exe