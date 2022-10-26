#ifndef LIST_HPP_INCLUDED
#define LIST_HPP_INCLUDED
#include "utils.hpp"


void list_ctor    (list *lst, int size);

void list_dtor    (list *lst);

void list_realloc (list *lst);

void dump         (list *lst);

int list_insert   (list *lst, int ind, elem_data_t value); //разобраться с первым элементом

int list_erase    (list *lst, int ind);
// realloc
// pop элемента по индексу
// сортировка
// закольцевать список


#endif