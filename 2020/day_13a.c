
#include "../utl.h"

//#define TEST
#define REAL

static void print_results(char *msg, int res)
{
    printf("%s: %d\n", msg, res);
}

int main(int argc, char *argv[])
{
    long long int start = GetTickCount64();
    FILE *fp;
    char *line = NULL;
    size_t len = 0;
    int length, res, buses_count, i, c, id, time;
    int *buses;
    int target = 0;
    int last = 0;

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
        clean_input(line);
        if (target == 0)
        {
            target = atoi(line);
            time = target;
        }
        else
        {
            buses_count = count_occurences(line, ',') + 1 - count_occurences(line, 'x');
            buses = malloc(buses_count * sizeof(int));
            buses_count= 0;
            for (i = 1; line[i] != '\0'; i++)
            {
                if (line[i] == ',')
                {
                    if (line[i - 1] != 'x')
                    {
                        buses[buses_count++] = str_to_int(line + last, ',');
                    }
                    last = i + 1;
                }
            }
            if (line[i - 1] != 'x')
            {
                buses[buses_count++] = str_to_int(line + last, '\0');
            }
        }
    }

    for (i = 0; i < buses_count; i++)
    {
        c = target / buses[i];
        //printf("%d, %d\n", buses[i], c);
        c = (buses[i] * (c + 1)) - target;
        //printf("%d, %d\n", buses[i], c);
        if (c < time)
        {
            time = c;
            id = buses[i];
        }
    }
    //printf("%d, %d\n", id, time);
    res = id * time;

    fclose(fp);
    if (line) free(line);
    free(buses);
    print_time(start, GetTickCount64());
    print_results("ID of earliest bus x minutes to wait", res);
}
