#define _GNU_SOURCE

#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include <math.h>

#include "mem.h"

#define SEC_TO_MS CLOCKS_PER_SEC
#define MAX_LINE_LEN 256

#define ABS(n) ((n < 0) ? -(n) : n)
#define MAX(n1, n2) ((n1 > n2) ? n1 : n2)
#define MIN(n1, n2) ((n1 < n2) ? n1 : n2)
#define CHAR_TO_NUM(c) (c - 48)

#define ALPHABET_SIZE 26
#define ASCII_UPPER_A 'A'
#define ASCII_UPPER_Z 'Z'
#define ASCII_LOWER_A 'a'
#define ASCII_LOWER_Z 'z'
#define ASCII_0 '0'
#define ASCII_9 '9'
#define MAX_DIGITS 10
#define MAX_DIGITS_LL 20
#define CR 13
#define PI 3.14159265359

#define HASH_LOWER_CHAR(c) (c - ASCII_LOWER_A)
#define HASH_UPPER_CHAR(c) (c - ASCII_UPPER_A)
#define LOWER_CHAR_FROM_HASH(i) (i + ASCII_LOWER_A)
#define UPPER_CHAR_FROM_HASH(i) (i + ASCII_UPPER_A)

#define clear(p) memset((void *)(p), 0, sizeof *(p))

typedef unsigned char       uint8;
typedef unsigned short int  uint16;
typedef unsigned long int   uint32;

typedef uint8 direction;
enum {
    DIRECTION_NONE,
    UP,
    DOWN,
    LEFT,
    RIGHT,
    DIRECTION_ALL
};

// Is number?
bool is_num(char c)
{
    return c >= ASCII_0 && c <= ASCII_9;
}

// Is uppercase character?
bool is_uppercase(char c)
{
    return c >= ASCII_UPPER_A && c <= ASCII_UPPER_Z;
}

// Is lowercase character?
bool is_lowercase(char c)
{
    return c >= ASCII_LOWER_A && c <= ASCII_LOWER_Z;
}

// Is string empty?
bool is_empty_str(char *s)
{
    return s[0] == '\0';
}

// Is (x, y) pair within bounds of a grid?
bool is_inbounds(int rows, int cols, int r, int c)
{
    return r >= 0 && r < rows && c >= 0 && c < cols;
}

// Are two strings equal?
bool str_equals(const char *s1, const char *s2)
{
    return strcmp(s1, s2) == 0;
}

// Are two strings equal up to a given length?
bool str_equals_length(const char *s1, const char *s2, int length)
{
    for (int i = 0; i < length; i++)
    {
        if (s1[i] != s2[i])
        {
            return false;
        }
    }

    return true;
}

// Does a target character exist within a string? 
bool is_in_str(const char *s, char target)
{
    for (int i = 0; s[i] != '\0'; i++)
    {
        if (s[i] == target)
        {
            return true;
        }
    }
    return false;
}

// Does a target int exist within an array?
bool is_in_int_arr(int *arr, int size, int target)
{
    for (int i = 0; i < size; i++)
    {
        if (arr[i] == target) return true;
    }
    return false;
}

// Does a target large int exist within an array?
bool is_in_ll_arr(long long int *arr, int size, long long int target)
{
    for (int i = 0; i < size; i++)
    {
        if (arr[i] == target) return true;
    }
    return false;
}

// Count the number of occurences in a hash
int count_hash(bool *arr, int size)
{
    int i, sum;
    for (i = 0, sum = 0; i < size; i++)
    {
        if (arr[i]) sum++;
    }
    return sum;
}

// Gets the index of the nth occurence of a character within a string
int get_x_occurence(const char *s, char target, int x)
{
    for (int i = 0; s[i] != '\0'; i++)
    {
        if (s[i] == target)
        {
            x--;
            if (x == 0) return i;
        }
    }
    return -1;
}

