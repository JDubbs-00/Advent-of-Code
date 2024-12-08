#include "../utl.h"

//#define TEST
#define REAL

// GUESSES:

int main(int argc, char *argv[])
{
    clock_t start = clock();
    FILE *fp;
    char *line = _malloc(MAX_LINE_LEN);
    int res, size, i, j, x, y, start_x, start_y, m, n, o;
    direction dir;
    bool out;
    char **grid;
    bool ***visited;

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
    visited = _malloc(size * sizeof(bool **));
    i = 0;
    out = false;
    dir = UP;
    while ((fgets(line, MAX_LINE_LEN, fp)) != NULL)
    {
        clean_input(line);
        //printf("%s", line);

        grid[i] = _malloc(size * sizeof(char));
        visited[i] = _malloc(size * sizeof(bool *));
        for (j = 0; j < size; j++)
        {
            visited[i][j] = _malloc(4 * sizeof(bool));
        }
        copy_str(line, grid[i], size);
        j = find_in_str(line, '^');
        if (j != -1)
        {
            start_x = i;
            start_y = j;
        }
        i++;
    }

    res = 0;
    for (i = 0; i < size; i++)
    {
        for (j = 0; j < size; j++)
        {
            if (grid[i][j] == '.')
            {
                out = false;
                dir = UP;
                x = start_x;
                y = start_y;
                for (m = 0; m < size; m++)
                {
                    for (n = 0; n < size; n++)
                    {
                        for (o = 0; o < 4; o++)
                        {
                            visited[m][n][o] = false;
                        }
                    }
                }
                grid[i][j] = '#';
                while (!out)
                {
                    if (visited[x][y][dir - 1])
                    {
                        res++;
                        break;
                    }
                    visited[x][y][dir - 1] = true;
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
                grid[i][j] = '.';
            }
        }
    }

    if (ferror(fp)) printf("Error reading file.");
    fclose(fp);
    emancipation_proclamation();
    print_time(start, clock());
    print_malloced_mem();
    print_results("Positions stuck in a loop", res);
}
