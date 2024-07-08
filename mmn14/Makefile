myset: assembler.o read_file.o
	gcc -g -Wall -ansi -pedantic assembler.o read_file.o -o assembler

assembler.o: assembler.c read_file.h
	gcc -c -Wall -ansi -pedantic assembler.c -o assembler.o

read_file.o: read_file.c read_file.h
	gcc -c -Wall -ansi -pedantic read_file.c -o read_file.o
