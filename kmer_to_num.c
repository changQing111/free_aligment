#include <stdio.h>
#include <string.h>
#include "dna_encode.h"
#define KMER 6

int* kmer_to_num(char* seq, int length, int* num_array, int* base_map, int* recv_comp) {
    unsigned int set_zore = 0b01;
    for(int i = 0; i < 2*(KMER-1)-1; i++)  {
        set_zore = (set_zore << 1) | 0b01;
    }
    unsigned left_set_zore = set_zore;
    //printf("left=%u\n", left_set_zore);
    unsigned right_set_zore = set_zore << 2;
    //printf("right=%u\n", right_set_zore);

    unsigned int num = 0; 
    unsigned int recv_comp_num = 0;
    for(int i = 0; i < KMER; i++) {
        //int left_move = 2*(KMER-1-i);
        //num |= (base_map[seq[i]] << left_move);
        num = (num << 2)|base_map[seq[i]];
        //recv_comp_num = (recv_comp_num >> 2) | (recv_comp[seq[i]] >> (KMER+1));
    }
    //printf("first kmer:%d\n", num);
    recv_comp_num = recv_comp[seq[0]];
    for(int i = 1; i < KMER; i++) {
        recv_comp_num |= (recv_comp[seq[i]] << (2*i));
    }
    //printf("first recv_comp kmer:%d\n", recv_comp_num);
    
    num_array[0] = (num < recv_comp_num) ? num : recv_comp_num;

    for(int j = KMER; j < length; j++) {
        num = ((num & left_set_zore) << 2) | base_map[seq[j]];
        recv_comp_num = ((recv_comp_num & right_set_zore) >> 2) | (recv_comp[seq[j]] << (2*KMER-2));
        //printf("normal kmer=%d\n", num);
        //printf("recv kmer=%d\n", recv_comp_num);
        num_array[j-KMER+1] = (num < recv_comp_num) ? num : recv_comp_num;
    }

    return num_array;
}

int main() {
    base_map_init(base_map);
    recv_comp_init(recv_comp);

    char* seq = "CTAGCTGCTAATGTCTAGCTCGTA";
    int len = strlen(seq);
    int kmer_num = len - KMER + 1;
    int num_arr[kmer_num];
    int* res = kmer_to_num(seq, len, num_arr, base_map, recv_comp);

    for(int i = 0; i < kmer_num; i++) {
        printf("%d\n", res[i]);
    }

    return 0;
}
