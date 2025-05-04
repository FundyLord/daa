#include <iostream>
#include <fstream>
#include <vector>
#include <cstring>
#include <chrono>

#define PRIME 101
#define MAX_TEXT_SIZE 10000
#define RUNS 5

using namespace std;

// Function to calculate hash value
long long create_hash(const string &str, int len) {
    long long hash = 0;
    for (int i=0; i<len; i++) {
        hash=(hash*256+str[i])%PRIME;
    }
    return hash;
}

// Rolling hash function
long long recalculate_hash(const string &str, int old_index, int new_index, long long old_hash, int pattern_length) {
    long long hash_multiplier=1;
    for (int i=0; i<pattern_length-1; i++) {
        hash_multiplier=(hash_multiplier*256)%PRIME;
    }

    old_hash=(old_hash-str[old_index]*hash_multiplier)%PRIME;
    old_hash=(old_hash*256+str[new_index])%PRIME;

    if (old_hash<0) {
        old_hash+=PRIME;
    }
    return old_hash;
}

// Rabin-Karp Algorithm
int search(const string &text, const string &pattern) {
    int text_length=text.size();
    int pattern_length=pattern.size();

    long long pattern_hash=create_hash(pattern, pattern_length);
    long long text_hash=create_hash(text, pattern_length);

    for (int i=0; i<=text_length-pattern_length; i++) {
        if (pattern_hash==text_hash) {
            if (text.substr(i, pattern_length)==pattern) {
                return i;
            }
        }
        if (i<text_length-pattern_length) {
            text_hash=recalculate_hash(text,i,i+pattern_length,text_hash,pattern_length);
        }
    }
    return -1;
}

// Function to get high-resolution time
double get_time() {
    return chrono::duration<double, milli>(chrono::high_resolution_clock::now().time_since_epoch()).count();
}

void benchmark_search(const string &filename) {
    ifstream file(filename);
    ofstream result_output("results.csv");

    if (!file || !result_output) {
        cout << "Error opening file!" << endl;
        return;
    }

    vector<int> sizes = {1000, 2000, 3000, 4000, 5000, 6000, 7000, 8000, 9000, 10000};
    vector<int> pattern_lengths = {10, 20, 30, 40, 50, 60, 70, 80, 90, 100};
    string text;
    text.resize(MAX_TEXT_SIZE);

    result_output << "Pattern Size";
    for (int n : sizes) {
        result_output << ",Text Size " << n;
    }
    result_output << endl;

    for (int m : pattern_lengths) {
        result_output << m;
        for (int n : sizes) {
            if (m > n) {
                result_output << ",";
                continue;
            }
            
            file.seekg(0, ios::beg);
            file.read(&text[0], n);
            text[n] = '\0';

            int fixed_index = n / 2 - m / 2;
            string pattern = text.substr(fixed_index, m);

            double total_time = 0;
            for (int r = 0; r < RUNS; r++) {
                double start = get_time();
                search(text, pattern);
                double end = get_time();
                total_time += (end - start);
            }

            double avg_time = total_time / RUNS;
            result_output << "," << avg_time;
        }
        result_output << endl;
    }
    file.close();
    result_output.close();
}

int main() {
    benchmark_search("big.txt");
    cout << "Benchmark completed. Check results.csv for results." << endl;
    return 0;
}
