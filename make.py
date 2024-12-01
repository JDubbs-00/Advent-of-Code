import sys
import os

year = sys.argv[1]

os.mkdir(year)
os.mkdir(year + "/" + "input")

for i in range(1, 26):
    f_in = open(year + "/input/day_" + str(i) + "_input.txt", "w")
    f_in.close()

    f_ex = open(year + "/input/day_" + str(i) + "_example_input.txt", "w")
    f_ex.close()
    sub_day = str(i)
    day = "day_" + sub_day + "a"

    f_day = open(year + "/" + day + ".c", "w")
    f_day.write(
"""#include "../utl.h"

#define TEST
//#define REAL

// GUESSES:

int main(int argc, char *argv[])
{
    long long int start = GetTickCount64();
    FILE *fp;
    char *line = _malloc(MAX_LINE_LEN);
    int res;

""")
    f_day.write("    #ifdef TEST\n")
    f_day.write("    fp = fopen(\"input/" + day[:-1] + "_example_input.txt\", \"r\");\n")
    f_day.write("    #endif\n")
    f_day.write("    #ifdef REAL\n")
    f_day.write("    fp = fopen(\"input/" + day[:-1] + "_input.txt\", \"r\");\n")
    f_day.write("    #endif")
    f_day.write(
"""
    if (fp == NULL)
    {
        printf("Input file not found.");
        return 0;
    }

    

    while ((fgets(line, MAX_LINE_LEN, fp)) != NULL)
    {
        clean_input(line);
        //printf("%s", line);
    }

    

    if (ferror(fp)) printf("Error reading file.");
    fclose(fp);
    if (line) free(line);
    emancipation_proclamation();
    print_time(start, GetTickCount64());
    print_malloced_mem();
    print_results("", res);
}
""")
    f_day.close()

f_comp = open(year + "/comp.sh", "w")
f_comp.write("gcc -o x.exe day_$1$2.c; x.exe")
f_comp.close()
