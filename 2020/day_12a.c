
#include "../utl.h"

//#define TEST
#define REAL

int x = 0;
int y = 0;
int angle = 90;

static void print_results(char *msg, int res)
{
    printf("%s: %d\n", msg, res);
}

char angle_to_direction()
{
    switch (angle)
    {
    case 0:
        return 'N';
    case 90:
        return 'E';
    case 180:
        return 'S';
    default:
        return 'W';
    }
}

void move(char c, int n)
{
    switch (c)
    {
    case 'N':
        x += n;
        break;
    case 'S':
        x -= n;
        break;
    case 'E':
        y += n;
        break;
    case 'W':
        y -= n;
        break;
    case 'L':
        angle -= n;
        if (angle < 0)
        {
            angle = 360 + angle;
        }
        break;
    case 'R':
        angle = (angle + n) % 360;
        break;
    default: //'F'
        move(angle_to_direction(), n);
        break;
    }
}

int main(int argc, char *argv[])
{
    long long int start = GetTickCount64();
    FILE *fp;
    char *line = NULL;
    size_t len = 0;
    int length, res, n;
    char c;

    #ifdef TEST
    fp = fopen("input/day_12_example_input.txt", "r");
    #endif
    #ifdef REAL
    fp = fopen("input/day_12_input.txt", "r");
    #endif
    if (fp == NULL)
    {
        printf("Input file not found.");
        return 0;
    }

    while ((length = getline(&line, &len, fp)) != -1)
    {
        clean_input(line);
        c = line[0];
        n = atoi(line + 1);
        move(c, n);
    }

    res = manhattan_dist(x, y);

    fclose(fp);
    if (line) free(line);
    print_time(start, GetTickCount64());
    print_results("Manhattan Distance from starting position", res);
}
