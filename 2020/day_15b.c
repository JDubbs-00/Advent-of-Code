
#include "../utl.h"

//#define TEST
#define REAL

#define NTH_NUM 30000000

/*
Guesses:
3240 - High
*/

typedef struct
{
    int turn;
    bool seen;
} table;

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
    int length, res, size, i, j, prev, prev_turn;
    int *nums;
    const char delimiter = ',';
    table *last = malloc(NTH_NUM * sizeof(table));

    #ifdef TEST
    fp = fopen("input/day_15_example_input.txt", "r");
    #endif
    #ifdef REAL
    fp = fopen("input/day_15_input.txt", "r");
    #endif
    if (fp == NULL)
    {
        printf("Input file not found.");
        return 0;
    }

    while ((length = getline(&line, &len, fp)) != -1)
    {
        clean_input(line);
        size = count_occurences(line, delimiter);
        nums = malloc(size * sizeof(int));
        size = split_to_int(nums, size, line, delimiter);
    }

    memset(last, 0, NTH_NUM * sizeof(table));
    for (i = 0; i < size - 1; i++)
    {
        last[nums[i]].seen = true;
        last[nums[i]].turn = i;
    }
    /*printf("1st number is 0, never spoken before\n");
    printf("2nd number is 3, never spoken before\n");
    printf("3rd number is 6, never spoken before\n");*/

    for (i = size, prev = nums[size - 1]; i < NTH_NUM; i++)
    {
        if (last[prev].seen)
        {
            j = i - 1 - last[prev].turn;
            //printf("%dth number is %d, %d spoken before on turn %d\n", i + 1, j, prev, last[prev].turn + 1);
        }
        else
        {
            j = 0;
            //printf("%dth number is %d, %d never spoken before\n", i + 1, j, prev);
        }
        //printf("%d\n", j);
        last[prev].turn = i - 1;
        last[prev].seen = true;
        prev = j;
    }

    res = prev;

    fclose(fp);
    if (line) free(line);
    free(nums);
    free(last);
    print_time(start, GetTickCount64());
    print_results("30000000th number", res);
}
