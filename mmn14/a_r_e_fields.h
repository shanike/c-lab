#ifndef A_R_E_FIELDS_H
#define A_R_E_FIELDS_H

#include "global_variables.h"

#define FIELD_A_INDEX 2
#define FIELD_R_INDEX 1
#define FIELD_E_INDEX 0

/* Turns on the A field of the given word */
void turn_on_a(word *num);

/* Turns on the R field of the given word */
void turn_on_r(word *num);

/* Turns on the E field of the given word */
void turn_on_e(word *num);

#endif
