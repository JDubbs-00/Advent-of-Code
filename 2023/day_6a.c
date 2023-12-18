#include "../utl.h"

//#define TEST
#define REAL

typedef struct
{
    int time;
    int dist;
} race;

int main(int argc, char *argv[])
{
    long long int start = GetTickCount64();
    FILE *fp;
    char *line = NULL;
    size_t len = 0;
    int length, res, races_cnt, i, j;
    int *vals;
    race *races, *r;

    #ifdef TEST
    fp = fopen("input/day_6_example_input.txt", "r");
    races_cnt = 3;
    #endif
    #ifdef REAL
    fp = fopen("input/day_6_input.txt", "r");
    races_cnt = 4;
    #endif
    if (fp == NULL)
    {
        printf("Input file not found.");
        return 0;
    }

    races = malloc(races_cnt * sizeof(race));
    vals = malloc(races_cnt * sizeof(int));

    getline(&line, &len, fp);
    clean_input(line);
    remove_extra_delimiters(line, ' ');
    //printf("%s\n", line);
    split_to_int(vals, races_cnt, &line[get_x_occurence(line, ':', 1) + 2], ' ');
    for (i = 0; i < races_cnt; i++)
    {
        races[i].time = vals[i];
        //printf("%d\n", races[i].time);
    }

    getline(&line, &len, fp);
    clean_input(line);
    remove_extra_delimiters(line, ' ');
    split_to_int(vals, races_cnt, &line[get_x_occurence(line, ':', 1) + 2], ' ');
    for (i = 0; i < races_cnt; i++)
    {
        races[i].dist = vals[i];
        //printf("%d\n", races[i].dist);
    }

    res = 1;
    for (i = 0; i < races_cnt; i++)
    {
        j = 1;
        r = &races[i];
        while ((r->time - j) * j <= r->dist)
        {
            j++;
        }
        res *= (r->time - (j * 2) + 1);
        //printf("%d\n", j);
    }

    fclose(fp);
    if (line) free(line);
    free(races);
    free(vals);
    print_time(start, GetTickCount64());
    print_results("Ways to beat the record multiplied", res);
}
