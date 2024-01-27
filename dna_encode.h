#ifndef ENCODE_H
#define ENCODE_H
#define DEFAULT -1

static int *base_map_init(int * map) {
    memset(map, DEFAULT, 128*sizeof(int));
    map['A'] = 0;
    map['C'] = 1;
    map['G'] = 2;
    map['T'] = 3;
}

#endif
