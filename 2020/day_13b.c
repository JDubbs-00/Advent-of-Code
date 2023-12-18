
#include "../utl.h"

//#define TEST
#define REAL

/*----------
guessed:
1962415654
----------*/

static void print_results(char *msg, long long int res)
{
    printf("%s: %lld\n", msg, res);
}

int main(int argc, char *argv[])
{
    long long int start = GetTickCount64();
    FILE *fp;
    char *line = NULL;
    size_t len = 0;
    int length, buses_count, i, j, c, id, time;
    int *buses, *indices;
    int last = 0;
    long long int inc = 1;
    long long int res;

    bool first = true;
    bool good = false;

    #ifdef TEST
    fp = fopen("input/day_13_example_input.txt", "r");
    #endif
    #ifdef REAL
    fp = fopen("input/day_13_input.txt", "r");
    #endif
    if (fp == NULL)
    {
        printf("Input file not found.");
        return 0;
    }

    while ((length = getline(&line, &len, fp)) != -1)
    {
        if (first)
        {
            first = false;
            c = 0;
        }
        else
        {
            clean_input(line);
            buses_count = count_occurences(line, ',') + 1 - count_occurences(line, 'x');
            buses = malloc(buses_count * sizeof(int));
            indices = malloc(buses_count * sizeof(int));
            buses_count = 0;
            for (i = 1; line[i] != '\0'; i++)
            {
                if (line[i] == ',')
                {
                    if (line[i - 1] != 'x')
                    {
                        buses[buses_count] = str_to_int(line + last, ',');
                        //indices[buses_count] = (-c) % buses[buses_count];
                        indices[buses_count] = c;
                        printf("%d, %d\n", buses[buses_count], indices[buses_count]);
                        buses_count++;
                    }
                    last = i + 1;
                    c++;
                }
            }
            if (line[i - 1] != 'x')
            {
                buses[buses_count] = str_to_int(line + last, '\0');
                //indices[buses_count] = (-c) % buses[buses_count];
                indices[buses_count] = c;
                //printf("%d, %d\n", buses[buses_count], indices[buses_count]);
                buses_count++;
            }
        }
    }

    //res = chinese_remainder(buses, indices, buses_count);
    res = 0;
    for (i = 0; i < buses_count; inc *= buses[i], i++)
    {
        for (; (res + indices[i]) % buses[i] != 0; res += inc) {
            //printf("Rem: %lld\n", (j + indices[i]) % buses[i]);
        }
        //printf("%lld, %lld\n", res, inc);
    }

    fclose(fp);
    if (line) free(line);
    free(buses);
    print_time(start, GetTickCount64());
    print_results("Earliest time all buses arrive in order", res);
}
