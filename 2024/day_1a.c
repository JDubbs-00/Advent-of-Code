#include "../utl.h"

#define TEST
//#define REAL

// GUESSES:

int main(int argc, char *argv[])
{
    long long int start = GetTickCount64();
    FILE *fp;
    char *line = _malloc(MAX_LINE_LEN);
    int res;

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

    

    while ((fgets(line, MAX_LINE_LEN, fp)) != NULL)
    {
        clean_input(line);
        //printf("%s", line);
    }

    

    if (ferror(fp)) printf("Error reading file.");
    fclose(fp);
    if (line) free(line);
    emancipation_proclamation();
    print_time(start, GetTickCount64());
    print_malloced_mem();
    print_results("", res);
}
