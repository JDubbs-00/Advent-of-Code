#include "../utl.h"

//#define TEST
#define REAL

struct node
{
    char name[4];
    int name_hash_l;
    int name_hash_r;
    struct node *l;
    struct node *r;
    struct node *next;
};

struct node *find_node(struct node *list, char *target)
{
    while (list)
    {
        if (str_equals_length(target, list->name, 3))
        {
            return list;
        }
        list = list->next;
    }

    return NULL;
}

int name_to_hash(char *name)
{
    return (HASH_UPPER_CHAR(name[0]) * 26 * 26) + (HASH_UPPER_CHAR(name[1]) * 26) + HASH_UPPER_CHAR(name[2]);
}

void hash_to_name(int n, char *name)
{
    name[0] = UPPER_CHAR_FROM_HASH(n / (26 * 26));
    //printf("%c\n", name[0]);
    n %= (26 * 26);
    name[1] = UPPER_CHAR_FROM_HASH(n / 26);
    //printf("%c\n", name[1]);
    n %= 26;
    name[2] = UPPER_CHAR_FROM_HASH(n);
    //printf("%c\n", name[2]);
    name[3] = '\0';
    //printf("%s\n", name);
}

struct node *find_node_from_hash(struct node *list, int hash)
{
    char name[4];

    hash_to_name(hash, name);
    return find_node(list, name);
}

struct node *make_node(char *s)
{
    struct node *n;
    char name[4];

    n = malloc(sizeof(struct node));
    copy_str(&s[0], n->name, 3);
    copy_str(&s[7], name, 3);
    n->name_hash_l = name_to_hash(name);
    copy_str(&s[12], name, 3);
    n->name_hash_r = name_to_hash(name);

    n->l = NULL;
    n->r = NULL;
    n->next = NULL;

    return n;
}

int main(int argc, char *argv[])
{
    long long int start = GetTickCount64();
    FILE *fp;
    char *line = NULL;
    char *instructions = NULL;
    size_t len = 0;
    int length, res;
    struct node *head, *tail, *c, *end;
    char *i;

    #ifdef TEST
    fp = fopen("input/day_8_example_input.txt", "r");
    #endif
    #ifdef REAL
    fp = fopen("input/day_8_input.txt", "r");
    #endif
    if (fp == NULL)
    {
        printf("Input file not found.");
        return 0;
    }

    getline(&instructions, &len, fp);
    clean_input(instructions);
    getline(&line, &len, fp);
    getline(&line, &len, fp);
    clean_input(line);
    head = make_node(line);
    tail = head;

    while ((length = getline(&line, &len, fp)) != -1)
    {
        clean_input(line);
        tail->next = make_node(line);
        tail = tail->next;
    }

    for (c = head; c; c = c->next)
    {
        c->l = find_node_from_hash(head, c->name_hash_l);
        c->r = find_node_from_hash(head, c->name_hash_r);
        //printf("%s, LEFT: %s, RIGHT: %s\n", c->name, c->l->name, c->r->name);
    }

    for (res = 0, i = instructions, c = find_node(head, "AAA"), end = find_node(head, "ZZZ"); c != end; res++, i++)
    {
        if (*i == '\0')
        {
            i = instructions;
        }
        //printf("%s\n", c->name);
        if (*i == 'L')
        {
            //printf("Going left\n");
            c = c->l;
        }
        else
        {
            //printf("Going right\n");
            c = c->r;
        }
    }

    fclose(fp);
    if (line) free(line);
    if (instructions) free(instructions);
    for (; head; head = c)
    {
        c = head->next;
        free(head);
    }
    print_time(start, GetTickCount64());
    print_results("Steps to 'ZZZ'", res);
}
