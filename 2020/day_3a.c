
#include "../utl.h"

//#define TEST
#define REAL

#define TREE '#'
#define OPEN '.'

static void print_results(int n)
{
    printf("Trees encountered: %d", n);
}

int main(int argc, char *argv[])
{
    long long int start = GetTickCount64();
    FILE *fp;
    char *line = NULL;
    size_t len = 0;
    int length, cols, rows, i, j;
    int c = 0;
    char **grid;

    #ifdef TEST
    fp = fopen("input/day_3_example_input.txt", "r");
    cols = 11;
    rows = 11;
    #endif
    #ifdef REAL
    fp = fopen("input/day_3_input.txt", "r");
    cols = 31;
    rows = 323;
    #endif
    if (fp == NULL)
    {
        printf("Input file not found.");
        return 0;
    }

    init_2d_char(&grid, cols, rows);
    i = 0;
    while ((length = getline(&line, &len, fp)) != -1)
    {
        for (j = 0; j < cols; j++)
        {
            //printf("%c", grid[i][j]);
            grid[i][j] = line[j];
        }
        //printf("\n");
        i++;
    }

    for (i = 0, j = 0; i < rows; i++, j = (j + 3) % cols)
    {
        if (grid[i][j] == TREE) c++;
    }

    fclose(fp);
    if (line) free(line);
    free_2d_char(grid, rows);
    print_time(start, GetTickCount64());
    print_results(c);
}
