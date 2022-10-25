#include "utils.hpp" 
#include "list.hpp"

int main() {
    list lst = {};

    list_ctor(&lst, 10);
    dump(&lst);
    for (int i = 1; i < lst.capacity; i++) {
    list_insert(&lst, i, i*10);
    dump(&lst);

    }

    list_dtor(&lst);
    return 0;
}