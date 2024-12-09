#include "../utl.h"

//#define TEST
#define REAL

// GUESSES:

typedef struct
{
    coordinates coords[50];
    int cnt;
} coords_set;


int main(int argc, char *argv[])
{
    clock_t start = clock();
    FILE *fp;
    char *line = _malloc(MAX_LINE_LEN);
    int res, size, i, j, k, x_dir, y_dir, x, y;
    char **grid;
    char c;
    coords_set *hash = _malloc(256 * sizeof(coords_set));
    coords_set *h;
    coordinates *p1, *p2;
    bool **antinodes;

    #ifdef TEST
    fp = fopen("input/day_8_example_input.txt", "r");
    size = 12;
    #endif
    #ifdef REAL
    fp = fopen("input/day_8_input.txt", "r");
    size = 50;
    #endif
    if (fp == NULL)
    {
        printf("Input file not found.");
        return 0;
    }

    grid = _malloc(size * sizeof(char *));
    antinodes = _malloc(size * sizeof(bool *));
    i = 0;

    while ((fgets(line, MAX_LINE_LEN, fp)) != NULL)
    {
        clean_input(line);
        //printf("%s", line);
        grid[i] = _malloc(size + 1);
        antinodes[i] = _malloc(size * sizeof(bool));
        copy_str(line, grid[i], size);

        for (j = 0; grid[i][j] != '\0'; j++)
        {
            c = grid[i][j];
            if (c == '.')
            {
                continue;
            }

            h = &hash[c];
            h->coords[h->cnt].x = i;
            h->coords[h->cnt++].y = j;
        }

        i++;
    }

    for (i = 0; i < 256; i++)
    {
        h = &hash[i];
        for (j = 0; j < h->cnt; j++)
        {
            p1 = &h->coords[j];
            for (k = j + 1; k < h->cnt; k++)
            {
                p2 = &h->coords[k];
                x_dir = p1->x - p2->x;
                y_dir = p1->y - p2->y;

                x = p1->x + x_dir;
                y = p1->y + y_dir;
                if (is_inbounds(size, size, x, y))
                {
                    antinodes[x][y] = true;
                }

                x = p2->x - x_dir;
                y = p2->y - y_dir;
                if (is_inbounds(size, size, x, y))
                {
                    antinodes[x][y] = true;
                }
            }
        }
    }

    for (i = 0, res = 0; i < size; i++)
    {
        for (j = 0; j < size; j++)
        {
            if (antinodes[i][j])
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
    print_results("Antinode locations", res);
}
