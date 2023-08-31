#include <iostream>
#include <vector>
#include <functional>
#include <string>

using namespace std;

class CountMinSketch {
private:
    unsigned int nrow;
    uint64_t ncol;
public:
    CountMinSketch(unsigned int heigth, uint64_t width) {
        this->nrow = heigth;
        this->ncol = width;
        size_t table[nrow][ncol] = {0};
        vector<hash<string>>(this->nrow) v_hash;
    }
    ~CountMinSketch() {}
    void add(string item) {
        for(int i=0; i < nrow; i++) {
            index = v_hash[i](item);
            table[i][index] != 0 ? table[i][index]++ : table[i][index]=1;
        }
    }
    size_t query(string item) {
        size_t res[nrow] = {0};
        for(int i=0; i < nrow; i++) {
            index = v_hash[i](item);
            res[i] = table[i][index];
        }
        size_t minValue = *max_element(res, res+nrow);
        return minValue;
    }

};

int main(int argc, char* argv[]) {
    unsigned int nrow = atof(argv[1]);
    unsigned long length = atof(argv[2]);
    int table[];
    int table[nrow*length] = {0};
    table[1] = 42;
    cout << "table[1] = " << table[1] << endl;
  
    return 0;
}
