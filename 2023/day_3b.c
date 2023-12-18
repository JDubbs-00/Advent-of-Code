#include "../utl.h"

//#define TEST
#define REAL

typedef struct
{
    int x;
    int y;
} part_number;

static char **schematic;
static int size;
static part_number gear[2];
static int count;

part_number find_start(int row, int col)
{
    part_number start;

    col--;
    while (col >= 0 && is_num(schematic[row][col]))
    {
        col--;
    }

    start.x = row;
    start.y = col + 1;

    return start;
}

bool part_numbers_equal(part_number *p1, part_number *p2)
{
    return p1->x == p2->x && p1->y == p2->y;
}

bool is_valid_gear(int row, int col)
{
    int i, j, x, y;
    char c;
    part_number start;

    if (!is_inbounds(size, size, row, col))
    {
        return false;
    }

    count = 0;
    for (i = -1; i < 2; i++)
    {
        x = row + i;
        for (j = -1; j < 2; j++)
        {
            y = col + j;
            if (is_inbounds(size, size, x, y))
            {
                c = schematic[x][y];
                //printf("schematic[%d][%d] = %c\n", x, y, c);
                if (is_num(c))
                {
                    start = find_start(x, y);
                    if (count == 0 || (count == 1 && !part_numbers_equal(&start, &gear[0])))
                    {
                        gear[count++] = start;
                    }
                    else if (count == 2 && !part_numbers_equal(&start, &gear[0]) && !part_numbers_equal(&start, &gear[1]))
                    {
                        return false;
                    }
                }
            }
        }
    }

    return count == 2;
}

int main(int argc, char *argv[])
{
    long long int start = GetTickCount64();
    FILE *fp;
    char *line = NULL;
    size_t len = 0;
    int length, res, c, r;

    #ifdef TEST
    fp = fopen("input/day_3_example_input.txt", "r");
    size = 10;
    #endif
    #ifdef REAL
    fp = fopen("input/day_3_input.txt", "r");
    size = 140;
    #endif
    if (fp == NULL)
    {
        printf("Input file not found.");
        return 0;
    }

    schematic = init_2d_char(size, size);
    r = 0;
    while ((length = getline(&line, &len, fp)) != -1)
    {
        clean_input(line);
        copy_str(line, schematic[r], size);
        r++;
    }

    res = 0;
    for (r = 0; r < size; r++)
    {
        //printf("%s\n", schematic[r]);
        for (c = 0; c < size; c++)
        {
            //printf("Trying %c\n", schematic[r][c]);
            if (schematic[r][c] == '*' && is_valid_gear(r, c))
            {
                res += (str_to_int(&schematic[gear[0].x][gear[0].y], '.') * str_to_int(&schematic[gear[1].x][gear[1].y], '.'));
            }
        }
    }

    fclose(fp);
    if (line) free(line);
    free_2d_char(schematic, size);
    print_time(start, GetTickCount64());
    print_results("Sum of all gear ratios", res);
}
