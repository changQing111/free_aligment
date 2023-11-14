#include <stdio.h>
#include <string.h>
#include <stdint.h>

int base_map[128] = {[0 ... 127] = -1};
base_map['A'] = 0;
base_map['C'] = 1;
base_map['G'] = 2;
base_map['T'] = 3;

int seq_to_num(char* seq, int* BaseMap) {
    int length = strlen(seq);
    int num = 0;
    for(int i = 0; i < length; i++) {
        int left_move = 2*(length-1-i);
        num |= (BaseMap[seq[i]] << left_move);
    }
    return num;
}
