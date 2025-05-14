// 13) String Matching Algorithm: Rabin-Karp
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

#define d 256 // Number of characters in the input alphabet (ASCII characters)
#define q 101 // A prime number for the modulus operation (used for hashing)

// Function to perform Rabin-Karp string matching
void rabinKarp(char *txt, char *pat) {
    int m = strlen(pat);  // Length of the pattern
    int n = strlen(txt);  // Length of the text
    int i, j;
    int p = 0;  // Hash value for pattern
    int t = 0;  // Hash value for text
    int h = 1;

    // The value of h would be "pow(d, m-1)%q"
    for (i = 0; i < m - 1; i++) {
        h = (h * d) % q;
    }

    // Compute the hash value of the pattern and the first window of text
    for (i = 0; i < m; i++) {
        p = (d * p + pat[i]) % q;
        t = (d * t + txt[i]) % q;
    }

    // Slide the pattern over the text one by one
    for (i = 0; i <= n - m; i++) {
        // If the hash values match, then check the characters one by one
        if (p == t) {
            for (j = 0; j < m; j++) {
                if (txt[i + j] != pat[j]) {
                    break;
                }
            }
            if (j == m) {
                printf("Pattern found at index %d\n", i);
            }
        }

        // Compute hash value for the next window of text
        if (i < n - m) {
            t = (d * (t - txt[i] * h) + txt[i + m]) % q;
            if (t < 0) {
                t = (t + q);
            }
        }
    }
}

int main() {
    char txt[100], pat[100];

    printf("Enter the text: ");
    // Using fgets to properly read the text with spaces
    fgets(txt, sizeof(txt), stdin);
    // Remove newline character if any
    txt[strcspn(txt, "\n")] = '\0';

    printf("Enter the pattern: ");
    // Using fgets to properly read the pattern with spaces
    fgets(pat, sizeof(pat), stdin);
    // Remove newline character if any
    pat[strcspn(pat, "\n")] = '\0';

    clock_t start = clock();
    rabinKarp(txt, pat);
    clock_t end = clock();

    double time_taken = ((double)(end - start)) / CLOCKS_PER_SEC;
    printf("\nTime taken: %f seconds\n", time_taken);

    return 0;
}
