#include "include/list.hpp"
#include "include/list_debug.hpp"


int main() {
    list lst = {};

    list_ctor(&lst, 10);
    dump(&lst);

    for (int i = 1; i < 5; i++) {
        list_insert(&lst, i, i*10);
        dump(&lst);
    }
    // printf("%d\n", list_erase(&lst, 2));

    // dump(&lst);

    // for (int i = 0; i < 4; i++) {
    //     printf("%d\n", list_erase(&lst, ));

    // // } 
    // printf("%d\n", list_erase(&lst, 2));
    // dump(&lst);
    // printf("%d\n", list_erase(&lst, lst.tail - 1));
    // dump(&lst);
    // printf("%d\n", list_erase(&lst, lst.tail - 1));
    // dump(&lst);

    list_insert(&lst, 3, 35);
    dump(&lst);
    list_insert(&lst, lst.tail, 50);
    dump(&lst);
    list_insert(&lst, 2, 25);
    list_insert(&lst, 1, 15);
    dump(&lst);
    list_insert(&lst, 3, 33);
    dump(&lst);


    list_dtor(&lst);
    return 0;
}