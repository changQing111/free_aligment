#include <stdio.h>
#include <string.h>

int base_map[128] = {[0 ... 127] = -1};
base_map['A'] = 0;
base_map['C'] = 1;
base_map['G'] = 2;
base_map['T'] = 3;
