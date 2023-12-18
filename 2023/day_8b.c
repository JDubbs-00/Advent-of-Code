#include "../utl.h"

//#define TEST
#define REAL

struct node
{
    char name[4];
    int name_hash_l;
    int name_hash_r;
    struct node *nodes[2];
    struct node *next;
};

static int size = 0;

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

    n->nodes[0] = NULL;
    n->nodes[1] = NULL;
    n->next = NULL;

    if (n->name[2] == 'A')
    {
        size++;
    }

    return n;
}

// bool all_end_z(struct node **a)
// {
//     for (int i = 0; i < size; i++)
//     {
//         if (a[i]->name[2] != ASCII_UPPER_Z)
//         {
//             return FALSE;
//         }
//     }

//     return TRUE;
// }

void merge_special(long long int *arr, int l, int m, int r)
{
    int i, j, k;
    int n1 = m - l + 1;
    int n2 = r - m;
    long long int *L, *R;

    L = malloc(n1 * sizeof(long long int));
    R = malloc(n2 * sizeof(long long int));

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
        if (L[i] > R[j])
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

void merge_sort_special(long long int *arr, int l, int r)
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
    char *instructions = NULL;
    size_t len = 0;
    int length, a_count, z_count, j, k;
    long long int res;
    size_t offset;
    struct node *head, *tail, *c;
    struct node **a;
    char *i;
    long long int *repeaters;

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

    a = malloc(size * sizeof(struct node *));
    repeaters = malloc(size * sizeof(long long int));
    clear_ll_arr(repeaters, size);

    for (c = head, a_count = 0, z_count = 0; c; c = c->next)
    {
        c->nodes[0] = find_node_from_hash(head, c->name_hash_l);
        c->nodes[1] = find_node_from_hash(head, c->name_hash_r);
        //printf("%s, LEFT: %s, RIGHT: %s\n", c->name, c->l->name, c->r->name);
        if (c->name[2] == ASCII_UPPER_A)
        {
            a[a_count++] = c;
        }
    }

    for (j = 0, i = instructions; is_in_ll_arr(repeaters, size, 0); j++, i++)
    {
        if (*i == '\0')
        {
            i = instructions;
        }
        if (*i == 'L')
            {
                offset = 0;
            }
            else
            {
                offset = 1;
            }
        for (k = 0; k < size; k++)
        {
            if (repeaters[k] == 0 && a[k]->name[2] == ASCII_UPPER_Z)
            {
                repeaters[k] = (long long int)j;
                //printf("%d\n", j);
            }
            a[k] = a[k]->nodes[offset];
        }
    }

    while (size > 1)
    {
        merge_sort_special(repeaters, 0, size - 1);
        //print_ll_arr(repeaters, size);
        repeaters[size - 2] = lcm(repeaters[size - 1], repeaters[size - 2]);
        //printf("LCM: %lld\n", repeaters[size - 2]);
        size--;
    }

    res = repeaters[0];

    fclose(fp);
    if (line) free(line);
    if (instructions) free(instructions);
    for (; head; head = c)
    {
        c = head->next;
        free(head);
    }
    free(a);
    free(repeaters);
    print_time(start, GetTickCount64());
    print_results_ll("Steps to all nodes ending with 'Z'", res);
}
