#ifndef ENCODE_H
#define ENCODE_H
#define DEFAULT -1

int base_map[128];
void base_map_init(int * map) {
    memset(map, DEFAULT, 128*sizeof(int));
    map['A'] = 0; map['a'] = 0;
    map['C'] = 1; map['c'] = 1;
    map['G'] = 2; map['g'] = 2;
    map['T'] = 3; map['t'] = 3;
}

int recv_comp[128];
void recv_comp_init(int* map) {
        memset(map, DEFAULT, 128*sizeof(int));
        map['A'] = 3; map['a'] = 3;
        map['C'] = 2; map['c'] = 2;
        map['G'] = 1; map['g'] = 1;
        map['T'] = 0; map['t'] = 0;

}

#endif
