#ifndef LIST_HPP_INCLUDED
#define LIST_HPP_INCLUDED
#include "utils.hpp" 

void list_ctor(list *lst, int size);

void list_dtor(list *lst);

void dump(list *lst);

void list_insert(list *lst, int id, elem_data_t value);

// realloc
// pop элемента по индексу
// сортировка
// закольцевать список


#endif