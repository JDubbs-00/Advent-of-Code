
#include "../utl.h"

#define TEST
//#define REAL

#define TICKETS 200

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

typedef struct
{
    int val;
    bool *in_range;
} value;


typedef struct
{
    value *vals;
} ticket;


ticket tickets[TICKETS];
field *fields;
int tickets_size;
int fields_size;
int *field_to_index;

static void print_results(char *msg, int res)
{
    printf("%s: %d\n", msg, res);
}

bool in_range(range *r, int target)
{
    return target >= r->min && target <= r->max;
}

bool check_range(int i, int target)
{
    return in_range(&fields[i].ranges[0], target) || in_range(&fields[i].ranges[1], target);
}

bool search(int size, int target)
{
    for (int i = 0; i < size; i++)
    {
        if (check_range(i, target))
        {
            return true;
        }
    }
    return false;
}

void check_ticket_ranges(int t, int v, int size)
{
    for (int i = 0; i < size; i++)
    {
        tickets[t].vals[v].in_range[i] = check_range(i, tickets[t].vals[v].val);
    }
}

bool field_in_any_range(int t, int v, int size)
{
    for (int i = 0; i < size; i++)
    {
        if (tickets[t].vals[v].in_range[i])
        {
            return true;
        }
    }
    return false;
}

bool all_vals_in_range(int t, int size)
{
    for (int v = 0; v < size; v++)
    {
        if (!field_in_any_range(t, v, size))
        {
            return false;
        }
    }
    return true;
}

int main(int argc, char *argv[])
{
    long long int start = GetTickCount64();
    FILE *fp;
    char *line = NULL;
    size_t len = 0;
    int length, res, i, colon, or, dash1, c, j;
    int *my_ticket;
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

    field_to_index = malloc(fields_size * sizeof(field));
    fields = malloc(fields_size * sizeof(field));
    vals = malloc(fields_size * sizeof(int));
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
    my_ticket = malloc(fields_size * sizeof(int));
    split_to_int(my_ticket, fields_size, line, ',');

    length = getline(&line, &len, fp);
    length = getline(&line, &len, fp);

    res = 1;

    for (i = 0; i < TICKETS; i++)
    {
        tickets[i].vals = malloc(tickets_size * sizeof(value));
        for (j = 0; j < fields_size; j++)
        {
            tickets[i].vals[j].in_range = malloc(tickets_size * sizeof(bool));
        }
    }

    tickets_size = 0;
    while ((length = getline(&line, &len, fp)) != -1)
    {
        clean_input(line);
        split_to_int(vals, fields_size, line, ',');
        for (i = 0; i < fields_size; i++)
        {
            tickets[tickets_size].vals[i].val = vals[i];
        }
        for (i = 0; i < fields_size; i++)
        {
            check_ticket_ranges(tickets_size, i, fields_size);
        }
        if (all_vals_in_range(tickets_size, fields_size))
        {
            tickets_size++;
        }
        printf("%d\n", tickets_size);
    }

    fclose(fp);
    if (line) free(line);
    for (i = 0; i < fields_size; i++)
    {
        free(fields[i].name);
    }
    free(fields);
    for (i = 0; i < TICKETS; i++)
    {
        for (j = 0; j < fields_size; j++)
        {
            free(tickets[i].vals[j].in_range);
        }
    }
    free(my_ticket);
    free(field_to_index);
    free(vals);
    print_time(start, GetTickCount64());
    print_results("Multiplying 6 departure values together", res);
}
