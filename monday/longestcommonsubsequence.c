// A Naive recursive implementation of LCS problem
#include <stdio.h>
#include <string.h>

int max(int x, int y) {
  	return x > y ? x : y; 
}

// Returns length of LCS for s1[0..m-1], s2[0..n-1]
int lcsRec(char s1[], char s2[], int m, int n) {

    // Base case: If either string is empty, the length of LCS is 0
    if (m == 0 || n == 0)
        return 0;

    // If the last characters of both substrings match
    if (s1[m - 1] == s2[n - 1])

        // Include this character in LCS and recur for remaining substrings
        return 1 + lcsRec(s1, s2, m - 1, n - 1);

    else
        // If the last characters do not match
        // Recur for two cases:
        // 1. Exclude the last character of S1 
        // 2. Exclude the last character of S2 
        // Take the maximum of these two recursive calls
        return max(lcsRec(s1, s2, m, n - 1), lcsRec(s1, s2, m - 1, n));
}
int lcs(char s1[],char s2[]){
    int m = strlen(s1);
    int n = strlen(s2);
    
    return lcsRec(s1,s2,m,n);
}

int main() {
    char s1[] = "AGGTAB";
    char s2[] = "GXTXAYB";
    printf("%d\n", lcs(s1, s2));
    return 0;
}


















// 1) Input:
// - Two strings s1 and s2 of lengths m and n respectively

// 2) Algorithm:
// Naive recursive approach:
// - Compare last characters of both strings
// - If match: add 1 and recurse on both shorter substrings
// - If not: recurse on two subproblems (exclude one end at a time)
// - Take maximum result

// 3) Time Complexity:
// Worst Case: O(2^(m+n)), due to overlapping subproblems
// Each call branches into 2 recursive calls in worst case

// 4) Space Complexity:
// - O(m + n), due to recursion stack depth

// 5) Advantages / Disadvantages:
// + Simple and intuitive
// + No extra memory except recursion stack
// - Very slow for large strings due to exponential time
// - Repeats many computations (no memoization)

// 6) Recurrence Relation:
// lcs(m, n) = 
//   if s1[m-1] == s2[n-1]: 1 + lcs(m-1, n-1)
//   else: max(lcs(m-1, n), lcs(m, n-1))
// Base case: lcs(0, n) = lcs(m, 0) = 0

// 7) Summary (2 lines):
// Solves LCS problem using pure recursive approach.
// Correct but inefficient — avoid for long strings due to exponential runtime.