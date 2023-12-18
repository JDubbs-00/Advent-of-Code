
#include "../utl.h"

//#define TEST
#define REAL

static void print_results(int n)
{
    printf("# of valid passwords: %d", n);
}

bool is_valid(char *s, int index1, int index2, char target)
{
    index1--;
    index2--;
    return s[index1] == target ^ s[index2] == target;
}

int main(int argc, char *argv[])
{
    long long int start = GetTickCount64();
    FILE *fp;
    char *line = NULL;
    size_t len = 0;
    int length, index1, index2, i;
    int valid = 0;

    #ifdef TEST
    fp = fopen("input/day_2_example_input.txt", "r");
    #endif
    #ifdef REAL
    fp = fopen("input/day_2_input.txt", "r");
    #endif
    if (fp == NULL)
    {
        printf("Input file not found.");
        return 0;
    }

    while ((length = getline(&line, &len, fp)) != -1)
    {
        index1 = string_to_int(line, 0, '-');
        index2 = string_to_int(line, (index1 < 10 ? 2 : 3), ' ');
        i = find_in_string(line, ':');
        if(is_valid(line + i + 2, index1, index2, line[i - 1])) valid++;
    }

    fclose(fp);
    if (line) free(line);
    print_time(start, GetTickCount64());
    print_results(valid);
}
