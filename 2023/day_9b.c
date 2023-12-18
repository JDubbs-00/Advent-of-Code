#include "../utl.h"

//#define TEST
#define REAL

int get_extrapolated_val(int *vals, int size)
{
    int *diffs;
    int i, val;

    if (count_occurences_int(vals, size, 0) == size)
    {
        return 0;
    }

    diffs = malloc((size) * sizeof(int));
    for (int i = 1; i < size; i++)
    {
        diffs[i] = vals[i] - vals[i - 1];
    }

    diffs[0] = get_extrapolated_val(&diffs[1], size - 1);
    //print_int_arr(diffs, size);
    val = vals[0] - diffs[0];
    free(diffs);
    return val;
}

int main(int argc, char *argv[])
{
    long long int start = GetTickCount64();
    FILE *fp;
    char *line = NULL;
    size_t len = 0;
    int length, res, size;
    int *vals;

    #ifdef TEST
    fp = fopen("input/day_9_example_input.txt", "r");
    #endif
    #ifdef REAL
    fp = fopen("input/day_9_input.txt", "r");
    #endif
    if (fp == NULL)
    {
        printf("Input file not found.");
        return 0;
    }

    res = 0;
    while ((length = getline(&line, &len, fp)) != -1)
    {
        clean_input(line);
        size = split_to_int_unknown_size(&vals, line, ' ');
        res += get_extrapolated_val(vals, size);
        free(vals);
    }



    fclose(fp);
    if (line) free(line);
    print_time(start, GetTickCount64());
    print_results("Sum of extrapolated values", res);
}
