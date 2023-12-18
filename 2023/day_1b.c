#include "../utl.h"

//#define TEST
#define REAL

int match(char *c)
{
    int i;
    static char nums[9][6] =
    {
        "one",
        "two",
        "three",
        "four",
        "five",
        "six",
        "seven",
        "eight",
        "nine"
    };

    static int lengths[9] =
    {
        3,
        3,
        5,
        4,
        4,
        3,
        5,
        5,
        4
    };

    for (i = 0; i < 9; i++)
    {
        if (str_equals_length(nums[i], c, lengths[i]))
        {
            return i + 1;
        }
    }

    return -1;
}

int main(int argc, char *argv[])
{
    long long int start = GetTickCount64();
    FILE *fp;
    char *line = NULL;
    size_t len = 0;
    int length, res;
    int i, m, n;
    int sum = 0;
    bool first, found;

    #ifdef TEST
    fp = fopen("input/day_1_example_input.txt", "r");
    #endif
    #ifdef REAL
    fp = fopen("input/day_1_input.txt", "r");
    #endif
    if (fp == NULL)
    {
        printf("Input file not found.");
        return 0;
    }

    sum = 0;
    while ((length = getline(&line, &len, fp)) != -1)
    {
        clean_input(line);
        first = true;
        for (i = 0; line[i] != '\0'; i++)
        {
            found = false;
            if (is_num(line[i]))
            {
                n = CHAR_TO_NUM(line[i]);
                found = true;
            }
            else
            {
                m = match(&line[i]);
                if (m != -1)
                {
                    n = m;
                    found = true;
                }
            }

            if (found && first)
            {
                sum += (n * 10);
                first = false;
            }
        }
        sum += n;
    }

    res = sum;

    fclose(fp);
    if (line) free(line);
    print_time(start, GetTickCount64());
    print_results("Sum of all combined digits", res);
}
