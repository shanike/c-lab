- Documentation of functions is in the corresponding function prototype in the header file.

## TODO (core):

### entries .ent (=export)

= list of all labels that were `.entry`ed

- on second pass, if encountered an `.entry` directive -> then find and update the label in `labels_table` to have feature_type of `ENTRY`
- **OR** on first pass, if encountered an `.entry` directive -> then add the label to (a new) `entry_labels_table`.

  (which-ever is easier.)

- Then, anyway,  
  on second pass, go over `entry_labels_table` OR over `labels_table.filter(feature_type == ENTRY)` -> and write them to .ent file.

### externs .ext (=import)

= list of all usages of external labels

- on second pass, go over input (.am) file and find all labels with feature_type of `EXTERNAL` -> and white them to .ext file.

## TODO (chore):

- remove includes from .c files that are already included in the header files
