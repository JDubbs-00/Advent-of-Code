
#include "../utl.h"

//#define TEST
#define REAL

#define NAME_SIZE 30

typedef struct
{
    char name[NAME_SIZE];
    int *contents;
    int containers[100];
    int contents_count;
    int containers_count;
    int id;
    bool shiny;
} Bag;

static void print_results(int n)
{
    printf("Number of bags that can contain a shiny gold bag: %d\n", n);
}

static Bag *init_bags(int size)
{
    Bag *bags = malloc(size * sizeof(Bag));
    bags->contents_count = 0;
    bags->containers_count = 0;
    bags->shiny = false;
    return bags;
}

int get_content_count(char *s)
{
    int i, c;
    for (i = 0, c = 0; s[i] != '\0'; i++)
    {
        if (is_num(s[i]))
        {
            c++;
        }
    }
    return c;
}

int name_to_id(Bag *bags, int size, char *name)
{
    for (int i = 0; i < size; i++)
    {
        if (str_equals(bags[i].name, name)) return bags[i].id;
    }
    return -1;
}

void append_id(Bag *bag, int id)
{
    bag->containers[bag->containers_count++] = id;
}

void contains_shiny(Bag *bags, int id)
{
    int i;
    Bag *b = &bags[id];
    b->shiny = true;
    for (i = 0; i < b->containers_count; i++)
    {
        contains_shiny(bags, b->containers[i]);
    }
}

int main(int argc, char *argv[])
{
    long long int start = GetTickCount64();
    FILE *fp;
    char *line = NULL;
    size_t len = 0;
    int length, bag_count, i, j;
    int c = 0;
    Bag *bags;
    Bag *bag;
    char name[NAME_SIZE];

    #ifdef TEST
    fp = fopen("input/day_7_example_input.txt", "r");
    bag_count = 9;
    #endif
    #ifdef REAL
    fp = fopen("input/day_7_input.txt", "r");
    bag_count = 594;
    #endif
    if (fp == NULL)
    {
        printf("Input file not found.");
        return 0;
    }

    bags = init_bags(bag_count);
    while ((length = getline(&line, &len, fp)) != -1)
    {
        clean_input(line);
        bag = &bags[c];
        i = get_x_occurence(line, ' ', 2);
        bag->id = c;
        memcpy(bag->name, line, i * sizeof(char));
        bag->name[i] = '\0';
        //printf("%s\n", bag->name);
        c++;
    }

    fclose(fp);
    #ifdef TEST
    fp = fopen("input/day_7_example_input.txt", "r");
    #endif
    #ifdef REAL
    fp = fopen("input/day_7_input.txt", "r");
    #endif

    c = 0;
    while ((length = getline(&line, &len, fp)) != -1)
    {
        clean_input(line);
        bag = &bags[c];
        bag->contents_count = get_content_count(line);
        bag->contents = malloc(bag->contents_count * sizeof(int));
        //printf("%d bags can be contained in %s: ", bag->contents_count, bag->name);
        for (i = 13; line[i] != '\0'; i++)
        {
            if (is_num(line[i]))
            {
                i += 2;
                j = get_x_occurence(&line[i], ' ', 2);
                memcpy(name, &line[i], j * sizeof(char));
                name[j] = '\0';
                //printf("%s, ", name);
                j = name_to_id(bags, bag_count, name);
                //printf("ID: %d\n", j);
                append_id(&bags[j], bag->id);
                i += 4;
            }
        }
        //printf("\n");
        c++;
    }

    i = name_to_id(bags, bag_count, "shiny gold");
    //printf("shiny gold index: %d\n", i);
    contains_shiny(bags, i);

    c = -1;
    for (i = 0; i < bag_count; i++)
    {
        if (bags[i].shiny)
        {
            //printf("%s\n", bags[i].name);
            c++;
        }
    }

    fclose(fp);
    if (line) free(line);
    for (i = 0; i < bag_count; i++)
    {
        free(bags[i].contents);
    }
    free(bags);
    print_time(start, GetTickCount64());
    print_results(c);
}
