
#include "../utl.h"

//#define TEST
#define REAL

static void print_results(char *msg, long long int res)
{
    printf("%s: %lld\n", msg, res);
}

int main(int argc, char *argv[])
{
    long long int start = GetTickCount64();
    FILE *fp;
    char *line = NULL;
    size_t len = 0;
    int length, size, j;
    int i = 1;
    int diff1 = 0;
    int diff3 = 0;
    int *jolts;
    long long int *connections;

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
    connections = malloc(size * sizeof(long long int));
    jolts[0] = 0;
    while ((length = getline(&line, &len, fp)) != -1)
    {
        clean_input(line);
        jolts[i] = atoi(line);
        i++;
    }
    jolts[i] = get_max(jolts, i) + 3;

    merge_sort(jolts, 0, size - 1);
    connections[size - 1] = 1;
    for (i = size - 2; i >= 0; i--)
    {
        connections[i] = 0;
        for (j = i + 1; j < size && jolts[j] - jolts[i] <= 3; j++)
        {
            connections[i] += connections[j];
        }
    }

    fclose(fp);
    if (line) free(line);
    free(jolts);
    print_time(start, GetTickCount64());
    print_results("Possible combinations of adaptors", connections[0]);
}
