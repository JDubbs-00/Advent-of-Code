
#include "../utl.h"

//#define TEST
#define REAL

typedef struct
{
    int min;
    int max;
} range;


typedef struct
{
    char *name;
    range ranges[2];
} field;

static void print_results(char *msg, int res)
{
    printf("%s: %d\n", msg, res);
}

void free_field(field *field)
{
    free(field->name);
}

bool in_range(range *r, int target)
{
    return target >= r->min && target <= r->max;
}

bool search(field *fields, int size, int target)
{
    for (int i = 0; i < size; i++)
    {
        if (in_range(&fields[i].ranges[0], target) || in_range(&fields[i].ranges[1], target))
        {
            return true;
        }
    }
    return false;
}

int main(int argc, char *argv[])
{
    long long int start = GetTickCount64();
    FILE *fp;
    char *line = NULL;
    size_t len = 0;
    int length, res, fields_size, i, colon, or, dash1, c;
    field *fields;
    int *vals;

    #ifdef TEST
    fp = fopen("input/day_16_example_input.txt", "r");
    fields_size = 3;
    #endif
    #ifdef REAL
    fp = fopen("input/day_16_input.txt", "r");
    fields_size = 20;
    #endif
    if (fp == NULL)
    {
        printf("Input file not found.");
        return 0;
    }

    fields = malloc(fields_size * sizeof(field));
    for (i = 0; i < fields_size; i++)
    {
        length = getline(&line, &len, fp);
        clean_input(line);
        colon = find_in_str(line, ':');
        fields[i].name = malloc((colon + 1) * sizeof(char));
        copy_str(line, fields[i].name, colon);
        dash1 = find_in_str(line, '-');
        fields[i].ranges[0].min = str_to_int(line + colon + 2, '-');
        fields[i].ranges[0].max = str_to_int(line + dash1 + 1, ' ');
        or = find_in_str(line + colon, 'o');
        fields[i].ranges[1].min = str_to_int(line + colon + or + 3, '-');
        fields[i].ranges[1].max = str_to_int(line + get_x_occurence(line, '-', 2) + 1, '\0');
    }

    length = getline(&line, &len, fp);
    length = getline(&line, &len, fp);

    length = getline(&line, &len, fp);
    clean_input(line);
    //ignore your ticket for now

    length = getline(&line, &len, fp);
    length = getline(&line, &len, fp);

    res = 0;
    vals = malloc(fields_size * sizeof(field));
    while ((length = getline(&line, &len, fp)) != -1)
    {
        clean_input(line);
        split_to_int(vals, fields_size, line, ',');
        for (i = 0; i < fields_size; i++)
        {
            if (!search(fields, fields_size, vals[i]))
            {
                res += vals[i];
            }
        }
    }

    fclose(fp);
    if (line) free(line);
    for (i = 0; i < fields_size; i++)
    {
        free_field(fields + i);
    }
    free(fields);
    free(vals);
    print_time(start, GetTickCount64());
    print_results("Ticket scanning error rate", res);
}
