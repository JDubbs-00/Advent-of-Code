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
    long long int time, dist, j;

    #ifdef TEST
    fp = fopen("input/day_6_example_input.txt", "r");
    #endif
    #ifdef REAL
    fp = fopen("input/day_6_input.txt", "r");
    #endif
    if (fp == NULL)
    {
        printf("Input file not found.");
        return 0;
    }

    getline(&line, &len, fp);
    clean_input(line);
    remove_char(line, ' ');
    //printf("%s\n", line);
    time = str_to_ll(&line[get_x_occurence(line, ':', 1) + 1], '\0');

    getline(&line, &len, fp);
    clean_input(line);
    remove_char(line, ' ');
    //printf("%s\n", line);
    dist = str_to_ll(&line[get_x_occurence(line, ':', 1) + 1], '\0');

    j = 1;
    while ((time - j) * j <= dist)
    {
        j++;
    }
    res = (time - (j * 2) + 1);

    fclose(fp);
    if (line) free(line);
    print_time(start, GetTickCount64());
    print_results("Ways to beat the record", res);
}
