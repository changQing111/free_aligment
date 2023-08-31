#include "dna_encode.h"
#include <iostream>
#include <unordered_map>
#define SIZE (1<<20)
using namespace std;

void get_minimizer(char* seq, int n , int k, int w, unordered_map<uint32_t, uint32_t>& count_map) {
    uint32_t kmer_array[SIZE];
    memset(kmer_array, 0, sizeof(kmer_array));
    char kmer[k];
    for(int i = 0; i < n-k+1; i++) {
        strncpy(kmer, seq + i, k);
        uint32_t bin = seq_to_bin(kmer, k);
        uint32_t hash_val = bin & (SIZE - 1); // take the last 20 bits as hash value
        kmer_array[i] = hash_val;
    }
    uint32_t mini_size = n-k-w+2;
    for(int i = 0; i < mini_size; i++) {
        uint32_t minimizer = kmer_array[i];
        for(int j = 1; j < w; j++) {
            uint32_t cand_minimizer  = kmer_array[i+j];
            if(cand_minimizer < minimizer) {
                minimizer = cand_minimizer;
            }
        }
        if (count_map.find(minimizer) == count_map.end()) {
            count_map[minimizer] = 1;
        } else {
            count_map[minimizer]++;
        }
    }

}

int main(int argc,char* argv[]) {
    int base_map[128];
    base_map['A'] = 0;
    base_map['C'] = 1;
    base_map['G'] = 2;
    base_map['T'] = 3;
    char* seq = argv[1];
    int n = strlen(seq);
    int k = 5;
    int w = 3;
    unordered_map<uint32_t, uint32_t> minimizer_map;
    get_minimizer(seq, n, k, w, minimizer_map);
    for (auto it = minimizer_map.begin(); it != minimizer_map.end(); it++) {
        cout << it->first << " : " << it->second << endl;
    }
}
