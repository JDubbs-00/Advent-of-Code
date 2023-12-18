
#include "../utl.h"

//#define TEST
#define REAL

static void print_results(int n)
{
    printf("Sum of group counts: %d\n", n);
}

int main(int argc, char *argv[])
{
    long long int start = GetTickCount64();
    FILE *fp;
    char *line = NULL;
    size_t len = 0;
    int length, i;
    int sum = 0;
    bool *hash;

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

    hash = malloc(26 * sizeof(bool));
    clear_bool_arr(hash, 26);
    while ((length = getline(&line, &len, fp)) != -1)
    {
        clean_input(line);
        if (is_empty_get_line(line))
        {
            sum += count_hash(hash, 26);
            clear_bool_arr(hash, 26);
        }
        else
        {
            for (i = 0; line[i] != '\0'; i++)
            {
                hash[HASH_LOWER_CHAR(line[i])] = true;
            }
        }
    }

    sum += count_hash(hash, 26);

    fclose(fp);
    if (line) free(line);
    print_time(start, GetTickCount64());
    print_results(sum);
}
