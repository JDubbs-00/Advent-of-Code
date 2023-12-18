
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

bool execute(instruction *instructions, int i, int size, int *acc, bool *visited, bool can_switch)
{
    instruction *inst;
    if (i == size)
    {
        return true;
    }
    if (visited[i])
    {
        return false;
    }
    visited[i] = true;
    inst = &instructions[i];
    //printf("At instruction %d, accelerator: %d\n", i, *acc);
    i++;
    if (inst->type == NOP)
    {
        if (execute(instructions, i, size, acc, visited, can_switch))
        {
            return true;
        }
        if (can_switch)
        {
            inst->type = JMP;
            if (execute(instructions, i + inst->val, size, acc, visited, false))
            {
                return true;
            }
            inst->type = NOP;
        }
    }
    else if (inst->type == ACC)
    {
        (*acc) += inst->val;
        if (execute(instructions, i, size, acc, visited, can_switch))
        {
            return true;
        }
        (*acc) -= inst->val;
    }
    else
    {
        if (execute(instructions, i + inst->val, size, acc, visited, can_switch))
        {
            return true;
        }
        if (can_switch)
        {
            inst->type = NOP;
            if (execute(instructions, i, size, acc, visited, false))
            {
                return true;
            }
            inst->type = JMP;
        }
    }
    visited[i - 1] = false;
    return false;
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

    if (!execute(instructions, 0, instructions_count, &acc, visited, true))
    {
        printf("Something went wrong.\n");
    }

    fclose(fp);
    if (line) free(line);
    print_time(start, GetTickCount64());
    print_results("Accelerator value after fixing the instructions", acc);
}
