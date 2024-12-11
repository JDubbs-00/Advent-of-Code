#include "../utl.h"

//#define TEST
#define REAL

// GUESSES:
// 10435769 - low
// 169819321 - low

int main(int argc, char *argv[])
{
    clock_t start = clock();
    FILE *fp;
    char *line;
    int size, i, j, k, id, n, *disk, c;
    long long int res;

    #ifdef TEST
    fp = fopen("input/day_9_example_input.txt", "r");
    size = 20;
    #endif
    #ifdef REAL
    fp = fopen("input/day_9_input.txt", "r");
    size = 20000;
    #endif
    if (fp == NULL)
    {
        printf("Input file not found.");
        return 0;
    }

    line = _malloc(size + 1);
    disk = _malloc(size * 9 * sizeof(int));

    while ((fgets(line, size, fp)) != NULL)
    {
        clean_input(line);
        //printf("%s", line);
    }

    for (i = 0, j = 0, id = 0; i < size; i++)
    {
        if (is_even(i))
        {
            c = id;
            id++;
        }
        else
        {
            c = -1;
        }
        for (n = CHAR_TO_NUM(line[i]), k = 0; k < n; j++, k++)
        {
            disk[j] = c;
        }
    }

    size = j;
    res = 0;
    i = 0;
    j--;
    while (i < j)
    {
        while (disk[i] != -1 && i < j)
        {
            i++;
        }
        while (disk[j] == -1 && i < j)
        {
            j--;
        }
        if (i >= j)
        {
            break;
        }
        disk[i] = disk[j];
        disk[j] = -1;
    }

    printf("size: %d\n", size);

    for (i = 0; i < size; i++)
    {
        if (disk[i] != -1)
        {
            res += (long long int)(disk[i] * i);
        }
    }

    if (ferror(fp)) printf("Error reading file.");
    fclose(fp);
    emancipation_proclamation();
    print_time(start, clock());
    print_malloced_mem();
    print_results_ll("Filesystem checksum", res);
}
