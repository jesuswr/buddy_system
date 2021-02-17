#ifndef _MULTILAYER_PERCEPTRON_HPP
#define _MULTILAYER_PERCEPTRON_HPP

#include <vector>
#include <iostream>
#include <set>
#include <string>
#include <map>

using namespace std;


class buddy_system
{
    // maximum possible power of two
    int mx_pow;
    // vector of sets of ints, if i is in free_bucket[j]
    // that means that you have a block of size 2^j free
    // starting at i
    vector< set<int> > free_bucket;

    // vector of booleans, if is_free[i] is true then position i
    // its free, else its reseverd
    vector< bool > is_free;

    // here we save the starting position and size of the block
    // reserved for each id
    map< string, pair<int, int> > reserved_ids;


public:
    buddy_system(int num_blocks);
    ~buddy_system();
    int reserve(string id, int size);
    int free(string id);
    void show();
    void print_error(int code);
};



#endif