// Gets the indices of occurences of a character within a string
int get_occurences(char *s, char target, int **arr, int max)
{
    int i;
    int c = 0;
    *arr = _malloc(max * sizeof(int));
    for (i = 0; s[i] != '\0'; i++)
    {
        if (s[i] == target)
        {
            //printf("%c found at index %d\n", target, i);
            (*arr)[c++] = i;
        }
    }
    return c;
}

// Counts the occurences of a characer within a string
int count_occurences(char *s, char target)
{
    int i;
    int c = 0;

    for (i = 0; s[i] != '\0'; i++)
    {
        if (s[i] == target)
        {
            c++;
        }
    }
    return c;
}

// Counts the occurences of an int within an array
int count_occurences_int(int *arr, int size, int target)
{
    int i;
    int c = 0;

    for (i = 0; i < size; i++)
    {
        if (arr[i] == target)
        {
            c++;
        }
    }
    return c;
}

// Gets the minimum large int value in an array
long long int get_min_ll(long long int *arr, int size)
{
    long long int min = arr[0];
    for (int i = 1; i < size; i++)
    {
        if (arr[i] < min) min = arr[i];
    }
    return min;
}

// Gets the maximum large int value in an array
long long int get_max_ll(long long int *arr, int size)
{
    long long int max = arr[0];
    for (int i = 1; i < size; i++)
    {
        if (arr[i] > max) max = arr[i];
    }
    return max;
}

// Gets the minimum int value in an array
int get_min(int *arr, int size)
{
    int min = arr[0];
    for (int i = 1; i < size; i++)
    {
        if (arr[i] < min) min = arr[i];
    }
    return min;
}

// Gets the maximum int value in an array
int get_max(int *arr, int size)
{
    int max = arr[0];
    for (int i = 1; i < size; i++)
    {
        if (arr[i] > max) max = arr[i];
    }
    return max;
}

// Gets the index of the first occurence of a target int within an array
int search_int(int *arr, int size, int target)
{
    for (int i = 0; i < size; i++)
    {
        if (arr[i] == target)
        {
            return i;
        }
    }
    return -1;
}

// Gets the index of the last occurence of a target int within an array
int search_int_rev(int *arr, int size, int target)
{
    for (int i = size - 1; i >= 0; i--)
    {
        if (arr[i] == target)
        {
            return i;
        }
    }
    return -1;
}

// Gets the index of the first occurence of a target large int within an array
int search_ll(long long int *arr, int size, long long int target)
{
    for (int i = 0; i < size; i++)
    {
        if (arr[i] == target)
        {
            return i;
        }
    }
    return -1;
}

// Copies a string
void copy_str(char *from, char *to, int amount)
{
    memcpy(to, from, amount * sizeof(char));
    to[amount] = '\0';
}

// Copies a string, stops at a given terminator 
void copy_str_terminator(const char *from, char *to, char terminator)
{
    int i;
    for (i = 0; from[i] != terminator && from[i] != '\0'; i++)
    {
        to[i] = from[i];
    }
    to[i] = '\0';
}

// Copies a string, stops at given terminators
char copy_str_terminators(char *from, char *to, const char *terminators)
{
    int i;
    for (i = 0; from[i] != '\0' && !is_in_str(terminators, from[i]); i++)
    {
        to[i] = from[i];
    }
    to[i] = '\0';
    return from[i];
}

// Copies an int array
void copy_int_array(int *from, int *to, int size)
{
    memcpy(to, from, size * sizeof(int));
}

// Clears a boolean array
void clear_bool_arr(bool *arr, int size)
{
    memset(arr, 0, size * sizeof(bool));
}

// Clears an int array
void clear_int_arr(int *arr, int size)
{
    memset(arr, 0, size * sizeof(int));
}

// Clears a large int array
void clear_ll_arr(long long int *arr, int size)
{
    memset(arr, 0, size * sizeof(long long int));
}

// Initializes a 2D character array (or an array of strings)
char **init_2d_char(int cols, int rows)
{
    int i;
    char **arr = _malloc(rows * sizeof(char *));
    for (i = 0; i < rows; i++)
    {
        arr[i] = _malloc(cols * sizeof(char));
    }
    return arr;
}

