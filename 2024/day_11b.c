#include "../utl.h"

//#define TEST
#define REAL

// GUESSES:
// 128557190258 - low
// 769742215740 - low

typedef struct
{
    long long int start;
    long long int result;
} history;

#define MAX_BLINKS 75
#define MAX_HIST_CNT 10000

history hist[MAX_BLINKS][MAX_HIST_CNT];
int hist_cnt[MAX_BLINKS];

long long int search(int blinks, long long int target)
{
    int i;
    history *h = hist[blinks];

    for (i = 0; i < hist_cnt[blinks]; i++)
    {
        if (h[i].start == target)
        {
            return h[i].result;
        }
    }

    return -1;
}

void add_to_hist(int blinks, long long int start, long long int result)
{
    if (hist_cnt[blinks] == MAX_HIST_CNT)
    {
        exit(-1);
    }
    hist[blinks][hist_cnt[blinks]].start = start;
    hist[blinks][hist_cnt[blinks]].result = result;
    hist_cnt[blinks]++;
}

long long int simulate(long long int n, int blinks)
{
    long long int res;
    int len;
    char num_as_str[MAX_DIGITS_LL];

    if (blinks == MAX_BLINKS)
    {
        return 1;
    }

    res = search(blinks, n);
    if (res != -1)
    {
        return res;
    }

    if (n == 0)
    {
        res = simulate(1, blinks + 1);
        add_to_hist(blinks, n, res);

        return res;
    }
    ll_to_str(n, num_as_str);
    len = str_length(num_as_str);
    if (is_even(len))
    {
        long long int num1, num2;
        int mid = len / 2;

        num2 = str_to_ll(num_as_str + mid, '\0');
        num_as_str[mid] = '\0';
        num1 = str_to_ll(num_as_str, '\0');

        res = simulate(num1, blinks + 1);
        res += simulate(num2, blinks + 1);

        add_to_hist(blinks, n, res);

        return res;
    }

    res = simulate(n * 2024, blinks + 1);
    add_to_hist(blinks, n, res);

    return res;
}

int main(int argc, char *argv[])
{
    clock_t start = clock();
    FILE *fp;
    char *line = _malloc(MAX_LINE_LEN);
    int i, size;
    long long int *vals, res;

    #ifdef TEST
    fp = fopen("input/day_11_example_input.txt", "r");
    #endif
    #ifdef REAL
    fp = fopen("input/day_11_input.txt", "r");
    #endif
    if (fp == NULL)
    {
        printf("Input file not found.");
        return 0;
    }

    for (i = 0; i < MAX_BLINKS; i++)
    {
        hist_cnt[i] = 0;
    }

    while ((fgets(line, MAX_LINE_LEN, fp)) != NULL)
    {
        clean_input(line);
        //printf("%s", line);

        size = split_to_ll_unknown_size(&vals, line, ' ');
    }

    for (i = 0, res = 0; i < size; i++)
    {
        res += simulate(vals[i], 0);
    }

    if (ferror(fp)) printf("Error reading file.");
    fclose(fp);
    emancipation_proclamation();
    print_time(start, clock());
    print_malloced_mem();
    printf("Stones after blinking %d times: %lld\n", MAX_BLINKS, res);
}
