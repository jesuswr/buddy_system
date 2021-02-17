#include "buddy_system.hpp"

using namespace std;


/*
    Constructor:
    Initializes the buddy system structure to manage memory

    Param:
        num_blocks: int representing the total memory size to manage
*/
buddy_system::buddy_system(int num_blocks) {
    if (num_blocks <= 0) return;

    // initialization of buddy_system attributes
    for (int bit = 0; bit < 32; ++bit)
        if (num_blocks & (1 << bit)) mx_pow = bit;
    free_bucket.resize(mx_pow + 1);
    is_free.resize(num_blocks, true);

    // save free blocks in the according bucket
    for (int bit = 31, ind = 0; bit >= 0; --bit) {
        if (num_blocks & (1 << bit)) {
            free_bucket[bit].insert(ind);
            ind += (1 << bit);
        }
    }
}

/*
    Destructor:
    Clears the data used by the buddy system
*/
buddy_system::~buddy_system() {
    free_bucket.clear();
    is_free.clear();
    return;
}

/*
    reserve:
    function to assign a block of memory to a given id

    Param:
        id: string to assign the block of memory to
        size: int that represents the size of the block

    Return:
        0 in case of success
        negative number in case of error
*/
int buddy_system::reserve(string id, int size) {
    // error if the id is being used already
    if (reserved_ids.find(id) != reserved_ids.end()) return -1;
    // error if the size is not positive
    if (size <= 0) return -2;

    // look for the smallest block size available that can cover 
    // the asked size
    int pow = 0;
    while ((1 << pow) < size) ++pow;
    while (pow <= mx_pow && free_bucket[pow].empty()) ++pow;
    // error if there is no memory block to give
    if (pow > mx_pow) return -3;

    // starting position of the block
    int ind = *free_bucket[pow].begin();
    free_bucket[pow].erase(ind);

    // while the chosen block is too big, split it in smaller blocks
    while ((1 << (pow - 1)) >= size) {
        --pow;
        free_bucket[pow].insert(ind + (1 << pow));
    }

    reserved_ids[id] = {ind, pow};
    for (int i = ind; i < ind + (1 << pow); ++i) is_free[i] = false;
    return 0;
}

/*
    free:
    function to free a block of memory assigned to an id

    Param:
        id: string that has the block of memory assigned to

    Return:
        0 in case of success
        negative number in case of error
*/
int buddy_system::free(string id) {
    // error if the given id doesnt exist
    if (reserved_ids.find(id) == reserved_ids.end()) return -4;

    // get position and size of block
    int ind, pow;
    tie(ind, pow) = reserved_ids[id];

    // free the block
    reserved_ids.erase(id);
    for (int i = ind; i < ind + (1 << pow); ++i) is_free[i] = true;
    free_bucket[pow].insert(ind);

    // while there are adjacent blocks of the same size, merge them
    bool try_merge = true;
    while (try_merge && pow <= mx_pow) {
        try_merge = false;
        // try left
        if (free_bucket[pow].count(ind - (1 << pow)) > 0) {
            free_bucket[pow].erase(ind);
            free_bucket[pow].erase(ind - (1 << pow));
            free_bucket[pow + 1].insert(ind - (1 << pow));
            ind = ind - (1 << pow);
            ++pow;
            try_merge = true;
        }
        // try right
        else if (free_bucket[pow].count(ind + (1 << pow)) > 0) {
            free_bucket[pow].erase(ind);
            free_bucket[pow].erase(ind + (1 << pow));
            free_bucket[pow + 1].insert(ind);
            ++pow;
            try_merge = true;
        }
    }
    return 0;
}

/*
    show:
    function to print the status of the memory
*/
void buddy_system::show() {
    printf("REPRESENTACION DE LA MEMORIA (1 ES LIBRE, 0 ES RESERVADO):\n");
    for (auto f : is_free) printf("%d ", (int)f);
    printf("\n\n");

    printf("BLOQUES RESERVADOS:\n");
    for (auto info : reserved_ids) {
        printf("\t%s : \n", info.first.data());
        printf("\t\tTAMANO : %d\n", (1 << info.second.second));
        printf("\t\tEMPIEZA EN : %d\n", info.second.first);
    }
    printf("\n");

    printf("BLOQUES LIBRES:\n");
    for (int i = 0; i <= mx_pow; ++i) {
        for (auto ind : free_bucket[i]) {
            printf("\tEMPEZANDO EN %d DE TAMANO %d\n", ind, (1 << i));
        }
    }
    printf("\n");
}

/*
    print_error:
    function to print the error of the given code

    Param:
        code: int that represents an error given by the buddy system
*/
void buddy_system::print_error(int code) {
    switch (code) {
        case -1:
            printf("YA EXISTE UN BLOQUE DE MEMORIA CON ESE ID\n");
            break;
        case -2:
            printf("NO SE PUEDE ASIGNAR UN NUMERO DE BLOQUES NO POSITIVOS\n");
            break;
        case -3:
            printf("NO HAY UN BLOQUE DEL TAMANO NECESARIO PARA ASIGNAR\n");
            break;
        case -4:
            printf("EL ID DADO NO EXISTE\n");
            break;
    }
}