// Hashes a string (e.g. A --> 0, E --> 5, etc.)
void hash_str(char *s, int *hash)
{
    memset(hash, 0, ALPHABET_SIZE * sizeof(int));
    for (int i = 0; s[i] != '\0'; i++)
    {
        hash[HASH_LOWER_CHAR(s[i])]++;
    }
}

// Does string exist in array?
bool str_in_array(const char **arr, int size, char *target)
{
    for (int i = 0; i < size; i++)
    {
        if (str_equals(arr[i], target)) return true;
    }
    return false;
}

// Gets the index of the first occurence in a string
int find_in_str(const char *s, char target)
{
    return get_x_occurence(s, target, 1);
}

// Converts a string to an int, stops at a terminator
int str_to_int(char *s, char end)
{
    char temp[MAX_DIGITS + 1];
    int i;
    for (i = 0; i < MAX_DIGITS && s[i] != end && s[i] != '\0'; i++)
    {
        temp[i] = s[i];
    }
    temp[i] = '\0';
    //printf("%d\n", atoi(temp));
    return atoi(temp);
}

// Converts a string to a large int, stops at a terminator
long long int str_to_ll(char *s, char end)
{
    char temp[MAX_DIGITS_LL + 1];
    int i;
    for (i = 0; i < MAX_DIGITS_LL && s[i] != end && s[i] != '\0'; i++)
    {
        temp[i] = s[i];
    }
    temp[i] = '\0';
    //printf("%d\n", atoll(temp));
    return atoll(temp);
}

// Gets the length of a string
int str_length(char *s)
{
    int c = 0;
    while (s[c] != '\0') c++;
    return c;
}

// Splits a string to an array of ints given a delimiter
int split_to_int(int *arr, int size, char *str, char delimiter)
{
    int i;
    int *occurences = NULL;
    int count = get_occurences(str, delimiter, &occurences, size);
    int c = 0;

    arr[c++] = str_to_int(str, delimiter);
    for (i = 0; i < count - 1; i++)
    {
        arr[c++] = str_to_int(str + occurences[i] + 1, delimiter);
    }
    arr[c++] = str_to_int(str + occurences[i] + 1, '\n');

    return c;
}

// Splits a string to an array of ints given a delimiter when the number of separate values is unknown
int split_to_int_unknown_size(int **arr, char *str, char delimiter)
{
    int size = count_occurences(str, delimiter);
    *arr = _malloc((size + 1) * sizeof(int));
    return split_to_int(*arr, size, str, delimiter);
}

// Splits a string to an array of large ints given a delimiter
int split_to_ll(long long int *arr, int size, char *str, char delimiter)
{
    int i;
    int *occurences = NULL;
    int count = get_occurences(str, delimiter, &occurences, size);
    int c = 0;

    arr[c++] = str_to_ll(str, delimiter);
    for (i = 0; i < count - 1; i++)
    {
        arr[c++] = str_to_ll(str + occurences[i] + 1, delimiter);
    }
    arr[c++] = str_to_ll(str + occurences[i] + 1, '\n');
    return c;
}

// Splits a string to an array of large ints given a delimiter when the number of separate values is unknown
int split_to_ll_unknown_size(long long int **arr, char *str, char delimiter)
{
    int size = count_occurences(str, delimiter);
    *arr = _malloc((size + 1) * sizeof(long long int));
    return split_to_ll(*arr, size, str, delimiter);
}

// Shifts all characters in a string from a starting index to the left
void shift_left(char *s, int index)
{
    for (int i = index; s[i] != '\0'; i++)
    {
        s[i] = s[i + 1];
    }
}

// Removes duplicate delimiters next to each other in a string
void remove_extra_delimiters(char *s, char delimiter)
{
    for(int i = 0; s[i] != '\0'; i++)
    {
        if (s[i] == delimiter && s[i + 1] == delimiter)
        {
            shift_left(s, i + 1);
            i--;
        }
    }
}

