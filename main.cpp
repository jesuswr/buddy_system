#include <iostream>
#include "buddy_system.hpp"

int main(int argc, char **argv) {
    if (argc == 1) {
        printf("NO SE ESPECIFICO LA CANTIDAD DE BLOQUES\n");
        return -1;
    }
    int num_blocks = atoi(argv[1]);
    if (num_blocks <= 0) {
        printf("EL NUMERO INGRESADO NO ES VALIDO\n");
        return -1;
    }

    buddy_system my_buddy(num_blocks);
    while (true) {
        printf("QUE DESEA HACER?\n");
        string s;
        cin >> s;
        if (s.compare("RESERVAR") == 0) {
            string id; int size;
            cin >> id >> size;
            int err = my_buddy.reserve(id, size);
            if (err < 0) my_buddy.print_error(err);
        }
        else if (s.compare("LIBERAR") == 0) {
            string id;
            cin >> id;
            int err = my_buddy.free(id);
            if (err < 0) my_buddy.print_error(err);
        }
        else if (s.compare("MOSTRAR") == 0) {
            my_buddy.show();
        }
        else if (s.compare("SALIR") == 0) {
            break;
        }
        else{
            printf("COMANDO NO CONOCIDO\n");
        }
    }
    return 0;
}