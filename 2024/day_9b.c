#include "../utl.h"

//#define TEST
#define REAL

// GUESSES:
// 6907961555952 - high
// 6351802801072 - high
// 6351802164592 - high
// 6351802065320

typedef struct
{
    int index;
    int size;
} block;

int main(int argc, char *argv[])
{
    clock_t start = clock();
    FILE *fp;
    char *line;
    int size, i, j, k, id, n, *disk, c, opening_cnt, block_cnt;
    block *openings, *blocks;
    long long int res;
    bool found;

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
    openings = _malloc(((size / 2) + 1) * sizeof(block));
    blocks = _malloc(((size / 2) + 1) * sizeof(block));
    disk = _malloc(size * 9 * sizeof(int));

    while ((fgets(line, size, fp)) != NULL)
    {
        clean_input(line);
        //printf("%s", line);
    }

    for (i = 0, j = 0, id = 0, block_cnt = 0, opening_cnt = 0; i < size; i++)
    {
        n = CHAR_TO_NUM(line[i]);
        if (is_even(i))
        {
            c = id;
            id++;
            blocks[block_cnt].index = j;
            blocks[block_cnt++].size = n;
        }
        else
        {
            c = -1;
            openings[opening_cnt].index = j;
            openings[opening_cnt++].size = n;
        }
        for (k = 0; k < n; j++, k++)
        {
            disk[j] = c;
        }
    }

    size = j;
    res = 0;
    j = block_cnt - 1;
    while (j > 0)
    {
        i = 0;
        found = false;
        while (i < opening_cnt && openings[i].index < blocks[j].index - 1)
        {
            if (openings[i].size >= blocks[j].size)
            {
                found = true;
                break;
            }
            i++;
        }
        if (found)
        {
            for (k = 0; k < blocks[j].size; k++)
            {
                disk[openings[i].index++] = disk[blocks[j].index + k];
                disk[blocks[j].index + k] = -1;
            }

            openings[i].size -= blocks[j].size;
            if (openings[i].size == 0)
            {
                if (i == 0)
                {
                    openings++;
                }
                else
                {
                    for (; i < opening_cnt; i++)
                    {
                        openings[i] = openings[i + 1];
                    }
                }
                opening_cnt--;
            }
        }
        j--;
        // print_int_arr(disk, size);
    }

    // printf("size: %d\n", size);
    //print_int_arr(disk, size);

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
