
#include "../utl.h"

//#define TEST
#define REAL

#define TREE '#'
#define OPEN '.'

static void print_results(long long int n)
{
    printf("Product of trees encountered: %lld", n);
}

int main(int argc, char *argv[])
{
    long long int start = GetTickCount64();
    FILE *fp;
    char *line = NULL;
    size_t len = 0;
    int length, cols, rows, i, j, k, c;
    long long int product = 1;
    char **grid;

    const int slopes[5][2] = {{1, 1}, {3, 1}, {5, 1}, {7, 1}, {1, 2}};

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

    for (k = 0; k < 5; k++)
    {
        c = 0;
        for (i = 0, j = 0; i < rows; i += slopes[k][1], j = (j + slopes[k][0]) % cols)
        {
            if (grid[i][j] == TREE) c++;
        }
        printf("Trees encountered: %d\n", c);
        product *= (long long int)c;
    }

    fclose(fp);
    if (line) free(line);
    free_2d_char(grid, rows);
    print_time(start, GetTickCount64());
    print_results(product);
}
