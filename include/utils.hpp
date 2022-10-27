#ifndef UTILS_HPP_INCLUDED
#define UTILS_HPP_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#define MULTIPLY 2


typedef int elem_data_t;


typedef struct {
    elem_data_t elem;
    int next, prev;
} arr_list;

typedef struct {
    int head, tail, free;
    arr_list *data;
    size_t size, capacity;
    bool is_sorted;
} list;

#endif 