/* Set values vary between 0 and 127 */
#define MAX_NUMBER 128
#define BYTE_SIZE 8
#define NUM_OF_BYTES MAX_NUMBER / BYTE_SIZE

/* An array of 8 characters, representing 128 digits */
typedef char ELEMENTS[NUM_OF_BYTES];

typedef struct set
{
    ELEMENTS elements;
    int is_empty;
} SET;

void read_set(SET *, int[]);
void print_set(SET *);
void union_set(SET, SET, SET);
void intersect_set(SET, SET, SET);
void sub_set(SET, SET, SET);
void symdiff_set(SET, SET, SET);