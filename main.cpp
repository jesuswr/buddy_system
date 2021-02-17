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
    while (true) {
        printf("Que desea hacer?\n");
        string s;
        cin >> s;
        if (s.compare("RESERVAR") == 0) {
            string id; int size;
            cin >> id >> size;
            printf("%d\n", my_buddy.reserve(id, size));
        }
        else if (s.compare("LIBERAR") == 0) {
            string id;
            cin >> id;
            printf("%d\n", my_buddy.free(id));
        }
    }

    return 0;
}