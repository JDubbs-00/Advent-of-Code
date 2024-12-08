#include "../utl.h"

//#define TEST
#define REAL

// GUESSES:

int main(int argc, char *argv[])
{
    clock_t start = clock();
    FILE *fp;
    char *line = _malloc(MAX_LINE_LEN);
    int res, rules_cnt, i, **rules, *nums, size, j, k, *sorted, insert, m;
    bool pass;

    #ifdef TEST
    fp = fopen("input/day_5_example_input.txt", "r");
    rules_cnt = 21;
    #endif
    #ifdef REAL
    fp = fopen("input/day_5_input.txt", "r");
    rules_cnt = 1176;
    #endif
    if (fp == NULL)
    {
        printf("Input file not found.");
        return 0;
    }

    i = 0;
    res = 0;
    rules = _malloc(rules_cnt * sizeof(int *));
    while ((fgets(line, MAX_LINE_LEN, fp)) != NULL)
    {
        clean_input(line);
        //printf("%s", line);
        if( i <= rules_cnt )
        {
            rules[i] = _malloc(2 * sizeof(int));
            split_to_int(rules[i], 2, line, '|');
        }
        else if (i != rules_cnt)
        {
            size = split_to_int_unknown_size(&nums, line, ',');
            pass = true;
            for (j = 1; j < size && pass; j++)
            {
                for (k = 0; k < rules_cnt && pass; k++)
                {
                    if (nums[j] == rules[k][0] && is_in_int_arr(nums, j, rules[k][1]))
                    {
                        pass = false;
                    }
                }
            }
            if (!pass)
            {
                sorted = _malloc(size * sizeof(int));
                for (j = 0; j < size; j++)
                {
                    insert = 0;
                    for (k = 0; k < j; k++)
                    {
                        for (m = 0; m < rules_cnt; m++)
                        {
                            if (rules[m][1] == nums[j] && rules[m][0] == sorted[insert])
                            {
                                insert++;
                                m = -1;
                            }
                        }
                    }
                    insert_into_arr(sorted, j + 1, insert, nums[j]);
                }
                // print_int_arr(sorted, size);
                res += sorted[size / 2];
            }
        }

        i++;
    }

    

    if (ferror(fp)) printf("Error reading file.");
    fclose(fp);
    emancipation_proclamation();
    print_time(start, clock());
    print_malloced_mem();
    print_results("Middle page number sum", res);
}