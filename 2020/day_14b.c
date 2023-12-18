
#include "../utl.h"

//#define TEST
#define REAL

/*
Guessed:

*/

#define MAX_MEM_SIZE 70000

int mask[36];
bool bits[36];
long long int addr;
long long int val;
int size;
bool *combo = NULL;
int mem_size = 0;
long long int addrs[MAX_MEM_SIZE];
long long int vals[MAX_MEM_SIZE];

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

void print_combo()
{
    for (int i = 0; i <= size; i++)
    {
        printf("%c", combo[i] ? 'T' : 'F');
    }
    printf("\n");
}

void apply_mask()
{
    int i, j;
    long long int addr_masked;
    //print_combo();
    int_to_bits(addr);
    for (i = 0, j = 0; i < 36; i++)
    {
        if (mask[i] == -1)
        {
            bits[i] = combo[j];
            j++;
        }
        else
        {
            bits[i] |= mask[i] == 1;
        }
    }
    addr_masked = bits_to_int();
    //printf("%lld\n", addr_masked);
    i = search_ll(addrs, mem_size, addr_masked);
    if (i != -1)
    {
        vals[i] = val;
    }
    else
    {
        addrs[mem_size] = addr_masked;
        vals[mem_size] = val;
        mem_size++;
        //printf("Size: %d\n", mem_size);
    }
}

void wombo_combo(int i)
{
    //printf("%d\n", i);
    combo[i] = false;
    if (i == size)
    {
        apply_mask();
        combo[i] = true;
        apply_mask();
    }
    else
    {
        wombo_combo(i + 1);
        combo[i] = true;
        wombo_combo(i + 1);
    }
}

int main(int argc, char *argv[])
{
    long long int start = GetTickCount64();
    FILE *fp;
    char *line = NULL;
    size_t len = 0;
    int length, i;
    int c = 0;
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
        //printf("%d\n", c);
        clean_input(line);
        if (line[1] == 'a')
        {
            if (combo)
            {
                free(combo);
            }
            size = 0;
            for (i = 0; i < 36; i++)
            {
                if (line[i + 7] == 'X')
                {
                    mask[i] = -1;
                    size++;
                }
                else
                {
                    mask[i] = CHAR_TO_NUM(line[i + 7]);
                }
            }
            combo = malloc(size * sizeof(bool));
            size--;
        }
        else
        {
            addr = str_to_int(line + 4, ']');
            i = find_in_str(line, '=') + 2;
            val = atoll(line + i);
            wombo_combo(0);
        }
        c++;
    }

    for (i = 0; i < mem_size; i++)
    {
        res += vals[i];
        //printf("Sum: %lld\n", vals[i]);
    }

    fclose(fp);
    if (line) free(line);
    free(combo);
    print_time(start, GetTickCount64());
    print_results("Sum of all values left in memory", res);
}
