
#include "../utl.h"

//#define TEST
#define REAL

/*
Guessed:
266695781 - low
1726098936 - low
10056808196593 - high
*/

#define MAX_MEM_SIZE 400

int mask[36];
bool bits[36];

static void print_results(char *msg, long long int res)
{
    printf("%s: %lld\n", msg, res);
}

void int_to_bits(long long int n)
{
    long long int x = 34359738368;
    for (int i = 0; i < 36; i++, x /= 2)
    {
        bits[i] = n >= x;
        if (bits[i])
        {
            n -= x;
            //printf("1 at %d\n", i);
        }
    }
}

long long int bits_to_int()
{
    long long int x = 34359738368;
    long long n = 0;
    for (int i = 0; i < 36; i++, x /= 2)
    {
        if (bits[i])
        {
            n += x;
        }
    }
    return n;
}

void apply_mask()
{
    for (int i = 0; i < 36; i++)
    {
        if (mask[i] != -1)
        {
            //printf("bits[%d] forced to %d\n", i, mask[i]);
            bits[i] = mask[i] == 1;
        }
    }
}

int main(int argc, char *argv[])
{
    long long int start = GetTickCount64();
    FILE *fp;
    char *line = NULL;
    size_t len = 0;
    int length, i, addr;
    int mem_size = 0;
    int addrs[MAX_MEM_SIZE];
    long long int vals[MAX_MEM_SIZE];
    long long int res = 0;

    #ifdef TEST
    fp = fopen("input/day_14_example_input.txt", "r");
    #endif
    #ifdef REAL
    fp = fopen("input/day_14_input.txt", "r");
    #endif
    if (fp == NULL)
    {
        printf("Input file not found.");
        return 0;
    }

    while ((length = getline(&line, &len, fp)) != -1)
    {
        clean_input(line);
        if (line[1] == 'a')
        {
            for (i = 0; i < 36; i++)
            {
                if (line[i + 7] == 'X')
                {
                    mask[i] = -1;
                }
                else
                {
                    mask[i] = CHAR_TO_NUM(line[i + 7]);
                }
                //printf("%c", line[i + 7]);
            }
            //printf("\n");
        }
        else
        {
            addr = str_to_int(line + 4, ']');
            //printf("Address: %d\n", addr);
            i = find_in_str(line, '=') + 2;
            int_to_bits(atoll(line + i));
            apply_mask();
            i = search_int(addrs, mem_size, addr);
            if (i != -1)
            {
                //printf("Address match found.\n");
                vals[i] = bits_to_int();
                //printf("%lld\n", vals[i]);
            }
            else
            {
                addrs[mem_size] = addr;
                vals[mem_size] = bits_to_int();
                //printf("%lld\n", vals[mem_size]);
                mem_size++;
            }
        }
    }

    for (i = 0; i < mem_size; i++)
    {
        res += vals[i];
        //printf("Sum: %lld\n", vals[i]);
    }

    fclose(fp);
    if (line) free(line);
    print_time(start, GetTickCount64());
    print_results("Sum of all values left in memory", res);
}
