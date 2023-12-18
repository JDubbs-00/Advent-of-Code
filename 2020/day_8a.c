
#include "../utl.h"

//#define TEST
#define REAL

enum Type
{
    NOP,
    ACC,
    JMP
};

typedef struct
{
    int type;
    int val;
} instruction;

static void print_results(char *msg, int res)
{
    printf("%s: %d\n", msg, res);
}

int main(int argc, char *argv[])
{
    long long int start = GetTickCount64();
    FILE *fp;
    char *line = NULL;
    size_t len = 0;
    int length, instructions_count;
    int acc = 0;
    int i = 0;
    instruction *instructions;
    instruction *inst;
    bool *visited;

    #ifdef TEST
    fp = fopen("input/day_8_example_input.txt", "r");
    instructions_count = 9;
    #endif
    #ifdef REAL
    fp = fopen("input/day_8_input.txt", "r");
    instructions_count = 631;
    #endif
    if (fp == NULL)
    {
        printf("Input file not found.");
        return 0;
    }

    instructions = malloc(instructions_count * sizeof(instruction));
    visited = malloc(instructions_count * sizeof(bool));
    clear_bool_arr(visited, instructions_count);
    while ((length = getline(&line, &len, fp)) != -1)
    {
        clean_input(line);
        //printf("%s", line);
        inst = &instructions[i];
        inst->val = atoi(line + 4);
        if (line[0] == 'n')
        {
            inst->type = NOP;
        }
        else if (line[0] == 'a')
        {
            inst->type = ACC;
        }
        else
        {
            inst->type = JMP;
            inst->val--;
        }
        //printf("Val: %d\n", inst->val);
        i++;
    }

    i = 0;
    while(!visited[i])
    {
        visited[i] = true;
        inst = &instructions[i];
        if (inst->type == ACC)
        {
            acc += inst->val;
        }
        else if (inst->type == JMP)
        {
            i += inst->val;
        }
        i++;
    }


    fclose(fp);
    if (line) free(line);
    print_time(start, GetTickCount64());
    print_results("Accelerator value before entering the loop", acc);
}
