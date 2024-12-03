#include "../utl.h"

//#define TEST
#define REAL

// GUESSES:

int main(int argc, char *argv[])
{
    clock_t start = clock();
    FILE *fp;
    int res, max_line_len, *arr, cnt, i, n1, n2, j;
    char num_str[4];

#ifdef TEST
    fp = fopen("input/day_3_example_input.txt", "r");
    max_line_len = 75;
#endif
#ifdef REAL
    fp = fopen("input/day_3_input.txt", "r");
    max_line_len = 3500;
#endif
    if (fp == NULL)
    {
        printf("Input file not found.");
        return 0;
    }

    char *line = _malloc(max_line_len);

    res = 0;
    while ((fgets(line, max_line_len, fp)) != NULL)
    {
        clean_input(line);
        // printf("%s", line);

        cnt = get_occurences_str(line, "mul", &arr, (max_line_len / 3) + 1);
        // print_int_arr(arr, cnt);
        for (i = 0; i < cnt; i++)
        {
            arr[i] += 3;
            if (line[arr[i]] == '(')
            {
                n1 = 0;
                n2 = 0;
                arr[i] += 1;
                for (j = 0; j < 3 && is_num(line[arr[i] + j]); j++)
                {
                    num_str[j] = line[arr[i] + j];
                }
                num_str[j] = '\0';
                if (line[arr[i] + j] == ',')
                {
                    n1 = str_to_int(num_str, '\0');
                    arr[i] += j;
                    if (line[arr[i]] == '\0')
                    {
                        break;
                    }
                    arr[i]++;
                    for (j = 0; j < 3 && is_num(line[arr[i] + j]); j++)
                    {
                        num_str[j] = line[arr[i] + j];
                    }
                    num_str[j] = '\0';
                    if (line[arr[i] + j] == ')')
                    {
                        n2 = str_to_int(num_str, '\0');
                        res += (n1 * n2);
                    }
                }
            }
        }
    }

    if (ferror(fp))
        printf("Error reading file.");
    fclose(fp);
    emancipation_proclamation();
    print_time(start, clock());
    print_malloced_mem();
    print_results("Uncorrupted 'mul' instructions sum", res);
}
