
#include "../utl.h"

#define TEST
//#define REAL

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
    int length, res;

    #ifdef TEST
    fp = fopen("input/day_11_example_input.txt", "r");
    #endif
    #ifdef REAL
    fp = fopen("input/day_11_input.txt", "r");
    #endif
    if (fp == NULL)
    {
        printf("Input file not found.");
        return 0;
    }

    while ((length = getline(&line, &len, fp)) != -1)
    {
        clean_input(line);
        //printf("%s", line);
    }



    fclose(fp);
    if (line) free(line);
    print_time(start, GetTickCount64());
    print_results("", res);
}
