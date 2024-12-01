#include "../utl.h"

//#define TEST
#define REAL

// GUESSES:

int main(int argc, char *argv[])
{
    clock_t start = clock();
    FILE *fp;
    char *line = _malloc(MAX_LINE_LEN);
    int res, size, *left, *right, i, j, k;

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

    for (i = 0, res = 0; i < size; i++)
    {
        for (j = 0, k = 0; j < size; j++)
        {
            if (left[i] == right[j])
            {
                k++;
            }
        }

        res += (left[i] * k);
    }

    if (ferror(fp)) printf("Error reading file.");
    fclose(fp);
    emancipation_proclamation();
    print_time(start, clock());
    print_malloced_mem();
    print_results("Similarity score", res);
}
