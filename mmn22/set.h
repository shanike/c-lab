/* Set values vary between 0 and 127 */
#define MAX_NUMBER 128
#define BYTE_SIZE 8
#define NUM_OF_BYTES MAX_NUMBER / BYTE_SIZE
#define MAX_SET_NAME 5

/* An array of 8 characters, representing 0-127, 128 digits */
typedef struct
{
    char members[NUM_OF_BYTES];
    char name[MAX_SET_NAME];
} Set;

void read_set(Set *, int *);
void print_set(Set *);
void union_set(Set *, Set *, Set *);
void intersect_set(Set *, Set *, Set *);
void sub_set(Set *, Set *, Set *);
void symdiff_set(Set *, Set *, Set *);

typedef enum
{
    READ_SET,
    PRINT_SET,
    UNION_SET,
    INTERSECT_SET,
    SUB_SET,
    SYMDIFF_SET
} Command;