// Removes all occurences of a character in a string
void remove_char(char *s, char target)
{
    for(int i = 0; s[i] != '\0'; i++)
    {
        if (s[i] == target)
        {
            shift_left(s, i);
            i--;
        }
    }
}

// Removes unwanted characters when copy/pasting from a text file
void clean_input(char *s)
{
    remove_char(s, '\n');
    remove_char(s, CR);
}

// Gets the greatest common denominator of two values
long long int gcd(long long int a, long long int b)
{
    if (b == 0)
    {
        return a;
    }

    return gcd(b, a % b);
}

// Gets the least common multiple of two values
long long int lcm(long long int a, long long int b)
{
    return (a / gcd(a, b)) * b;
}

// Prints the amount of time between two time stamps
void print_time(clock_t start, clock_t end)
{
    double total_time = end - start;
    int ms = (int)(total_time);
    int sec = ms / 1000;
    ms = ms % 1000;
    int min = sec / 60;
    sec = sec % 60;
    printf("Total runtime: %dm %ds %dms\n", min, sec, ms);
}

// Outputs an int array
void print_int_arr(int *arr, int size)
{
    int i;
    for (i = 0; i < size - 1; i++)
    {
        printf("%d, ", arr[i]);
    }
    printf("%d\n", arr[i]);
}

// Outputs a large int array
void print_ll_arr(long long int *arr, int size)
{
    int i;
    for (i = 0; i < size - 1; i++)
    {
        printf("%lld, ", arr[i]);
    }
    printf("%lld\n", arr[i]);
}

// Outputs a string array
void print_2d_char_arr(char **arr, int rows, int cols)
{
    int i, j;
    for (i = 0; i < rows; i++)
    {
        for (j = 0; j < cols; j++)
        {
            printf("%c", arr[i][j]);
        }
        printf("\n");
    }
}

// Merges two int arrays, utility for sorting algorithm
void merge(int *arr, int l, int m, int r)
{
    int i, j, k;
    int n1 = m - l + 1;
    int n2 = r - m;
    int *L, *R;

    L = _malloc(n1 * sizeof(int));
    R = _malloc(n2 * sizeof(int));

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
        if (L[i] <= R[j])
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
}

//Sorts two int arrays
void merge_sort(int *arr, int l, int r)
{
    if (l < r)
    {
        int m = l + (r - l) / 2;

        merge_sort(arr, l, m);
        merge_sort(arr, m + 1, r);

        merge(arr, l, m, r);
    }
}

// Gets the distance between two points in a grid-like path
int manhattan_dist(int x, int y)
{
    return ABS(x) + ABS(y);
}

// Converts degrees to radians
double degree_to_radians(double d)
{
    return (d * (PI / 180));
}

// TODO
long long int mul_inv(long long int a, long long int b)
{
    int t, q;
    int b0 = b;
    int x0 = 0;
    int x1 = 1;
    if (b == 1)
    {
        return 1;
    }
    
    while (a > 1)
    {
        q = a / b;
        t = b;
        b = a % b;
        a = t;
        t = x0;
        x0 = x1 - q * x0;
        x1 = t;
    }
    if (x1 < 0)
    {
        x1 += b0;
    }
    
    return x1;
}

// TODO
long long int chinese_remainder(int *n, int *a, int len)
{
    int p, i;
    long long int prod = 1;
    long long int sum = 0;

    for (i = 0; i < len; i++)
    {
        prod *= n[i];
    }
    for (i = 0; i < len; i++)
    {
        p = prod / n[i];
        sum += a[i] * mul_inv(p, n[i]) * p;
    }

    return sum % prod;
}

// Prints answers for sweet stars
void print_results(char *msg, int res)
{
    printf("%s: %d", msg, res);
}

// Prints answers for sweet stars
void print_results_ll(char *msg, long long int res)
{
    printf("%s: %lld", msg, res);
}
