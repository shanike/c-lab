- Documentation of functions is in the corresponding function prototype in the header file.

## TODO (core):

- Check whether the malloc in create_new_file_name is valid also in ubuntu 16. (Reason to worry: returning a pointer to a local `malloc`ed variable)

## TODO (chore):

- remove includes from .c files that are already included in the header files

## Tests

- [ ] Negative .data values
- [ ] Weird .string values
- [ ] Quotes in .string values
- [ ] .data with no values
- [ ] .string with no values
- [ ] Multi commas
- [ ] Label with no content
- [ ] Using a label that was not defined in operation
- [ ] Using a label that was not defined in .entry/.extern

- [ ] What should happen if calling the assembler with a file "file.as"?
- [ ] Check max length of line
