#include <stdio.h>

void print_bits(unsigned int num)
{
    /* Calculate the number of bits in an unsigned int */
    int num_bits = sizeof(num) * 8;
    int i;
    for (i = num_bits - 1; i >= 0; i--)
    {
        printf("%d", (num >> i) & 1);

        /* Print a space every 4 bits */
        if (i % 4 == 0)
            printf(" ");
    }
}

/*
Bit-wise addition of two non-negative integers.
*/
unsigned int my_add(unsigned int a, unsigned int b)
{
    unsigned int mask = 1;
    unsigned int sum = 0;

    unsigned int carry = 0;

    /* Loop over all bits in a and b */
    while (mask)
    {
        unsigned int a_bit, b_bit, current_bit_sum, current_carry;

        /* Extract the current bit from each digit */
        a_bit = a & mask;
        b_bit = b & mask;

        /* Add the bits */
        current_bit_sum = a_bit ^ b_bit ^ carry;

        /* Update sum with current bit sum */
        sum |= current_bit_sum;

        /* Calculate current carry */
        current_carry = (a_bit & b_bit) | (a_bit & carry) | (b_bit & carry);

        /* Set carry for next iteration */
        carry = current_carry << 1;

        /* Move to the next bit */
        mask = mask << 1;
    }

    printf("Sum in base 2: \n");
    print_bits(a);
    printf("\n + ");
    print_bits(b);
    printf("\n = ");
    print_bits(sum);
    printf("\n");
    return sum;
}

int main()
{
    unsigned int a, b, sum;
    printf("Enter two non-negative integers: ");
    scanf("%u %u", &a, &b);
    printf("sizeof %u\n", sizeof(a));
    printf("You entered: %u and %u\n", a, b);
    sum = my_add(a, b);
    printf("Sum in base 10: %u + %u = %u\n", a, b, sum);
    return 0;
}
