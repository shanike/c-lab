- Documentation of functions is in the corresponding function prototype in the header file.

## TODO (core):

- Check whether the malloc in create_new_file_name is valid also in ubuntu 16. (Reason to worry: returning a pointer to a local `malloc`ed variable)

### entries .ent (=export)

= list of all labels that were `.entry`ed

- on second pass, if encountered an `.entry` directive -> then find and update the label in `labels_table` to have feature_type of `ENTRY`
- **OR** on first pass, if encountered an `.entry` directive -> then add the label to (a new) `entry_labels_table`.

  (which-ever is easier.)

- Then, anyway,  
  on second pass, go over `entry_labels_table` OR over `labels_table.filter(feature_type == ENTRY)` -> and write them to .ent file.

### externs .ext (=import)

= list of all usages of external labels

- on second pass, go over input (.am) file and find all labels with feature_type of `EXTERNAL` -> and write them and their address to .ext file.

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
