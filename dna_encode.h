#include <stdio.h>
#include <string.h>
#include <stdint.h>

int8_t base_to_bin(char base) {
    switch (base) {
    case 'A': 
        return 0;
    case 'T': 
        return 1;
    case 'C': 
        return 2;
    case 'G': 
        return 3;
    }
}

uint32_t seq_to_bin(char* seq) {
    uint32_t binary_kmer = 0;
    int n = strlen(seq);
    for(int i = 0; i < n; i++) {
        int8_t val = base_to_bin(*(seq + i));
        binary_kmer <<= 2;
        binary_kmer |= val;
    }
 
    return binary_kmer;
}
