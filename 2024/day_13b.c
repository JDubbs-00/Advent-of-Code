#include "../utl.h"

//#define TEST
#define REAL

// GUESSES:
// 75189228471712 - high

#define OFFSET 10000000000000

typedef struct
{
    long long int x;
    long long int y;
} coordinates_ll;

int main(int argc, char *argv[])
{
    clock_t start = clock();
    FILE *fp;
    char *line = _malloc(MAX_LINE_LEN);
    int *occurences;
    long long int res, tokens, least, press_a, press_b, mul1, mul2, val1, val2;
    coordinates_ll a, b, prize;

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

    tokens = 0;

    while ((fgets(line, MAX_LINE_LEN, fp)) != NULL)
    {
        clean_input(line);
        //printf("%s", line);

        (void)get_occurences(line, '+', &occurences, 2);
        a.x = str_to_int(&line[occurences[0] + 1], ',');
        a.y = str_to_int(&line[occurences[1] + 1], '\0');

        (void)fgets(line, MAX_LINE_LEN, fp);
        clean_input(line);
        (void)get_occurences(line, '+', &occurences, 2);
        b.x = str_to_int(&line[occurences[0] + 1], ',');
        b.y = str_to_int(&line[occurences[1] + 1], '\0');

        (void)fgets(line, MAX_LINE_LEN, fp);
        clean_input(line);
        (void)get_occurences(line, '=', &occurences, 2);
        prize.x = str_to_int(&line[occurences[0] + 1], ',') + OFFSET;
        prize.y = str_to_int(&line[occurences[1] + 1], '\0') + OFFSET;

        least = lcm(a.x, a.y);

        mul1 = least / a.x;
        a.x *= mul1;
        b.x *= mul1;
        prize.x *= mul1;

        mul2 = least / a.y;
        a.y *= mul2;
        b.y *= mul2;
        prize.y *= mul2;

        val1 = prize.x - prize.y;
        val2 = b.x - b.y;
        press_b = val1 / val2;
        press_a = (prize.x - (b.x * press_b)) / a.x;
        if (((a.x * press_a) + (b.x * press_b)) == prize.x
         && ((a.y * press_a) + (b.y * press_b)) == prize.y)
        {
            tokens += ((3 * press_a) + press_b);
        }

        (void)fgets(line, MAX_LINE_LEN, fp); // skip empty line
    }

    res = tokens;

    if (ferror(fp)) printf("Error reading file.");
    fclose(fp);
    emancipation_proclamation();
    print_time(start, clock());
    print_malloced_mem();
    print_results_ll("Fewest tokens", res);
}
