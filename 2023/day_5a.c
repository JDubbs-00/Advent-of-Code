#include "../utl.h"

//#define TEST
#define REAL

// GUESSES:
// 101066236 - too low

typedef struct
{
    long long int min;
    long long int max;
    long long int diff;
} map;

typedef struct
{
    map maps[50];
    int count;
} conversion;

bool in_range(map *m, long long int seed)
{
    //printf("%d between %d and %d?\n", seed, m->min, m->max);
    return seed >= m->min && seed < m->max;
}

long long int map_seed(conversion *c, long long int seed)
{
    map *m;
    int i;

    for (i = 0; i < c->count; i++)
    {
        m = &c->maps[i];
        if (in_range(m, seed))
        {
            //printf("%lld -> %lld\n", seed, seed + m->diff);
            return seed + m->diff;
        }
    }

    return seed;
}

int main(int argc, char *argv[])
{
    long long int start = GetTickCount64();
    FILE *fp;
    char *line = NULL;
    size_t len = 0;
    int length, i, j, seeds_count;
    long long int seed, res;
    long long int *seeds = NULL;
    long long int nums[3];
    conversion conversions[7];
    conversion *c;
    map *m;

    #ifdef TEST
    fp = fopen("input/day_5_example_input.txt", "r");
    #endif
    #ifdef REAL
    fp = fopen("input/day_5_input.txt", "r");
    #endif
    if (fp == NULL)
    {
        printf("Input file not found.");
        return 0;
    }

    i = -1;
    while ((length = getline(&line, &len, fp)) != -1)
    {
        clean_input(line);
        //printf("%s\n", line);
        if (find_in_str(line, ':') != -1)
        {
            if (i == -1)
            {
                seeds_count = split_to_ll_unknown_size(&seeds, &line[7], ' ');
                //print_ll_arr(seeds, seeds_count);
            }
            else
            {
                c = &conversions[i];
                c->count = 0;
            }
            i++;
            //printf("%s\n", line);
        }
        else if (!is_empty_str(line))
        {
            split_to_ll(nums, 3, line, ' ');
            m = &c->maps[c->count++];
            m->min = nums[1];
            m->max = m->min + nums[2];
            m->diff = nums[0] - nums[1];
            //printf("%lld-%lld (%lld)\n", m->min, m->max, m->diff);
            //printf("%s (index %d)\n", line, i - 1);
        }
    }

    res = -1;
    for (i = 0; i < seeds_count; i++)
    {
        seed = seeds[i];
        //printf("%lld\n", seed);
        for (j = 0; j < 7; j++)
        {
            seed = map_seed(&conversions[j], seed);
            //printf("%lld\n", seed);
        }
        //printf("\n");
        if (res == -1 || seed < res)
        {
            res = seed;
        }
    }

    fclose(fp);
    if (line) free(line);
    if (seeds) free(seeds);
    print_time(start, GetTickCount64());
    print_results_ll("Lowest location", res);
}
