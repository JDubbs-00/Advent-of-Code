#include "../utl.h"

//#define TEST
#define REAL

static char **schematic;
static int size;

bool is_part_number(int row, int col)
{
    int i, j, x, y;
    char c;
    if (!is_inbounds(size, size, row, col))
    {
        return false;
    }
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
                if (c != '.' && !is_num(c))
                {
                    return true;
                }
            }
        }
    }

    return false;
}

int main(int argc, char *argv[])
{
    long long int start = GetTickCount64();
    FILE *fp;
    char *line = NULL;
    size_t len = 0;
    int length, res, c, r, digits, i;

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
            digits = 0;
            while (c + digits < size && is_num(schematic[r][c + digits]))
            {
                digits++;
            }
            //printf("Number has %d digits\n", digits);
            for (i = 0; i < digits; i++)
            {
                if (is_part_number(r, c + i))
                {
                    //printf("%d is a part number\n", str_to_int(&schematic[r][c], '.'));
                    res += str_to_int(&schematic[r][c], '.');
                    c += digits;
                    break;
                }
            }
        }
    }

    fclose(fp);
    if (line) free(line);
    free_2d_char(schematic, size);
    print_time(start, GetTickCount64());
    print_results("Sum of all part numbers", res);
}
