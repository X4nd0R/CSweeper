CSweeper: main.o mines.o | bin objects
	g++ objects/main.o objects/mines.o -o bin/CSweeper

main.o: | objects
	g++ main.cpp -I/include -c -o objects/main.o

mines.o: | objects
	g++ mines.cpp -c -o objects/mines.o

bin:
	mkdir -p $@

objects:
	mkdir -p $@