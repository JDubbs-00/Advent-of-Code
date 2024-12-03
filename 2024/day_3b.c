#include "../utl.h"

//#define TEST
#define REAL

// GUESSES:
// 105264641 - HIGH

int main(int argc, char *argv[])
{
    clock_t start = clock();
    FILE *fp;
    int res, max_line_len, *arr, cnt, i, n1, n2, j, *dos, *donts, m, dos_cnt, donts_cnt;
    char num_str[4];
    bool *enabled, enable;

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
    enabled = _malloc(max_line_len * sizeof(bool));

    res = 0;
    enable = true;
    while ((fgets(line, max_line_len, fp)) != NULL)
    {
        clean_input(line);
        // printf("%s", line);

        cnt = get_occurences_str(line, "mul", &arr, (max_line_len / 3) + 1);
        dos_cnt = get_occurences_str(line, "do()", &dos, (max_line_len / 4) + 1);
        donts_cnt = get_occurences_str(line, "don't()", &donts, (max_line_len / 7) + 1);
        // print_int_arr(dos, dos_cnt);
        // print_int_arr(donts, donts_cnt);
        for (m = 0; line[m] != '\0'; m++)
        {
            if(is_in_int_arr(dos, dos_cnt, m))
            {
                dos++;
                dos_cnt--;
                enable = true;
            }
            if (is_in_int_arr(donts, donts_cnt, m))
            {
                donts++;
                donts_cnt--;
                enable = false;
            }
            enabled[m] = enable;
        }
        //print_bool_arr(enabled, m);
        for (i = 0; i < cnt; i++)
        {
            arr[i] += 3;
            if (enabled[arr[i]])
            {
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
    }

    if (ferror(fp))
        printf("Error reading file.");
    fclose(fp);
    emancipation_proclamation();
    print_time(start, clock());
    print_malloced_mem();
    print_results("Uncorrupted enabled 'mul' instructions sum", res);
}
