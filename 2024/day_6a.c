#include "../utl.h"

//#define TEST
#define REAL

// GUESSES:

int main(int argc, char *argv[])
{
    clock_t start = clock();
    FILE *fp;
    char *line = _malloc(MAX_LINE_LEN);
    int res, size, i, j, x, y;
    direction dir;
    bool out;
    char **grid;
    bool **visited;

    #ifdef TEST
    fp = fopen("input/day_6_example_input.txt", "r");
    size = 10;
    #endif
    #ifdef REAL
    fp = fopen("input/day_6_input.txt", "r");
    size = 130;
    #endif
    if (fp == NULL)
    {
        printf("Input file not found.");
        return 0;
    }

    grid = _malloc(size * sizeof(char *));
    visited = _malloc(size * sizeof(bool *));
    i = 0;
    out = false;
    dir = UP;
    while ((fgets(line, MAX_LINE_LEN, fp)) != NULL)
    {
        clean_input(line);
        //printf("%s", line);

        grid[i] = _malloc(size * sizeof(char));
        visited[i] = _malloc(size * sizeof(bool));
        copy_str(line, grid[i], size);
        j = find_in_str(line, '^');
        if (j != -1)
        {
            x = i;
            y = j;
        }
        i++;
    }

    while (!out)
    {
        visited[x][y] = true;
        switch (dir)
        {
            case UP:
                if (x == 0)
                {
                    out = true;
                }
                else if (grid[x - 1][y] == '#')
                {
                    dir = RIGHT;
                }
                else
                {
                    x--;
                }
                break;
            case RIGHT:
                if (y == size - 1)
                {
                    out = true;
                }
                else if (grid[x][y + 1] == '#')
                {
                    dir = DOWN;
                }
                else
                {
                    y++;
                }
                break;
            case DOWN:
                if (x == size - 1)
                {
                    out = true;
                }
                else if (grid[x + 1][y] == '#')
                {
                    dir = LEFT;
                }
                else
                {
                    x++;
                }
                break;
            default: //LEFT
                if (y == 0)
                {
                    out = true;
                }
                else if (grid[x][y - 1] == '#')
                {
                    dir = UP;
                }
                else
                {
                    y--;
                }
                break;
        }

    }

    res = 0;
    for (i = 0; i < size; i++)
    {
        for (j = 0; j < size; j++)
        {
            if (visited[i][j])
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
    print_results("Positions visited", res);
}
