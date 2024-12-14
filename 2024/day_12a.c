#include "../utl.h"

//#define TEST
#define REAL

// GUESSES:

static char **plots;
static bool **explored;
static int area, perimeter, size;
static char plant;

void calc(int x, int y)
{
    if (explored[x][y])
    {
        return;
    }

    area++;
    explored[x][y] = true;

    if (x > 0)
    {
        if (plots[x - 1][y] == plant)
        {
            calc(x - 1, y);
        }
        else
        {
            perimeter++;
        }
    }
    else
    {
        perimeter++;
    }

    if (y > 0)
    {
        if (plots[x][y - 1] == plant)
        {
            calc(x, y - 1);
        }
        else
        {
            perimeter++;
        }
    }
    else
    {
        perimeter++;
    }

    if (x < size - 1)
    {
        if (plots[x + 1][y] == plant)
        {
            calc(x + 1, y);
        }
        else
        {
            perimeter++;
        }
    }
    else
    {
        perimeter++;
    }

    if (y < size - 1)
    {
        if (plots[x][y + 1] == plant)
        {
            calc(x, y + 1);
        }
        else
        {
            perimeter++;
        }
    }
    else
    {
        perimeter++;
    }
}

int main(int argc, char *argv[])
{
    clock_t start = clock();
    FILE *fp;
    char *line = _malloc(MAX_LINE_LEN);
    int res, i, j;

    #ifdef TEST
    fp = fopen("input/day_12_example_input.txt", "r");
    size = 10;
    #endif
    #ifdef REAL
    fp = fopen("input/day_12_input.txt", "r");
    size = 140;
    #endif
    if (fp == NULL)
    {
        printf("Input file not found.");
        return 0;
    }

    plots = _malloc(size * sizeof(char *));
    explored = _malloc(size * sizeof(bool *));
    i = 0;
    while ((fgets(line, MAX_LINE_LEN, fp)) != NULL)
    {
        clean_input(line);
        //printf("%s", line);

        plots[i] = _malloc(size + 1);
        explored[i] = _malloc(size * sizeof(bool));

        copy_str(line, plots[i], size);
        i++;
    }

    for (i = 0, res = 0; i < size; i++)
    {
        for (j = 0; j < size; j++)
        {
            area = 0;
            perimeter = 0;
            plant = plots[i][j];

            calc(i, j);

            res += (area * perimeter);
        }
    }

    if (ferror(fp)) printf("Error reading file.");
    fclose(fp);
    emancipation_proclamation();
    print_time(start, clock());
    print_malloced_mem();
    print_results("Total price of all fencing", res);
}
