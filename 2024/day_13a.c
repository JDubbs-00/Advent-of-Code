#include "../utl.h"

//#define TEST
#define REAL

// GUESSES:

int main(int argc, char *argv[])
{
    clock_t start = clock();
    FILE *fp;
    char *line = _malloc(MAX_LINE_LEN);
    int res, *occurences, tokens, least, press_a, press_b, mul1, mul2, val1, val2;
    coordinates a, b, prize;

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
        prize.x = str_to_int(&line[occurences[0] + 1], ',');
        prize.y = str_to_int(&line[occurences[1] + 1], '\0');

        least = (int)lcm(a.x, a.y);

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
        if (press_b * val2 == val1)
        {
            press_a = (prize.x - (b.x * press_b)) / a.x;
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
    print_results("Fewest tokens", res);
}
