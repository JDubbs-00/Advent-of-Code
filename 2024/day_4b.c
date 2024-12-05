#include "../utl.h"

//#define TEST
#define REAL

// GUESSES:

static char **grid;
static int size;

int main(int argc, char *argv[])
{
    clock_t start = clock();
    FILE *fp;
    char *line = _malloc(MAX_LINE_LEN);
    int res, i, j, m, s;
    char letters[5];

    #ifdef TEST
    fp = fopen("input/day_4_example_input.txt", "r");
    size = 10;
    #endif
    #ifdef REAL
    fp = fopen("input/day_4_input.txt", "r");
    size = 140;
    #endif
    if (fp == NULL)
    {
        printf("Input file not found.");
        return 0;
    }

    grid = init_2d_char(size + 1, size);    
    i = 0;
    while ((fgets(line, MAX_LINE_LEN, fp)) != NULL)
    {
        clean_input(line);
        //printf("%s", line);

        copy_str(line, grid[i], size);
        i++;
    }

    for (i = 1, res = 0; i < size - 1; i++)
    {
        for (j = 1; j < size - 1; j++)
        {
            if (grid[i][j] != 'A')
            {
                continue;
            }
            
            clear(letters);
            m = 0;
            s = 0;

            letters[0] = grid[i - 1][j - 1];
            letters[1] = grid[i - 1][j + 1];
            letters[2] = grid[i + 1][j - 1];
            letters[3] = grid[i + 1][j + 1];

            m = count_occurences(letters, 'M');
            s = count_occurences(letters, 'S');
            if(s == 2 && m == 2 && letters[0] != letters[3])
            {
                res++;
            }
        }
    }

    if (ferror(fp)) printf("Error reading file.");
    fclose(fp);
    emancipation_proclamation();
    print_time(start, clock());
    print_malloced_mem();
    print_results("XMAS occurences", res);
}
