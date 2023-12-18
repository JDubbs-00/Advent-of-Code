
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

bool is_valid_year(char *year, int min, int max)
{
    int n = atoi(year);
    //printf("Year: %d\n", n);
    return n >= min && n <= max;
}

bool is_valid_hair(char *color)
{
    int i;
    char c;
    if (str_length(color) != 6) return false;
    for (i = 0; i < 6; i++)
    {
        c = color[i];
        if (c < ASCII_0 || (c > ASCII_9 && c < ASCII_LOWER_A) || c > 102) return false;
    }
    return true;
}
bool is_valid_pid(char *pid)
{
    int i;
    if (str_length(pid) != 9) return false;
    for (i = 0; i < 9; i++)
    {
        if (!is_num(pid[i])) return false;
    }
    //printf("PID is valid.\n");
    return true;
}

int get_type(char *pass, int index)
{
    char type[4];
    char val[10];
    //printf("index: %d\n", index);
    copy_str(pass + index - 3, type, 3);
    //printf("%s type found.\n", type);
    index++;
    if(str_equals(type, "byr"))
    {
        copy_str_terminator(pass + index, val, ' ');
        if (is_valid_year(val, 1920, 2002))
        {
            return byr;
        }
    }
    else if(str_equals(type, "iyr"))
    {
        copy_str_terminator(pass + index, val, ' ');
        if (is_valid_year(val, 2010, 2020))
        {
            return iyr;
        }
    }
    else if(str_equals(type, "eyr"))
    {
        copy_str_terminator(pass + index, val, ' ');
        if (is_valid_year(val, 2020, 2030))
        {
            return eyr;
        }
    }
    else if(str_equals(type, "hgt"))
    {
        char t = copy_str_terminators(pass + index, val, "ic ");
        int h = atoi(val);
        //printf("Height: %d, type: %c\n", h, t);
        if ((t == 'i' && h >= 59 && h <= 76) || (t == 'c' && h >= 150 && h <= 193))
        {
            return hgt;
        }
    }
    else if(str_equals(type, "hcl"))
    {
        if (pass[index] == '#')
        {
            copy_str_terminator(pass + index + 1, val, ' ');
            //printf("Hair color: #%s\n", val);
            if (is_valid_hair(val))
            {
                return hcl;
            }
        }
    }
    else if(str_equals(type, "ecl"))
    {
        const char *colors[] = {"amb", "blu", "brn", "gry", "grn", "hzl", "oth"};
        copy_str_terminator(pass + index, val, ' ');
        //printf("Eye color: %s\n", val);
        if (str_in_array(colors, 7, val))
        {
            return ecl;
        }
    }
    else if(str_equals(type, "pid"))
    {
        copy_str_terminator(pass + index, val, ' ');
        //printf("PID: %s\n", val);
        if (is_valid_pid(val))
        {
            return pid;
        }
    }
    else if(str_equals(type, "cid"))
    {
        return cid;
    }
    else
    {
        printf("Unknown string: %s", type);
        return -1;
    }
    return -1;
}

int get_types(char *pass, bool *types)
{
    int type;
    int *indices;
    int i;
    int c = get_occurences(pass, ':', &indices, 8);
    //printf("%d fields in this line.\n", c);

    for (i = 0; i < c; i++)
    {
        type = get_type(pass, indices[i]);
        if (type == -1)
        {
            //char temp[100];
            //copy_str_terminator(pass + indices[i] - 3, temp, ' ');
            //printf("Invalid type.(%s)\n", temp);
            return 0;
        }
        else if (types[type])
        {
            printf("Duplicate found!\n");
        }
        else
        {
            types[type] = true;
        }
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
        remove_char(line, '\n');
        remove_char(line, CR);
        //printf("%d ", line[str_length(line)]);
        if (is_empty_get_line(line))
        {
            //printf("%d fields valid.\n", fields);
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
    //printf("%d fields valid.\n", fields);
    if(is_valid(types, fields))
        {
            valid++;
        }

    fclose(fp);
    if (line) free(line);
    print_time(start, GetTickCount64());
    print_results(valid);
}
