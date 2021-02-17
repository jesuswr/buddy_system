#include <iostream>
#include "buddy_system.hpp"

int main(int argc, char **argv) {
    if (argc == 1) {
        printf("No se especifico la cantidad de bloques.\n");
        return -1;
    }
    int num_blocks = atoi(argv[1]);
    if (num_blocks <= 0) {
        printf("El numero ingresado no es valido.\n");
        return -1;
    }

    buddy_system my_buddy(num_blocks);


    return 0;
}