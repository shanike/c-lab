assembler: objs/assembler.o objs/read_file.o
	gcc -g -Wall -ansi -pedantic objs/assembler.o objs/read_file.o -o assembler

objs/assembler.o: assembler.c read_file.h
	gcc -c -Wall -ansi -pedantic assembler.c -o objs/assembler.o

objs/read_file.o: read_file.c read_file.h
	gcc -c -Wall -ansi -pedantic read_file.c -o objs/read_file.o
