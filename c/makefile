all: unit.exe

unit.exe: unit.o
		gcc -o unit.exe unit.o

unit.o: unit.c
		gcc -c unit.c

clean:
		rm unit.o unit.exe *.pp *.o

debug:
		gcc unit.c -g

run:
		clear
		./unit.exe
