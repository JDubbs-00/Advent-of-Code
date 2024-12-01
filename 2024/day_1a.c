#include "../utl.h"

//#define TEST
#define REAL

// GUESSES:

int main(int argc, char *argv[])
{
    clock_t start = clock();
    FILE *fp;
    char *line = _malloc(MAX_LINE_LEN);
    int res, size, *left, *right, i;

    #ifdef TEST
    fp = fopen("input/day_1_example_input.txt", "r");
    size = 6;
    #endif
    #ifdef REAL
    fp = fopen("input/day_1_input.txt", "r");
    size = 1000;
    #endif
    if (fp == NULL)
    {
        printf("Input file not found.");
        return 0;
    }

    left = _malloc(size * sizeof(int));
    right = _malloc(size * sizeof(int));
    i = 0;

    while ((fgets(line, MAX_LINE_LEN, fp)) != NULL)
    {
        clean_input(line);
        //printf("%s", line);

        left[i] = str_to_int(line, ' ');
        right[i] = str_to_int(line + get_x_occurence(line, ' ', 3) + 1, '\0');
        i++;
    }

    merge_sort(left, 0, size - 1);
    merge_sort(right, 0, size - 1);

    for (i = 0, res = 0; i < size; i++)
    {
        res += ABS(right[i] - left[i]);
    }

    if (ferror(fp)) printf("Error reading file.");
    fclose(fp);
    emancipation_proclamation();
    print_time(start, clock());
    print_malloced_mem();
    print_results("Total distances between lists", res);
}
