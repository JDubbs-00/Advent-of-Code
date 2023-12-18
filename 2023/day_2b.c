#include "../utl.h"

//#define TEST
#define REAL

// GUESSES:

typedef struct
{
    int red;
    int green;
    int blue;
} set;

int main(int argc, char *argv[])
{
    long long int start = GetTickCount64();
    FILE *fp;
    char *line = NULL;
    size_t len = 0;
    int length, res, sets, max_subsets, i, j, k, n;
    int *color;
    set *games, *game;

    #ifdef TEST
    fp = fopen("input/day_2_example_input.txt", "r");
    #endif
    #ifdef REAL
    fp = fopen("input/day_2_input.txt", "r");
    #endif
    if (fp == NULL)
    {
        printf("Input file not found.");
        return 0;
    }

    while ((length = getline(&line, &len, fp)) != -1)
    {
        clean_input(line);
        sets++;
        i = count_occurences(line, ';');
        max_subsets = max(i, max_subsets);
    }

    games = malloc(sets * sizeof(set));
    fclose(fp);

    #ifdef TEST
    fp = fopen("input/day_2_example_input.txt", "r");
    #endif
    #ifdef REAL
    fp = fopen("input/day_2_input.txt", "r");
    #endif

    i = 0;
    while ((length = getline(&line, &len, fp)) != -1)
    {
        clean_input(line);
        game = &games[i];
        clr_struct(game);
        for (j = get_x_occurence(line, ':', 1) + 2; line[j] != '\0'; j++)
        {
            if (is_num(line[j]))
            {
                k = j + 1;
                while(line[k] != ' ')
                {
                    k++;
                }
                k++;
                switch(line[k])
                {
                case 'r':
                    color = &game->red;
                    break;
                case 'g':
                    color = &game->green;
                    break;
                default:
                    color = &game->blue;
                    break;
                }
                n = str_to_int(&line[j], ' ');
                //printf("%d\n", n);
                *color = max(*color, n);
                j = k;
            }
        }
        i++;
    }

    res = 0;
    for (i = 0; i < sets; i++)
    {
        game = &games[i];
        res += (game->red * game->green * game->blue);
    }

    fclose(fp);
    if (line) free(line);
    free(games);
    print_time(start, GetTickCount64());
    print_results("Sum of the powers of all sets", res);
}
