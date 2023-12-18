
#include "../utl.h"

//#define TEST
#define REAL

static void print_results(int n)
{
    printf("# of valid passwords: %d", n);
}

bool is_valid(int *hash, int min, int max, char target)
{
    int n = hash[HASH_LOWER_CHAR(target)];
    return n >= min && n <= max;
}

int main(int argc, char *argv[])
{
    long long int start = GetTickCount64();
    FILE *fp;
    char *line = NULL;
    size_t len = 0;
    int length, min, max, i;
    int valid = 0;
    int hash[26];

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
        min = string_to_int(line, 0, '-');
        max = string_to_int(line, (min < 10 ? 2 : 3), ' ');
        i = find_in_string(line, ':');
        hash_string(line + i + 2, hash);
        if(is_valid(hash, min, max, line[i - 1])) valid++;
    }

    fclose(fp);
    if (line) free(line);
    print_time(start, GetTickCount64());
    print_results(valid);
}
