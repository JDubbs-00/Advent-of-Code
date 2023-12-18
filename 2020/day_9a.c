
#include "../utl.h"

//#define TEST
#define REAL

static void print_results(char *msg, long long int res)
{
    printf("%s: %lld\n", msg, res);
}

static bool sums_up(long long int *arr, int size, long long int target)
{
    int i, j;
    long long int n;
    for (i = 0; i < size - 1; i++)
    {
        n = arr[i];
        for (j = i + 1; j < size; j++)
        {
            if (n + arr[j] == target)
            {
                return true;
            }
        }
    }
    return false;
}

int main(int argc, char *argv[])
{
    long long int start = GetTickCount64();
    FILE *fp;
    char *line = NULL;
    size_t len = 0;
    int length, size, preamble, i;
    int c = 0;
    long long int *nums;
    long long int weakness;

    #ifdef TEST
    fp = fopen("input/day_9_example_input.txt", "r");
    size = 20;
    preamble = 5;
    #endif
    #ifdef REAL
    fp = fopen("input/day_9_input.txt", "r");
    size = 1000;
    preamble = 25;
    #endif
    if (fp == NULL)
    {
        printf("Input file not found.");
        return 0;
    }

    nums = malloc(size * sizeof(long long int));
    while ((length = getline(&line, &len, fp)) != -1)
    {
        clean_input(line);
        nums[c] = atoll(line);
        c++;
    }

    for (i = preamble; i < size; i++)
    {
        if (!sums_up(nums + i - preamble, preamble, nums[i]))
        {
            weakness = nums[i];
            break;
        }
    }

    fclose(fp);
    if (line) free(line);
    print_time(start, GetTickCount64());
    print_results("First number in the list which is not the sum of two of the numbers before it", weakness);
}
