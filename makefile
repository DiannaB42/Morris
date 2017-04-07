objects = board.o main.o

morris: $(objects)
	g++ -o morris -Wall $(objects)
main.o: board.h
board.o: board.h

.PHONY: clean
clean:
	rm $(objects)