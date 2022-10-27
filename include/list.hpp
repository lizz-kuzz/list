#ifndef LIST_HPP_INCLUDED
#define LIST_HPP_INCLUDED
#include "utils.hpp"

void list_ctor    (list *lst, int size);

void list_dtor    (list *lst);

void list_realloc (list *lst);

void list_sort    (list *lst);

int list_insert   (list *lst, int ind, elem_data_t value); 

int list_erase    (list *lst, int ind);

#endif