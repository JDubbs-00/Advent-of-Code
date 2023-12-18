
#include "../utl.h"

//#define TEST
#define REAL

static void print_results(char *msg, int res)
{
    printf("%s: %d\n", msg, res);
}

int main(int argc, char *argv[])
{
    long long int start = GetTickCount64();
    FILE *fp;
    char *line = NULL;
    size_t len = 0;
    int length, res, size;
    int i = 1;
    int diff1 = 0;
    int diff3 = 0;
    int *jolts;

    #ifdef TEST
    fp = fopen("input/day_10_example_input.txt", "r");
    size = 31;
    #endif
    #ifdef REAL
    fp = fopen("input/day_10_input.txt", "r");
    size = 97;
    #endif
    if (fp == NULL)
    {
        printf("Input file not found.");
        return 0;
    }

    size += 2;
    jolts = malloc(size * sizeof(int));
    jolts[0] = 0;
    while ((length = getline(&line, &len, fp)) != -1)
    {
        clean_input(line);
        jolts[i] = atoi(line);
        i++;
    }
    jolts[i] = get_max(jolts, i) + 3;

    merge_sort(jolts, 0, size - 1);
    for (i = 0; i < size - 1; i++)
    {
        if (jolts[i + 1] - jolts[i] == 1)
        {
            diff1++;
        }
        else
        {
            diff3++;
        }
    }
    //printf("1 jolt differences: %d\n", diff1);
    //printf("3 jolt differences: %d\n", diff3);
    res = diff1 * diff3;

    fclose(fp);
    if (line) free(line);
    free(jolts);
    print_time(start, GetTickCount64());
    print_results("1 jolt differences * 3 jolt differences", res);
}
