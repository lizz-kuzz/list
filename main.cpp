#include "include/list.hpp"
#include "include/list_debug.hpp"


int main() {
    list lst = {};

    list_ctor(&lst, 10);
    dump(&lst);
    for (int i = 0; i < 15; i++) {
        list_push_back(&lst, (i+1)*10);
        dump(&lst);
    }

    // for (int i = 0; i < 10; i++) {
    //     list_insert(&lst, i, (i+1)*10);
    //     dump(&lst);
    // }

    
    // printf("%d\n", list_erase(&lst, 2));

    // dump(&lst);

   
    for (int i = 0; i < 10; i++) {
    printf("%d\n", list_pop_back(&lst));
    dump(&lst);

    }
    // printf("%d\n", list_erase(&lst, lst.size));
    // dump(&lst);
    // printf("%d\n", list_erase(&lst, lst.size));
    // dump(&lst);
    // printf("%d\n", list_erase(&lst, 3));
    // dump(&lst);
    // printf("%d\n", list_erase(&lst, 5));
    // dump(&lst);

    // list_insert(&lst, 3, 35);
    // dump(&lst);
    // // list_insert(&lst, lst.tail, 50);
    // // dump(&lst);
    // list_insert(&lst, 2, 25);
    // dump(&lst);
    // list_insert(&lst, 1, 15);
    // dump(&lst);
    // printf("%d\n", list_get_item_by_logical_ind(&lst, 6));


    list_sort(&lst);
    dump(&lst);
    // // list_insert(&lst, 3, 33);


    list_dtor(&lst);
    return 0;
}