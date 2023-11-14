#include <stdio.h>
#include <string.h>
#include "dna_encode.h"
#define KMER 4

int* kmer_to_num(char* seq, int length, int* num_array, int* BaseMap) {
    int set_zore = 0;
    for(int i = 0; i < 2*KMER-2; i++)  {
        set_zore |= 1<<i;
    }
    int num = 0;
    for(int i = 0; i < KMER; i++) {
        int left_move = 2*(KMER-1-i);
        num |= (BaseMap[seq[i]] << left_move);
    }
    num_array[0] = num;
    for(int j = KMER; j < length; j++) {
        num = ((num & set_zore) << 2) | BaseMap[seq[j]];
        num_array[j-KMER+1] = num;
    }

    return num_array;
}

int main() {
    base_map_init(base_map);
    char* seq = "CTAGCTGCTAATGTCTAGCTCGTA";
    int len = strlen(seq);
    int kmer_num = len - KMER + 1;
    int num_arr[kmer_num];
    int* res = kmer_to_num(seq, len, num_arr, base_map);

    for(int i = 0; i < kmer_num; i++) {
        printf("%d\n", res[i]);
    }

    return 0;
}
