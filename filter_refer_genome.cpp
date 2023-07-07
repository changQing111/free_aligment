#include <iostream>
#include <fstream>
#include <functional>
#include <bitset>
#include <vector>
#include <unordered_map>
#include <string>
#include <algorithm>
//#include <nthash/nthash.hpp>
#include <city.h>
//#include  <zlib.h>

#define KMER 21
using namespace std;

class BloomFilter {
private:
    uint64_t capacity;
    vector<bool> v_bool;
    int kmer_size;
    int hash_num;
    float error_ratio = 0.0;
public:
    BloomFilter(uint64_t capacity, int k, int n, float error_ratio=0.0) {
        this->capacity = capacity;
        this->v_bool = vector<bool>(this->capacity, false);
        this->kmer_size = k;
        this->hash_num = n;
        this->error_ratio = error_ratio;
    }
    ~BloomFilter() {}
    size_t get_size(void) {
        return this->v_bool.size();
    }
    void add(string item) {
        const char* kmer = item.c_str();
        uint32_t hash32 = CityHash32(kmer, kmer_size);
        this->v_bool[hash32] = true;
    }
    bool query(string item) {
        const char* kmer = item.c_str();
        uint32_t hash32 = CityHash32(kmer, 21);
        if(!v_bool[hash32]) {
            return false;
        }
        return true;
    }
    int save_refer_db(string filename) {
        ofstream out_file;
        out_file.open(filename, ios::out|ios::binary);
        if(!out_file) {
            cerr << "Can not create file!" << endl;
            return -1;
        }
        char data = 0;
        int count = 1;
        for(int i = 0; i < v_bool.size(); i++) {
            cout << v_bool[i] << endl;
            data |= (v_bool[i] << 8 - count);
            count++;
            if(count > 8) {
                out_file.write(&data, sizeof(char));
                data = 0;
                count = 1;
            }
        }
        out_file.close();
        return 0;
    }
    int load_refer_db(string filename) {
        ifstream fin;
        fin.open(filename, ios::binary | ios::in);
        char ch;
        //int count = 0;
        int n = 0;
        while(fin.get(ch)) {
            for(int i = 1; i < 8; i++) {
                v_bool[n] = ch >> 7 ? true : false;
                cout << v_bool[n] << endl;
            }
            n++;
        }
        return 0;
    }
    
    void add(string item) {
        cout << "begin" << endl;
        nthash::NtHash nth(item, hash_num, kmer_size);
        while (nth.roll()) {
           for (unsigned i = 0; i < nth.get_hash_num(); i++) {
                size_t index = nth.hashes()[i];
                v_bool[index] = true;
           }
        }
        cout << "end" << endl;
    }
    bool query(string item) {
        nthash::NtHash nth(item, hash_num, kmer_size);
        while (nth.roll()) {
           for (unsigned i = 0; i < nth.get_hash_num(); i++) {
                size_t index = nth.hashes()[i];
                if(!v_bool[index]) {
                    return false;
                }
           }
        }
        return true;
    }
};

 void put_kmer_bf(string& seq, BloomFilter &BF, int k=KMER) {
    int len = seq.length();
    int num = len - k + 1;
    for(int i = 0; i < len; i++) {
        string kmer = seq.substr(i, k);
        BF.add(kmer);
    }
}

void toUpper(string& Seq) {
    transform(Seq.begin(), Seq.end(), Seq.begin(), ::toupper);
}
string recvComp(string& Seq, unordered_map<char, char>& baseMap) {
    reverse(Seq.begin(), Seq.end());
    string comp_seq;
    for(int i=0; i<Seq.size(); i++) {
        comp_seq += baseMap[Seq[i]];
    }
    return comp_seq;
}

int main() {
    BloomFilter bf(1ULL << 32, 21, 1, 0.01);
    unsigned long long size = bf.get_size();
    cout << "size = " << size << endl;
    unordered_map<char, char> base_map = {{'A','T'}, {'T', 'A'}, {'C','G'}, {'G','C'}, {'N','N'}};
    string file_name = "GCF_014570535.1_YNU_ManJav_2.0_genomic.fna";
    string buffer;
    ifstream fin;
    fin.open(file_name);
    int n = 0;
    string seq = "";
    while(getline(fin, buffer)) {
        if(buffer[0] == '>'){
            n++;
            if(n > 1) {
                toUpper(seq);
                put_kmer_bf(seq, bf);
                string recvSeq = recvComp(seq, base_map);
                put_kmer_bf(recvSeq, bf);
                seq = "";
            }
        }
        else {
            seq += buffer;
        }
    }
    toUpper(seq);
    put_kmer_bf(seq, bf);
    string recvSeq = recvComp(seq, base_map);
    put_kmer_bf(recvSeq, bf);
    fin.close();
    bf.save_refer_db("refer_genome.bf");

    //const char* seq1 = seq.c_str();
    //uint32_t hash32 = CityHash32(seq1, 21);
    //cout << "hash32 = " << hash32 << endl;
    return 0;
}
