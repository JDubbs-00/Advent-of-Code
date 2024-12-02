#include "../utl.h"

//#define TEST
#define REAL

// GUESSES:

int main(int argc, char *argv[])
{
    clock_t start = clock();
    FILE *fp;
    char *line = _malloc(MAX_LINE_LEN);
    int res, reports_cnt, **reports, i, **diffs, max_diff, *sizes;

    #ifdef TEST
    fp = fopen("input/day_2_example_input.txt", "r");
    reports_cnt = 6;
    #endif
    #ifdef REAL
    fp = fopen("input/day_2_input.txt", "r");
    reports_cnt = 1000;
    #endif
    if (fp == NULL)
    {
        printf("Input file not found.");
        return 0;
    }

    reports = _malloc(reports_cnt * sizeof(int *));
    sizes = _malloc(reports_cnt * sizeof(int));

    i = 0;
    while ((fgets(line, MAX_LINE_LEN, fp)) != NULL)
    {
        clean_input(line);
        //printf("%s", line);

        sizes[i] = split_to_int_unknown_size(&reports[i], line, ' ');
        i++;
    }

    res = 0;
    diffs = _malloc(reports_cnt * sizeof(int *));
    for (i = 0; i < reports_cnt; i++)
    {
        diffs[i] = get_diffs(reports[i], sizes[i]);
        max_diff = 0;
        if (is_increasing(reports[i], sizes[i]))
        {
            max_diff = get_min(diffs[i], sizes[i] - 1) * -1;
        }
        else if (is_decreasing(reports[i], sizes[i]))
        {
            max_diff = get_max(diffs[i], sizes[i] - 1);
        }

        if (max_diff == 1 || max_diff == 2 || max_diff == 3)
        {
            res++;
        }
    }

    if (ferror(fp)) printf("Error reading file.");
    fclose(fp);
    emancipation_proclamation();
    print_time(start, clock());
    print_malloced_mem();
    print_results("Number of safe reports", res);
}
