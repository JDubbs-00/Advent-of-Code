#include "../utl.h"

//#define TEST
#define REAL

// GUESSES:
// 143 - low

static int size;
static char **grid;
static bool **seen;

bool faces_up(char c)
{
    return c == '|' || c == 'L' || c == 'J' || c == 'S';
}

bool faces_down(char c)
{
    return c == '|' || c == '7' || c == 'F' || c == 'S';
}

bool faces_right(char c)
{
    return c == '-' || c == 'L' || c == 'F' || c == 'S';
}

bool faces_left(char c)
{
    return c == '-' || c == 'J' || c == '7' || c == 'S';
}

bool is_in_range(int r, int c)
{
    return r >= 0 && r < size && c >= 0 && c < size;
}

int main(int argc, char *argv[])
{
    long long int start = GetTickCount64();
    FILE *fp;
    char *line = NULL;
    size_t len = 0;
    int length, res, i, j, steps, r, c;
    direction from;

    #ifdef TEST
    fp = fopen("input/day_10_example_input.txt", "r");
    size = 5;
    #endif
    #ifdef REAL
    fp = fopen("input/day_10_input.txt", "r");
    size = 140;
    #endif
    if (fp == NULL)
    {
        printf("Input file not found.");
        return 0;
    }

    grid = init_2d_char(size, size);
    seen = malloc(size * sizeof(bool *));
    i = 0;
    while ((length = getline(&line, &len, fp)) != -1)
    {
        clean_input(line);
        seen[i] = malloc(size * sizeof(bool));
        clear_bool_arr(seen[i], size);
        memcpy(grid[i], line, size * sizeof(char));
        j = find_in_str(grid[i], 'S');
        if (j != -1)
        {
            r = i;
            c = j;
        }
        i++;
    }

    for (steps = 0, from = DIRECTION_NONE; !seen[r][c]; steps++)
    {
        seen[r][c] = true;
        //printf("(%d, %d) - %d\n", r, c, steps);
        if (from != DOWN && is_in_range(r - 1, c) && faces_up(grid[r][c]) && faces_down(grid[r - 1][c]))
        {
            //printf("Going up\n");
            from = UP;
            r--;
        }
        else if (from != UP && is_in_range(r + 1, c) && faces_down(grid[r][c]) && faces_up(grid[r + 1][c]))
        {
            //printf("Going down\n");
            from = DOWN;
            r++;
        }
        else if (from != RIGHT && is_in_range(r, c - 1) && faces_left(grid[r][c]) && faces_right(grid[r][c - 1]))
        {
            //printf("Going left\n");
            from = LEFT;
            c--;
        }
        else
        {
            //printf("Going right\n");
            if (from == LEFT || !is_in_range(r, c + 1) || !faces_right(grid[r][c]) || !faces_left(grid[r][c + 1]))
            {
                printf("ERROR\n");
                return 0;
            }
            from = RIGHT;
            c++;
        }
    }

    res = (steps + (steps % 2 == 1 ? 1 : 0)) / 2;

    fclose(fp);
    if (line) free(line);
    free_2d_char(grid, size);
    for (i = 0; i < size; i++)
    {
        free(seen[i]);
    }
    free(seen);
    print_time(start, GetTickCount64());
    print_results("Total steps", res);
}
