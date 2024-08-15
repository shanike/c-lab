#include "bitwise_functions.h"
#include "./a_r_e_fields.h"

void turn_on_a(word *num)
{
    set_bit(num, FIELD_A_INDEX, 1);
}

void turn_on_r(word *num)
{
    set_bit(num, FIELD_R_INDEX, 1);
}

void turn_on_e(word *num)
{
    set_bit(num, FIELD_E_INDEX, 1);
}
