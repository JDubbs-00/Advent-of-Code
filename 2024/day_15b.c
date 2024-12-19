#include "../utl.h"

//#define TEST
#define REAL

// GUESSES:

typedef struct
{
    int x;
    bool valid;
} box;


direction char_to_vec(char c)
{
    switch (c)
    {
    case '^':
        return UP;

    case 'v':
        return DOWN;

    case '<':
        return LEFT;
    
    default:
        return RIGHT;
    }
}

void clear_boxes(box *boxes, int size)
{
    for (int i = 0; i < size; i++)
    {
        boxes[i].valid = false;
    }
}

bool is_open(char **map, box *boxes, int size, int x_dir)
{
    for (int i = 2; i < size; i++)
    {
        if (boxes[i].valid)
        {
            if (map[boxes[i].x + x_dir][i] != '.')
            {
                return false;
            }
        }
    }

    return true;
}

bool is_movable(char **map, box *boxes, int size, int x_dir)
{
    for (int i = 2; i < size; i++)
    {
        if (boxes[i].valid)
        {
            if (map[boxes[i].x + x_dir][i] == '#')
            {
                return false;
            }
        }
    }

    return true;
}

int main(int argc, char *argv[])
{
    clock_t start = clock();
    FILE *fp;
    char *line = _malloc(1500);
    int res, size, i, j, k, l, cnt;
    char **map;
    coordinates robot;
    coordinates t;
    bool space;
    direction dir;
    box *boxes;
    bool **moved;

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
    cnt = 1;
    map = init_2d_char(size * 2 + 1, size);
    moved = init_2d_bool(size * 2, size);
    boxes = _malloc(size * 2 * sizeof(box));

    while ((fgets(line, 1500, fp)) != NULL)
    {
        clean_input(line);
        //printf("%s", line);
        if (i < size)
        {
            ITER_STR(j, line)
            {
                switch (line[j])
                {
                case '#':
                    map[i][j * 2] = '#';
                    map[i][j * 2 + 1] = '#';
                    break;
                
                case 'O':
                    map[i][j * 2] = '[';
                    map[i][j * 2 + 1] = ']';
                    break;

                case '.':
                    map[i][j * 2] = '.';
                    map[i][j * 2 + 1] = '.';
                    break;
                
                default:
                    map[i][j * 2] = '.';
                    map[i][j * 2 + 1] = '.';
                    robot.x = i;
                    robot.y = j * 2;
                    break;
                }
            }
        }
        else if (i > size)
        {
            ITER_STR(j, line)
            {
                // printf("Command #%d\n", cnt);
                dir = char_to_vec(line[j]);
                t.x = robot.x;
                t.y = robot.y;
                space = false;

                if (dir == LEFT)
                {
                    while (map[t.x][t.y] != '#' && !space)
                    {
                        t.y--;

                        if (map[t.x][t.y] == '.')
                        {
                            space = true;
                        }
                    }
                    if (space)
                    {
                        for (; t.y < robot.y; t.y++)
                        {
                            map[t.x][t.y] = map[t.x][t.y + 1];
                        }
                        robot.y--;
                    }
                }
                else if (dir == RIGHT)
                {
                    while (map[t.x][t.y] != '#' && !space)
                    {
                        t.y++;

                        if (map[t.x][t.y] == '.')
                        {
                            space = true;
                        }
                    }
                    if (space)
                    {
                        for (; t.y > robot.y; t.y--)
                        {
                            map[t.x][t.y] = map[t.x][t.y - 1];
                        }
                        robot.y++;
                    }
                }
                else if (dir == UP)
                {
                    clear_boxes(boxes, size * 2);
                    for (k = 0; k < size; k++)
                    {
                        clear_bool_arr(moved[k], size * 2);
                    }
                    boxes[t.y].x = t.x;
                    boxes[t.y].valid = true;
                    while (is_movable(map, boxes, size * 2, -1) && !space)
                    {
                        if (is_open(map, boxes, size * 2, -1))
                        {
                            space = true;
                        }
                        else
                        {
                            for (k = 2; k < size * 2 - 2; k++)
                            {
                                if (boxes[k].valid)
                                {
                                    if (map[boxes[k].x - 1][k] == '[')
                                    {
                                        boxes[k].x--;
                                        boxes[k + 1].valid = true;
                                        boxes[k + 1].x = boxes[k].x;
                                        moved[boxes[k].x][k] = true;
                                        moved[boxes[k].x][k + 1] = true;
                                        k++;
                                    }
                                    else if (map[boxes[k].x - 1][k] == ']')
                                    {
                                        boxes[k].x--;
                                        boxes[k - 1].valid = true;
                                        boxes[k - 1].x = boxes[k].x;
                                        moved[boxes[k].x][k] = true;
                                        moved[boxes[k].x][k - 1] = true;
                                    }
                                }
                            }
                        }
                    }
                    if (space)
                    {
                        for (k = 2; k < size * 2 - 2; k++)
                        {
                            for (l = 1; l < size - 1; l++)
                            {
                                if (moved[l][k])
                                {
                                    map[l - 1][k] = map[l][k];
                                    if (!moved[l + 1][k])
                                    {
                                        map[l][k] = '.';
                                    }
                                }
                            }
                        }
                        robot.x--;
                    }
                }
                else if (dir == DOWN)
                {
                    clear_boxes(boxes, size * 2);
                    for (k = 0; k < size; k++)
                    {
                        clear_bool_arr(moved[k], size * 2);
                    }
                    boxes[t.y].x = t.x;
                    boxes[t.y].valid = true;
                    while (is_movable(map, boxes, size * 2 - 2, 1) && !space)
                    {
                        if (is_open(map, boxes, size * 2 - 2, 1))
                        {
                            space = true;
                        }
                        else
                        {
                            for (k = 2; k < size * 2 - 2; k++)
                            {
                                if (boxes[k].valid)
                                {
                                    if (map[boxes[k].x + 1][k] == '[')
                                    {
                                        boxes[k].x++;
                                        boxes[k + 1].valid = true;
                                        boxes[k + 1].x = boxes[k].x;
                                        moved[boxes[k].x][k] = true;
                                        moved[boxes[k].x][k + 1] = true;
                                        k++;
                                    }
                                    else if (map[boxes[k].x + 1][k] == ']')
                                    {
                                        boxes[k].x++;
                                        boxes[k - 1].valid = true;
                                        boxes[k - 1].x = boxes[k].x;
                                        moved[boxes[k].x][k] = true;
                                        moved[boxes[k].x][k - 1] = true;
                                    }
                                }
                            }
                        }
                    }
                    if (space)
                    {
                        for (k = size * 2 - 3; k >= 2; k--)
                        {
                            for (l = size - 2; l >= 1; l--)
                            {
                                if (moved[l][k])
                                {
                                    map[l + 1][k] = map[l][k];
                                    if (!moved[l - 1][k])
                                    {
                                        map[l][k] = '.';
                                    }
                                }
                            }
                        }
                        robot.x++;
                    }
                }
                // if (map[robot.x][robot.y] != '.')
                // {
                //     printf("Error!\n");
                // }
                // map[robot.x][robot.y] = '@';
                // printf("%c\n", line[j]);
                // print_2d_char_arr(map, size, size * 2);
                // map[robot.x][robot.y] = '.';
                // cnt++;
            }
        }

        i++;
    }

    for (res = 0, i = 0; i < size; i++)
    {
        for (j = 0; j < size * 2; j++)
        {
            if (map[i][j] == '[')
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
