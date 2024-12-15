#include "../utl.h"

//#define TEST
#define REAL

// GUESSES:

typedef struct
{
    coordinates pos;
    coordinates vector;
} robot_type;


int main(int argc, char *argv[])
{
    clock_t start = clock();
    FILE *fp;
    char *line = _malloc(MAX_LINE_LEN);
    int res, robots_cnt, height, width, i, j, *commas, *equals;
    int quads[4];
    robot_type *robots, *r;

    #ifdef TEST
    fp = fopen("input/day_14_example_input.txt", "r");
    robots_cnt = 12;
    width = 11;
    height = 7;
    #endif
    #ifdef REAL
    fp = fopen("input/day_14_input.txt", "r");
    robots_cnt = 500;
    width = 101;
    height = 103;
    #endif
    if (fp == NULL)
    {
        printf("Input file not found.");
        return 0;
    }

    robots = _malloc(robots_cnt * sizeof(robot_type));
    i = 0;

    while ((fgets(line, MAX_LINE_LEN, fp)) != NULL)
    {
        clean_input(line);
        //printf("%s", line);

        get_occurences(line, ',', &commas, 2);
        get_occurences(line, '=', &equals, 2);

        r = &robots[i];

        r->pos.x = str_to_int(&line[equals[0] + 1], ',');
        r->vector.x = str_to_int(&line[equals[1] + 1], ',');
        
        r->pos.y = str_to_int(&line[commas[0] + 1], ' ');
        r->vector.y = str_to_int(&line[commas[1] + 1], '\0');

        i++;
    }

    for (i = 0; i < 100; i++)
    {
        for (j = 0; j < robots_cnt; j++)
        {
            r = &robots[j];

            r->pos.x += r->vector.x;
            r->pos.y += r->vector.y;

            if (r->pos.x < 0)
            {
                r->pos.x += width;
            }
            else if (r->pos.x >= width)
            {
                r->pos.x -= width;
            }

            if (r->pos.y < 0)
            {
                r->pos.y += height;
            }
            else if (r->pos.y >= height)
            {
                r->pos.y -= height;
            }
        }
    }

    clear_int_arr(quads, 4);
    for (i = 0; i < robots_cnt; i++)
    {
        r = &robots[i];

        if (r->pos.x < width / 2 && r->pos.y < height / 2)
        {
            quads[0]++;
        }
        else if (r->pos.x > width / 2 && r->pos.y < height / 2)
        {
            quads[1]++;
        }
        else if (r->pos.x < width / 2 && r->pos.y > height / 2)
        {
            quads[2]++;
        }
        else if (r->pos.x > width / 2 && r->pos.y > height / 2)
        {
            quads[3]++;
        }
    }

    res = quads[0] * quads[1] * quads[2] * quads[3];

    if (ferror(fp)) printf("Error reading file.");
    fclose(fp);
    emancipation_proclamation();
    print_time(start, clock());
    print_malloced_mem();
    print_results("Safety score", res);
}
