main:
	g++ -c simulate.cpp
	g++ main.cpp simulate.o -o life -lncurses
remake:
	rm life *.o
	make
	./life
clean:
	rm life *.o
