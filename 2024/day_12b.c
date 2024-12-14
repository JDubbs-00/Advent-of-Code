#include "../utl.h"

//#define TEST
#define REAL

// GUESSES:

typedef struct
{
    bool up;
    bool down;
    bool left;
    bool right;
} walk_type;

static char **plots;
static bool **explored;
static walk_type **walked;
static int area, size, sides;
static char plant;

void calc(int x, int y)
{
    bool left_same, right_same, up_same, down_same;
    bool left_out, right_out, up_out, down_out;
    int tx, ty;

    if (explored[x][y])
    {
        return;
    }

    area++;
    explored[x][y] = true;

    left_out = y == 0;
    right_out = y == size - 1;
    up_out = x == 0;
    down_out = x == size - 1;

    left_same = !left_out && plots[x][y - 1] == plant;
    right_same = !right_out && plots[x][y + 1] == plant;
    up_same = !up_out && plots[x - 1][y] == plant;
    down_same = !down_out && plots[x + 1][y] == plant;

    if (!up_out)
    {
        if (up_same)
        {
            calc(x - 1, y);
        }
        else if (!walked[x][y].up)
        {
            sides++;
            walked[x][y].up = true;
            ty = y - 1;
            while (ty >= 0 && !walked[x][ty].up && plots[x][ty] == plant && plots[x - 1][ty] != plant)
            {
                walked[x][ty].up = true;
                ty--;
            }
            ty = y + 1;
            while (ty < size && !walked[x][ty].up && plots[x][ty] == plant && plots[x - 1][ty] != plant)
            {
                walked[x][ty].up = true;
                ty++;
            }
        }
    }
    else if (!walked[x][y].up)
    {
        sides++;
        walked[x][y].up = true;
        ty = y - 1;
        while (ty >= 0 && !walked[x][ty].up && plots[x][ty] == plant)
        {
            walked[x][ty].up = true;
            ty--;
        }
        ty = y + 1;
        while (ty < size && !walked[x][ty].up && plots[x][ty] == plant)
        {
            walked[x][ty].up = true;
            ty++;
        }
    }

    if (!left_out)
    {
        if (left_same)
        {
            calc(x, y - 1);
        }
        else if (!walked[x][y].left)
        {
            sides++;
            walked[x][y].left = true;
            tx = x - 1;
            while (tx >= 0 && !walked[tx][y].left && plots[tx][y] == plant && plots[tx][y - 1] != plant)
            {
                walked[x][ty].left = true;
                tx--;
            }
            tx = x + 1;
            while (tx < size && !walked[tx][y].left && plots[tx][y] == plant && plots[tx][y - 1] != plant)
            {
                walked[tx][y].left = true;
                tx++;
            }
        }
    }
    else if (!walked[x][y].left)
    {
        sides++;
        walked[x][y].left = true;
        tx = x - 1;
        while (tx >= 0 && !walked[tx][y].left && plots[tx][y] == plant)
        {
            walked[tx][y].left = true;
            tx--;
        }
        tx = x + 1;
        while (tx < size && !walked[tx][y].left && plots[tx][y] == plant)
        {
            walked[tx][y].left = true;
            tx++;
        }
    }

    if (!down_out)
    {
        if (down_same)
        {
            calc(x + 1, y);
        }
        else if (!walked[x][y].down)
        {
            sides++;
            walked[x][y].down = true;
            ty = y - 1;
            while (ty >= 0 && !walked[x][ty].down && plots[x][ty] == plant && plots[x + 1][ty] != plant)
            {
                walked[x][ty].down = true;
                ty--;
            }
            ty = y + 1;
            while (ty < size && !walked[x][ty].down && plots[x][ty] == plant && plots[x + 1][ty] != plant)
            {
                walked[x][ty].down = true;
                ty++;
            }
        }
    }
    else if (!walked[x][y].down)
    {
        sides++;
        walked[x][y].down = true;
        ty = y - 1;
        while (ty >= 0 && !walked[x][ty].down && plots[x][ty] == plant)
        {
            walked[x][ty].down = true;
            ty--;
        }
        ty = y + 1;
        while (ty < size && !walked[x][ty].down && plots[x][ty] == plant)
        {
            walked[x][ty].down = true;
            ty++;
        }
    }

    if (!right_out)
    {
        if (right_same)
        {
            calc(x, y + 1);
        }
        else if (!walked[x][y].right)
        {
            sides++;
            walked[x][y].right = true;
            tx = x - 1;
            while (tx >= 0 && !walked[tx][y].right && plots[tx][y] == plant && plots[tx][y + 1] != plant)
            {
                walked[tx][y].right = true;
                tx--;
            }
            tx = x + 1;
            while (tx < size && !walked[tx][y].right && plots[tx][y] == plant && plots[tx][y + 1] != plant)
            {
                walked[tx][y].right = true;
                tx++;
            }
        }
    }
    else if (!walked[x][y].right)
    {
        sides++;
        walked[x][y].right = true;
        tx = x - 1;
        while (tx >= 0 && !walked[tx][y].right && plots[tx][y] == plant)
        {
            walked[tx][y].right = true;
            tx--;
        }
        tx = x + 1;
        while (tx < size && !walked[tx][y].right && plots[tx][y] == plant)
        {
            walked[tx][y].right = true;
            tx++;
        }
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
    walked = _malloc(size * sizeof(walk_type *));
    i = 0;
    while ((fgets(line, MAX_LINE_LEN, fp)) != NULL)
    {
        clean_input(line);
        //printf("%s", line);

        plots[i] = _malloc(size + 1);
        explored[i] = _malloc(size * sizeof(bool));
        walked[i] = _malloc(size * sizeof(walk_type));

        copy_str(line, plots[i], size);
        i++;
    }

    for (i = 0, res = 0; i < size; i++)
    {
        for (j = 0; j < size; j++)
        {
            area = 0;
            sides = 0;
            plant = plots[i][j];

            calc(i, j);

            res += (area * sides);
        }
    }

    if (ferror(fp)) printf("Error reading file.");
    fclose(fp);
    emancipation_proclamation();
    print_time(start, clock());
    print_malloced_mem();
    print_results("Total price of all fencing", res);
}
