
#include "../utl.h"

//#define TEST
#define REAL

static void print_results(int n)
{
    printf("My seat ID: %d\n", n);
}

int get_val(char *pass, int l, int u, int times, char lower)
{
    int i, t;
    for (i = 0; i < times; i++)
    {
        t = (u - l) / 2;
        if (pass[i] == lower)
        {
            u -= (t + 1);
        }
        else
        {
            l += t + 1;
        }
        //printf("%c: %d-%d\n", pass[i], l, u);
    }
    return l;
}

int get_row(char *pass)
{
    return get_val(pass, 0, 127, 7, 'F');
}

int get_col(char *pass)
{
    return get_val(pass + 7, 0, 7, 3, 'L');
}

int main(int argc, char *argv[])
{
    long long int start = GetTickCount64();
    FILE *fp;
    char *line = NULL;
    size_t len = 0;
    int length, row, col, id;
    int s = 0;
    bool hash[128 * 8];

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

    memset(hash, 0, 128 * 8 * sizeof(bool));

    while ((length = getline(&line, &len, fp)) != -1)
    {
        clean_input(line);
        row = get_row(line);
        col = get_col(line);
        //printf("%d, %d\n", row, col);
        id = row * 8 + col;
        hash[id] = true;
    }

    for (id = 1; id < (128 * 8) - 1; id++)
    {
        if (hash[id - 1] && !hash[id] && hash[id + 1])
        {
            break;
        }
    }

    fclose(fp);
    if (line) free(line);
    print_time(start, GetTickCount64());
    print_results(id);
}
