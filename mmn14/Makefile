assembler: objs/assembler.o objs/read_file.o
	gcc -g -Wall -ansi -pedantic objs/assembler.o objs/read_file.o -o assembler

objs/assembler.o: assembler.c read_file.h
	gcc -c -Wall -ansi -pedantic assembler.c -o objs/assembler.o

objs/read_file.o: read_file.c read_file.h
	gcc -c -Wall -ansi -pedantic read_file.c -o objs/read_file.o



pre_assembler.o: pre_assembler.c pre_assembler.h globals.h
	gcc -c pre_assembler.c -ansi -Wall -pedantic -g -o $@

list_data_structure.o: list_data_structure.c list_data_structure.h globals.h
	gcc -c list_data_structure.c -ansi -Wall -pedantic -g -o $@

text_functions.o: text_functions.c text_functions.h globals.h
	gcc -c text_functions.c -ansi -Wall -pedantic -g -o $@

generic_file_functions.o: generic_file_functions.c generic_file_functions.h globals.h
	gcc -c generic_file_functions.c -ansi -Wall -pedantic -g -o $@

error_handling.o: error_handling.c error_handling.h globals.h
	gcc -c error_handling.c -ansi -Wall -pedantic -g -o $@

validations.o: validations.c validations.h globals.h
	gcc -c validations.c -ansi -Wall -pedantic -g -o $@

clean:
	rm -rf *.o *.am *.ob *.ent *.ext
