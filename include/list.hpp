#ifndef LIST_HPP_INCLUDED
#define LIST_HPP_INCLUDED
#include "utils.hpp"

void list_ctor    (list *lst, int capacity);
void list_dtor    (list *lst);

void list_realloc (list *lst);
void list_sort    (list *lst);

void        list_insert   (list *lst, int ind, elem_data_t value); 
elem_data_t list_erase    (list *lst, int ind);

int         pop_free         (list *lst);
void        push_free        (list *lst, int ind);

void        list_push_back   (list *lst, elem_data_t value);
void        list_push_front  (list *lst, elem_data_t value);
elem_data_t list_pop_back    (list *lst);
elem_data_t list_pop_front   (list *lst);

#endif