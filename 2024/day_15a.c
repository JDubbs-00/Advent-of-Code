#include "../utl.h"

//#define TEST
#define REAL

// GUESSES:

static coordinates left = {0, -1};
static coordinates right = {0, 1};
static coordinates up = {-1, 0};
static coordinates down = {1, 0};

coordinates *char_to_vec(char c)
{
    switch (c)
    {
    case '^':
        return &up;

    case 'v':
        return &down;

    case '<':
        return &left;
    
    default:
        return &right;
    }
}

coordinates add_coords(coordinates *c1, coordinates *c2)
{
    coordinates c;

    c.x = c1->x + c2->x;
    c.y = c1->y + c2->y;

    return c;
}

int main(int argc, char *argv[])
{
    clock_t start = clock();
    FILE *fp;
    char *line = _malloc(1500);
    int res, size, i, j;
    char **map;
    coordinates robot;
    coordinates t;
    coordinates *vec;
    bool space;

    #ifdef TEST
    fp = fopen("input/day_15_example_input.txt", "r");
    size = 10;
    #endif
    #ifdef REAL
    fp = fopen("input/day_15_input.txt", "r");
    size = 50;
    #endif
    if (fp == NULL)
    {
        printf("Input file not found.");
        return 0;
    }

    i = 0;
    map = init_2d_char(size + 1, size);

    while ((fgets(line, 1500, fp)) != NULL)
    {
        clean_input(line);
        //printf("%s", line);
        if (i < size)
        {
            copy_str(line, map[i], size);
            j = find_in_str(map[i], '@');
            if (j != -1)
            {
                robot.x = i;
                robot.y = j;
                map[i][j] = '.';
            }
        }
        else if (i > size)
        {
            ITER_STR(j, line)
            {
                vec = char_to_vec(line[j]);

                t = add_coords(&robot, vec);
                if (map[t.x][t.y] == '.')
                {
                    robot = t;
                }
                else if (map[t.x][t.y] != '#')
                {
                    space = false;
                    while (!space && map[t.x][t.y] != '#')
                    {
                        t = add_coords(&t, vec);

                        if (map[t.x][t.y] == '.')
                        {
                            space = true;
                        }
                    }

                    if (space)
                    {
                        robot = add_coords(&robot, vec);
                        map[robot.x][robot.y] = '.';
                        map[t.x][t.y] = 'O';
                    }
                }
                // map[robot.x][robot.y] = '@';
                // printf("%c\n", line[j]);
                // print_2d_char_arr(map, size, size);
                // map[robot.x][robot.y] = '.';
            }
        }

        i++;
    }

    for (res = 0, i = 0; i < size ; i++)
    {
        for (j = 0; j < size; j++)
        {
            if (map[i][j] == 'O')
            {
                res += ((i * 100) + j);
            }
        }
    }

    if (ferror(fp)) printf("Error reading file.");
    fclose(fp);
    emancipation_proclamation();
    print_time(start, clock());
    print_malloced_mem();
    print_results("Sum of all boxes' GPS coordinates", res);
}
