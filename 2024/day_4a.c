#include "../utl.h"

//#define TEST
#define REAL

// GUESSES:

static char xmas[5] = "XMAS";
static char **grid;
static int size;

bool left(int i, int j, int index)
{
    if (grid[i][j] != xmas[index])
    {
        return false;
    }
    if (index == 3)
    {
        return true;
    }
    return left(i, j - 1, index + 1);
}

bool right(int i, int j, int index)
{
    if (grid[i][j] != xmas[index])
    {
        return false;
    }
    if (index == 3)
    {
        return true;
    }
    return right(i, j + 1, index + 1);
}

bool up(int i, int j, int index)
{
    if (grid[i][j] != xmas[index])
    {
        return false;
    }
    if (index == 3)
    {
        return true;
    }
    return up(i - 1, j, index + 1);
}

bool down(int i, int j, int index)
{
    if (grid[i][j] != xmas[index])
    {
        return false;
    }
    if (index == 3)
    {
        return true;
    }
    return down(i + 1, j, index + 1);
}

bool up_left(int i, int j, int index)
{
    if (grid[i][j] != xmas[index])
    {
        return false;
    }
    if (index == 3)
    {
        return true;
    }
    return up_left(i - 1, j - 1, index + 1);
}

bool up_right(int i, int j, int index)
{
    if (grid[i][j] != xmas[index])
    {
        return false;
    }
    if (index == 3)
    {
        return true;
    }
    return up_right(i - 1, j + 1, index + 1);
}

bool down_left(int i, int j, int index)
{
    if (grid[i][j] != xmas[index])
    {
        return false;
    }
    if (index == 3)
    {
        return true;
    }
    return down_left(i + 1, j - 1, index + 1);
}

bool down_right(int i, int j, int index)
{
    if (grid[i][j] != xmas[index])
    {
        return false;
    }
    if (index == 3)
    {
        return true;
    }
    return down_right(i + 1, j + 1, index + 1);
}

int main(int argc, char *argv[])
{
    clock_t start = clock();
    FILE *fp;
    char *line = _malloc(MAX_LINE_LEN);
    int res, i, j;
    bool l, r, u, d;

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

    for (i = 0, res = 0; i < size; i++)
    {
        u = i > 2;
        d = i < size - 3;
        for (j = 0; j < size; j++)
        {
            if (grid[i][j] != xmas[0])
            {
                continue;
            }

            l = j > 2;
            r = j < size - 3;
            if (l && left(i, j, 0))
            {
                res++;
            }
            if (r && right(i, j, 0))
            {
                res++;
            }
            if (u && up(i, j, 0))
            {
                res++;
            }
            if (d && down(i, j, 0))
            {
                res++;
            }
            if (u && l && up_left(i, j, 0))
            {
                res++;
            }
            if (u && r && up_right(i, j, 0))
            {
                res++;
            }
            if (d && l && down_left(i, j, 0))
            {
                res++;
            }
            if (d && r && down_right(i, j, 0))
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
