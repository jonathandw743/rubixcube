default: main

main: o/main.o o/s.o o/move.o
	gcc o/main.o o/s.o o/move.o -o bin/main
	bin/main

o/main.o: c/main.c h/s.h h/move.h
	gcc -c c/main.c -o o/main.o

o/s.o: c/s.c h/s.h
	gcc -c c/s.c -o o/s.o
	
o/move.o: c/move.c h/move.h
	gcc -c c/move.c -o o/move.o
	
clean:
	rm -f bin/* o/*.o
