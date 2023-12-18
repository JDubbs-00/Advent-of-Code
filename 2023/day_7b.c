#include "../utl.h"

//#define TEST
#define REAL

// GUESSES:
// 251526188 - high
// 250222719 - low
// 252147660 - high

typedef uint8 hand_type;
enum
{
    FIVE_KIND,
    FOUR_KIND,
    FULL_HOUSE,
    THREE_KIND,
    TWO_PAIR,
    ONE_PAIR,
    HIGH_CARD
};

typedef struct
{
    char cards[6];
    int bid;
    hand_type type;
} hand;

char *get_type_str(hand_type t)
{
    static char *type_strs[7] =
    {
        "Five of a Kind",
        "Four of a Kind",
        "Full House",
        "Three of a Kind",
        "Two Pairs",
        "One Pair",
        "High Card"
    };

    return type_strs[t];
}

int char_to_index(char c)
{
    if (is_num(c))
    {
        return c - 49;
    }

    switch (c)
    {
    case 'A':
        return 12;
    case 'K':
        return 11;
    case 'Q':
        return 10;
    case 'J':
        return 0;
    default:
        return 9;
    }
}

void get_type(hand *h)
{
    int counts[13];
    int i, max, j;

    clear_int_arr(counts, 13);
    for (i = 0; i < 5; i++)
    {
        counts[char_to_index(h->cards[i])]++;
    }

    max = get_max(&counts[1], 12);
    j = counts[0];
    if (max + j == 5)
    {
        h->type = FIVE_KIND;
        //printf("%s has %d jokers and is '%s'\n", h->cards, j, get_type_str(h->type));
    }
    else if (max + j == 4)
    {
        h->type = FOUR_KIND;
    }
    else if (max == 3)
    {
        if (is_in_int_arr(counts, 13, 2))
        {
            h->type = FULL_HOUSE;
        }
        else
        {
            h->type = THREE_KIND;
        }
    }
    else if (j == 2)
    {
        h->type = THREE_KIND;
    }
    else if (max == 2)
    {
        if (count_occurences_int(counts, 13, 2) == 2)
        {
            h->type = TWO_PAIR;
        }
        else
        {
            h->type = ONE_PAIR;
        }
        if (j == 1)
        {
            h->type -= 2;
        }
    }
    else if (j == 1)
    {
        h->type = ONE_PAIR;
    }
    else
    {
        h->type = HIGH_CARD;
    }
    // if (h->type == FIVE_KIND)
    // {
    //     printf("%s (max: %d) - ", h->cards, max);
    //     print_int_arr(counts, 13);
    // }
    //printf("%s has %d jokers and is '%s'\n", h->cards, j, get_type_str(h->type));
}

bool hand_less_than(const hand *l, const hand *r)
{
    int i;
    if (l->type == r->type)
    {
        for (i = 0; i < 6; i++)
        {
            if (l->cards[i] != r->cards[i])
            {
                return char_to_index(l->cards[i]) < char_to_index(r->cards[i]);
            }
        }
    }
    return l->type > r->type;
}

void merge_special(hand *arr, int l, int m, int r)
{
    int i, j, k;
    int n1 = m - l + 1;
    int n2 = r - m;
    hand *L, *R;

    L = malloc(n1 * sizeof(hand));
    R = malloc(n2 * sizeof(hand));

    for (i = 0; i < n1; i++)
    {
        L[i] = arr[l + i];
    }
    for (j = 0; j < n2; j++)
    {
        R[j] = arr[m + 1 + j];
    }

    i = 0;
    j = 0;
    k = l;
    while (i < n1 && j < n2)
    {
        if (hand_less_than(&L[i], &R[j]))
        {
            arr[k] = L[i];
            i++;
        }
        else
        {
            arr[k] = R[j];
            j++;
        }
        k++;
    }

    while (i < n1)
    {
        arr[k] = L[i];
        i++;
        k++;
    }

    while (j < n2)
    {
        arr[k] = R[j];
        j++;
        k++;
    }

    free(L);
    free(R);
}

void merge_sort_special(hand *arr, int l, int r)
{
    if (l < r)
    {
        int m = l + (r - l) / 2;

        merge_sort_special(arr, l, m);
        merge_sort_special(arr, m + 1, r);

        merge_special(arr, l, m, r);
    }
}

int main(int argc, char *argv[])
{
    long long int start = GetTickCount64();
    FILE *fp;
    char *line = NULL;
    size_t len = 0;
    int length, res, hands_cnt, i;
    hand *hands, *h;

    #ifdef TEST
    fp = fopen("input/day_7_example_input.txt", "r");
    hands_cnt = 5;
    #endif
    #ifdef REAL
    fp = fopen("input/day_7_input.txt", "r");
    hands_cnt = 1000;
    #endif
    if (fp == NULL)
    {
        printf("Input file not found.");
        return 0;
    }

    hands = malloc(hands_cnt * sizeof(hand));
    i = 0;
    while ((length = getline(&line, &len, fp)) != -1)
    {
        clean_input(line);
        h = &hands[i];
        copy_str(line, h->cards, 5);
        //printf("%s\n", h->cards);
        h->bid = str_to_int(&line[6], '\0');
        get_type(h);
        i++;
    }

    merge_sort_special(hands, 0, hands_cnt - 1);
    res = 0;
    for (i = 0; i < hands_cnt; i++)
    {
        //printf("%s - %s\n", hands[i].cards, get_type_str(hands[i].type));
        res += hands[i].bid * (i + 1);
    }

    fclose(fp);
    if (line) free(line);
    free(hands);
    print_time(start, GetTickCount64());
    print_results("Total winnings", res);
}
