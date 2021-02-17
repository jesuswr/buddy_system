#ifndef _MULTILAYER_PERCEPTRON_HPP
#define _MULTILAYER_PERCEPTRON_HPP

#include <vector>
#include <set>

using namespace std;


class buddy_system
{
    // vector of sets of ints, if i is in free_bucket[j]
    // that means that you have a block of size 2^j free
    // starting at i
    vector< set<int> > free_bucket;

    // same as free_bucket but with reserved blocks
    vector< set<int> > reserved_bucket;

    // vector of booleans, if is_free[i] is true then position i
    // its free, else its reseverd
    vector< bool > is_free;


public:
    buddy_system(int num_blocks);
    ~buddy_system();
};



#endif