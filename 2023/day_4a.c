#include "../utl.h"

//#define TEST
#define REAL

int main(int argc, char *argv[])
{
    long long int start = GetTickCount64();
    FILE *fp;
    char *line = NULL;
    size_t len = 0;
    int length, res, i, winning_size, my_size, inc, score;
    int *winning, *mine;
    bool winning_hash[100];

    #ifdef TEST
    fp = fopen("input/day_4_example_input.txt", "r");
    winning_size = 5;
    my_size = 8;
    #endif
    #ifdef REAL
    fp = fopen("input/day_4_input.txt", "r");
    winning_size = 10;
    my_size = 25;
    #endif
    if (fp == NULL)
    {
        printf("Input file not found.");
        return 0;
    }

    winning = malloc((winning_size + my_size) * sizeof(int));
    res = 0;
    while ((length = getline(&line, &len, fp)) != -1)
    {
        clean_input(line);
        shift_left(line, get_x_occurence(line, '|', 1));
        for (i = 0; line[i] != '\0'; i++)
        {
            if (line[i] == ' ')
            {
                inc = i + 1;
                while (line[inc] == ' ')
                {
                    shift_left(line, inc);
                }
            }
        }
        split_to_int(winning, winning_size + my_size, &line[get_x_occurence(line, ':', 1) + 2], ' ');
        mine = &winning[winning_size];
        // for (i = 0; i < winning_size; i++)
        // {
        //     printf("%d ", winning[i]);
        // }
        // printf("\n");
        // for (i = 0; i < my_size; i++)
        // {
        //     printf("%d ", mine[i]);
        // }
        // printf("\n");

        clear_bool_arr(winning_hash, 100);

        for (i = 0; i < winning_size; i++)
        {
            winning_hash[winning[i]] = true;
        }
        score = 0;
        for (i = 0; i < my_size; i++)
        {
            if(winning_hash[mine[i]])
            {
                if (score == 0)
                {
                    score = 1;
                }
                else
                {
                    score *= 2;
                }
            }
        }
        res += score;
    }

    fclose(fp);
    if (line) free(line);
    free(winning);
    print_time(start, GetTickCount64());
    print_results("Total points", res);
}
