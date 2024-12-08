#include "../utl.h"

//#define TEST
#define REAL

// GUESSES:

bool try(long long int n, long long int *vals, int size, long long int target)
{
    if (n > target)
    {
        return false;
    }
    if (size == 0)
    {
        return n == target;
    }
    if (try(n * vals[0], vals + 1, size - 1, target))
    {
        return true;
    }
    return try(n + vals[0], vals + 1, size - 1, target);
}

int main(int argc, char *argv[])
{
    clock_t start = clock();
    FILE *fp;
    char *line = _malloc(MAX_LINE_LEN);
    int size, i, j;
    long long int res;
    long long int *results;
    int *sizes;
    long long int **vals;

    #ifdef TEST
    fp = fopen("input/day_7_example_input.txt", "r");
    size = 9;
    #endif
    #ifdef REAL
    fp = fopen("input/day_7_input.txt", "r");
    size = 850;
    #endif
    if (fp == NULL)
    {
        printf("Input file not found.");
        return 0;
    }

    results = _malloc(size * sizeof(long long int));
    sizes = _malloc(size * sizeof(int));
    vals = _malloc(size * sizeof(long long int *));
    i = 0;
    while ((fgets(line, MAX_LINE_LEN, fp)) != NULL)
    {
        clean_input(line);
        //printf("%s", line);

        j = find_in_str(line, ':');
        results[i] = str_to_ll(line, ':');
        sizes[i] = split_to_ll_unknown_size(&vals[i], line + j + 2, ' ');

        i++;
    }

    for (i = 0, res = 0; i < size; i++)
    {
        if (try(vals[i][0] * vals[i][1], vals[i] + 2, sizes[i] - 2, results[i])
         || try(vals[i][0] + vals[i][1], vals[i] + 2, sizes[i] - 2, results[i]))
        {
            // print_int_arr(vals[i], sizes[i]);
            res += results[i];
        }
    }

    if (ferror(fp)) printf("Error reading file.");
    fclose(fp);
    emancipation_proclamation();
    print_time(start, clock());
    print_malloced_mem();
    print_results_ll("Total calibration result", res);
}
