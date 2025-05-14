#include <stdio.h>
#include <string.h>
#include <malloc.h>
#include <stdlib.h>
#include <limits.h>
#include <unistd.h>
#include <stdbool.h>
#include <math.h>

#define MAX 100

#define d 256
#define q 181
long long calculateHash(char *text, int m)
{
    long long hash = 0;
    for (int i = 0; i < m; i++)
    {
        hash = (d * hash + text[i]) % q;
    }

    return hash;
}
int rabinKarp(char *pattern, char *text, int n, int m)
{
    long long pattern_hash = calculateHash(pattern, m);
    long long text_hash = calculateHash(text, m);
    long long hash = (long long)pow(256, m - 1) % q;
    for (int i = 0; i <= n - m; i++)
    {
        if (text_hash == pattern_hash)
        {
            if (strncmp(pattern, text + i, m) == 0)
            {
                printf("pattern found at index %d\n", i);
            }
        }
        if (i < n - m)
        {
            text_hash = (d * (text_hash - text[i] * hash) + text[i + m]) % q;
            if (text_hash < 0)
                text_hash += q;
        }
    }
}

int main()
{
    char text[] = "ABCCDDAEFG";
    char pattern[] = "CDD";

    rabinKarp(pattern, text, strlen(text), strlen(pattern));
    return 0;
}
