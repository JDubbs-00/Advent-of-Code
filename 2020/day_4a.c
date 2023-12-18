
#include "../utl.h"

//#define TEST
#define REAL

enum
{
    byr, //Birth Year
    iyr, //Issue Year
    eyr, //Expiration Year
    hgt, //Height
    hcl, //Hair Color
    ecl, //Eye Color
    pid, //Passport ID
    cid  //Country ID
};

static void print_results(int n)
{
    printf("# of valid passports: %d", n);
}

uint8 get_type(char *pass, int index)
{
    char type[4];
    //printf("index: %d\n", index);
    copy_string(pass + index - 3, type, 3);
    //printf("%s type found.\n", type);
    if(str_equals(type, "byr"))
    {
        return byr;
    }
    if(str_equals(type, "iyr"))
    {
        return iyr;
    }
    if(str_equals(type, "eyr"))
    {
        return eyr;
    }
    if(str_equals(type, "hgt"))
    {
        return hgt;
    }
    if(str_equals(type, "hcl"))
    {
        return hcl;
    }
    if(str_equals(type, "ecl"))
    {
        return ecl;
    }
    if(str_equals(type, "pid"))
    {
        return pid;
    }
    if(str_equals(type, "cid"))
    {
        return cid;
    }
    else
    {
        printf("Unknown string: %s", type);
        return -1;
    }
}

int get_types(char *pass, bool *types)
{
    uint8 type;
    int *indices;
    int i;
    int c = get_occurences(pass, ':', &indices, 8);
    //printf("%d fields in this line.\n", c);

    for (i = 0; i < c; i++)
    {
        type = get_type(pass, indices[i]);
        if (types[type])
        {
            printf("Duplicate found!\n");
        }
        types[type] = true;
    }

    free(indices);
    return c;
}

bool has_required_fields(bool *types)
{
    for (int i = 0; i < 7; i++)
    {
        if (!types[i]) return false;
    }
    return true;
}

bool is_valid(bool *types, int fields)
{
    return fields >= 8 || (fields == 7 && !types[cid]);
}

int main(int argc, char *argv[])
{
    long long int start = GetTickCount64();
    FILE *fp;
    char *line = NULL;
    size_t len = 0;
    int length;
    int valid = 0;
    int fields = 0;
    int *indices;
    bool types[8];

    #ifdef TEST
    fp = fopen("input/day_4_example_input.txt", "r");
    #endif
    #ifdef REAL
    fp = fopen("input/day_4_input.txt", "r");
    #endif
    if (fp == NULL)
    {
        printf("Input file not found.");
        return 0;
    }

    clear_bool_arr(types, 8);
    while ((length = getline(&line, &len, fp)) != -1)
    {
        if (is_empty_get_line(line))
        {
            if(is_valid(types, fields))
            {
                valid++;
            }
            fields = 0;
            clear_bool_arr(types, 8);
        }
        else
        {
            fields += get_types(line, types);
        }
    }
    if(is_valid(types, fields))
        {
            valid++;
        }

    fclose(fp);
    if (line) free(line);
    print_time(start, GetTickCount64());
    print_results(valid);
}
