#include "../utl.h"

//#define TEST
#define REAL

int main(int argc, char *argv[])
{
    long long int start = GetTickCount64();
    FILE *fp;
    char *line = NULL;
    size_t len = 0;
    int length, res;
    int i = 0;
    int sum = 0;
    int n;
    bool first;

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
            if (is_num(line[i]))
            {
                if (first) {
                    sum += (CHAR_TO_NUM(line[i]) * 10);
                    first = false;
                }
                n = CHAR_TO_NUM(line[i]);
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
