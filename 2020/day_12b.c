
#include "../utl.h"

//#define TEST
#define REAL

int wpt_x = 1;
int wpt_y = 10;
int self_x = 0;
int self_y = 0;

static void print_results(char *msg, int res)
{
    printf("%s: %d\n", msg, res);
}

int get_diff_x()
{
    return wpt_x - self_x;
}

int get_diff_y()
{
    return wpt_y - self_y;
}

void rotate(int degrees)
{
    double d = degree_to_radians(degrees);
    int s = sin(d);
    int c = cos(d);
    //printf("sin(%d) = %d\n", degrees, s);
    //printf("cos(%d) = %d\n", degrees, c);
    int diff_x = get_diff_x();
    int diff_y = get_diff_y();
    int x_new = diff_x * c - diff_y * s;
    int y_new = diff_x * s + diff_y * c;

    wpt_x = x_new + self_x;
    wpt_y = y_new + self_y;
}

void move(char c, int n)
{
    int diff_x, diff_y;

    switch (c)
    {
    case 'N':
        wpt_x += n;
        break;
    case 'S':
        wpt_x -= n;
        break;
    case 'E':
        wpt_y += n;
        break;
    case 'W':
        wpt_y -= n;
        break;
    case 'L':
        n = 360 - n;
    case 'R':
        rotate(n);
        break;
    default: //'F'
        diff_x = get_diff_x();
        diff_y = get_diff_y();
        self_x += (diff_x * n);
        self_y += (diff_y * n);
        wpt_x += (diff_x * n);
        wpt_y += (diff_y * n);
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
        //printf("%d, %d ------ %d, %d\n", self_x, self_y, wpt_x - self_x, wpt_y - self_y);
    }

    res = manhattan_dist(self_x, self_y);

    fclose(fp);
    if (line) free(line);
    print_time(start, GetTickCount64());
    print_results("Manhattan Distance from starting position", res);
}
