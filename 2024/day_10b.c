#include "../utl.h"

//#define TEST
#define REAL

// GUESSES:

char **map;
int size;

int explore(int x, int y, char level)
{
    int score = 0;

    if (level == '9')
    {
        return 1;
    }

    if (x > 0 && map[x - 1][y] == level + 1)
    {
        score += explore(x - 1, y, level + 1);
    }
    if (y > 0 && map[x][y - 1] == level + 1)
    {
        score += explore(x, y - 1, level + 1);
    }
    if (x < size - 1 && map[x + 1][y] == level + 1)
    {
        score += explore(x + 1, y, level + 1);
    }
    if (y < size - 1 && map[x][y + 1] == level + 1)
    {
        score += explore(x, y + 1, level + 1);
    }

    return score;
}

int main(int argc, char *argv[])
{
    clock_t start = clock();
    FILE *fp;
    char *line = _malloc(MAX_LINE_LEN);
    int res, i, j, trailhead_cnt;
    coordinates trailheads[300];

    #ifdef TEST
    fp = fopen("input/day_10_example_input.txt", "r");
    size = 8;
    #endif
    #ifdef REAL
    fp = fopen("input/day_10_input.txt", "r");
    size = 45;
    #endif
    if (fp == NULL)
    {
        printf("Input file not found.");
        return 0;
    }

    map = _malloc(size * sizeof(char *));
    i = 0;
    trailhead_cnt = 0;

    while ((fgets(line, MAX_LINE_LEN, fp)) != NULL)
    {
        clean_input(line);
        //printf("%s", line);

        map[i] = _malloc(size + 1);
        copy_str(line, map[i], size);

        for (j = 0; j < size; j++)
        {
            if (map[i][j] == '0')
            {
                trailheads[trailhead_cnt].x = i;
                trailheads[trailhead_cnt++].y = j;
            }
        }

        i++;
    }

    res = 0;
    for (i = 0; i < trailhead_cnt; i++)
    {
        res += explore(trailheads[i].x, trailheads[i].y, '0');
    }

    if (ferror(fp)) printf("Error reading file.");
    fclose(fp);
    emancipation_proclamation();
    print_time(start, clock());
    print_malloced_mem();
    print_results("Sum of all trailhead ratings", res);
}
