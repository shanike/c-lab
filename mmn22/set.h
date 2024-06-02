/* Set values vary between 0 and 127 */
#define MAX 128

typedef char set[MAX];

void read_set(char *set_name, int *elements);
void print_set(char *set_name);
void union_set(char *set_name1, char *set_name2, char *set_name3);
void intersect_set(char *set_name1, char *set_name2, char *set_name3);
void sub_set(char *set_name1, char *set_name2, char *set_name3);
void symdiff_set(char *set_name1, char *set_name2, char *set_name3);
