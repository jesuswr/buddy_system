#include "buddy_system.hpp"

using namespace std;


buddy_system::buddy_system(int num_blocks) {
    if (num_blocks <= 0) return;

    // initialization of buddy_system attributes
    for (int bit = 0; bit < 32; ++bit)
        if (num_blocks & (1 << bit)) mx_pow = bit;
    free_bucket.resize(mx_pow + 1);
    reserved_bucket.resize(mx_pow + 1);
    is_free.resize(num_blocks, true);

    // save free blocks in the according bucket
    for (int bit = 31, ind = 0; bit >= 0; --bit) {
        if (num_blocks & (1 << bit)) {
            free_bucket[bit].insert(ind);
            printf("bloque de tamano %d empezando en %d\n", 1 << bit, ind );
            ind += (1 << bit);
        }
    }
    printf("\n");
}

buddy_system::~buddy_system() {
    free_bucket.clear();
    reserved_bucket.clear();
    is_free.clear();
    return;
}


int buddy_system::reserve(string id, int size) {
    if (reserved_ids.find(id) != reserved_ids.end()) return -1;
    if (size <= 0) return -2;
    int pow = 0;
    while ((1 << pow) < size) ++pow;
    while (free_bucket[pow].empty() && pow <= mx_pow) ++pow;
    if (pow > mx_pow) return -3;

    int ind = *free_bucket[pow].begin();
    free_bucket[pow].erase(ind);
    while ((1 << (pow - 1)) >= size) {
        --pow;
        free_bucket[pow].insert(ind + (1 << pow));
    }
    reserved_bucket[pow].insert(ind);
    reserved_ids[id] = {ind, pow};
    for (int i = ind; i < ind + (1 << pow); ++i) is_free[i] = false;
    return 0;
}

int buddy_system::free(string id) {
    if (reserved_ids.find(id) == reserved_ids.end()) return -1;

    int ind, pow;
    tie(ind, pow) = reserved_ids[id];

    reserved_ids.erase(id);
    reserved_bucket[pow].erase(ind);
    for (int i = ind; i < ind + (1 << pow); ++i) is_free[i] = true;
    free_bucket[pow].insert(ind);

    bool try_merge = true;
    while (try_merge) {
        try_merge = false;
        if (free_bucket[pow].count(ind - (1 << pow)) > 0) {
            free_bucket[pow].erase(ind);
            free_bucket[pow].erase(ind - (1 << pow));
            ++pow;
            free_bucket[pow].insert(ind - (1 << pow));
            try_merge = true;
        }
        else if (free_bucket[pow].count(ind + (1 << pow)) > 0) {
            free_bucket[pow].erase(ind);
            free_bucket[pow].erase(ind + (1 << pow));
            ++pow;
            free_bucket[pow].insert(ind);
            try_merge = true;
        }
    }
    return 0;
}