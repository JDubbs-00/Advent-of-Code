
#include "../utl.h"

//#define TEST
#define REAL

#define EMPTY 'L'
#define OCCUPIED '#'
#define FLOOR '.'

static int rows;
static int cols;

static void print_results(char *msg, int res)
{
    printf("%s: %d\n", msg, res);
}

static void copy_grid(char **grid, char **copy, int cols, int rows)
{
    for (int i = 0; i < rows; i++)
    {
        copy_str(grid[i], copy[i], cols);
    }
}

static bool is_empty(char c)
{
    return c == EMPTY;
}

static bool is_occupied(char c)
{
    return c == OCCUPIED;
}

static char look(char **grid, int i, int j, int x, int y)
{
    do
    {
        i += x;
        j += y;
        if (i < 0 || j < 0 || i == rows || j == cols)
        {
            return FLOOR;
        }
    } while (grid[i][j] == '.');
    return grid[i][j];
}

static bool rule1(char **grid, int i, int j)
{
    if (!is_empty(grid[i][j]))
    {
        return false;
    }
    if (is_occupied(look(grid, i, j, -1, -1))) return false;
    if (is_occupied(look(grid, i, j, -1, 0))) return false;
    if (is_occupied(look(grid, i, j, -1, 1))) return false;
    if (is_occupied(look(grid, i, j, 0, -1))) return false;
    if (is_occupied(look(grid, i, j, 0, 1))) return false;
    if (is_occupied(look(grid, i, j, 1, -1))) return false;
    if (is_occupied(look(grid, i, j, 1, 0))) return false;
    if (is_occupied(look(grid, i, j, 1, 1))) return false;
    return true;
}

static bool rule2(char **grid, int i, int j)
{
    int c;
    if (!is_occupied(grid[i][j]))
    {
        return false;
    }
    c = 0;
    if (is_occupied(look(grid, i, j, -1, -1))) c++;
    if (is_occupied(look(grid, i, j, -1, 0))) c++;
    if (is_occupied(look(grid, i, j, -1, 1))) c++;
    if (is_occupied(look(grid, i, j, 0, -1))) c++;
    if (is_occupied(look(grid, i, j, 0, 1))) c++;
    if (is_occupied(look(grid, i, j, 1, -1))) c++;
    if (is_occupied(look(grid, i, j, 1, 0))) c++;
    if (is_occupied(look(grid, i, j, 1, 1))) c++;

    return c >= 5;
}

int main(int argc, char *argv[])
{
    long long int start = GetTickCount64();
    FILE *fp;
    char *line = NULL;
    size_t len = 0;
    int length, res, j;
    int i = 0;
    char **grid;
    char **copy;
    bool change = true;

    #ifdef TEST
    fp = fopen("input/day_11_example_input.txt", "r");
    rows = 10;
    cols = 10;
    #endif
    #ifdef REAL
    fp = fopen("input/day_11_input.txt", "r");
    rows = 92;
    cols = 91;
    #endif
    if (fp == NULL)
    {
        printf("Input file not found.");
        return 0;
    }

    grid = init_2d_char(cols, rows);
    copy = init_2d_char(cols, rows);
    while ((length = getline(&line, &len, fp)) != -1)
    {
        clean_input(line);
        copy_str(line, grid[i], cols);
        i++;
    }

    while (change)
    {
        change = false;
        copy_grid(grid, copy, cols, rows);
        for (i = 0; i < rows; i++)
        {
            for (j = 0; j < cols; j++)
            {
                if (rule1(copy, i, j))
                {
                    grid[i][j] = OCCUPIED;
                    change = true;
                }
                else if (rule2(copy, i, j))
                {
                    grid[i][j] = EMPTY;
                    change = true;
                }
            }
        }
    }

    res = 0;
    for (i = 0; i < rows; i++)
    {
        for (j = 0; j < cols; j++)
        {
            if (is_occupied(grid[i][j]))
            {
                res++;
            }
        }
    }

    fclose(fp);
    if (line) free(line);
    free_2d_char(grid, rows);
    free_2d_char(copy, rows);
    print_time(start, GetTickCount64());
    print_results("Number of seats occupied after people stop moving around", res);
}
