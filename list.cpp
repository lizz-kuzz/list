#include "include/list.hpp"
#include "include/list_debug.hpp"

FILE *log_file;


void list_ctor(list *lst, int capacity) {
    assert(lst != nullptr && "null pointer");
    const char *LOG_FILE = "/mnt/c/Users/User/Desktop/programs/list/res/log.html";

    lst->data = (arr_list *) calloc(capacity + 1, sizeof(arr_list));

    lst->size = 0;
    lst->head = 0;
    lst->free = 1;
    lst->tail = 0;
    lst->is_sorted = true;
    lst->capacity = capacity;

    for (unsigned i = 0; i < lst->capacity; i++) {
        lst->data[i].elem = 0;
        lst->data[i].next = i + 1;
        lst->data[i].prev = - 1;
    }

    lst->data[0].next = 0;
    lst->data[0].prev = 0;
    lst->data[lst->capacity - 1].next = 0;

    log_file = fopen(LOG_FILE, "w");
}


void list_dtor(list *lst) {
    assert(lst != nullptr && "null pointer");

    free(lst->data);
    fclose(log_file);

    lst->data = nullptr;
    lst->size     = -1;
    lst->head     = -1;
    lst->tail     = -1;
    lst->capacity = -1;
    lst->free     = -1;
}


void list_sort(list *lst) {

    assert(lst != nullptr && "null pointer");

    arr_list *data_sort = (arr_list *) calloc(lst->capacity, sizeof(arr_list));
    int next = lst->data[lst->head].next;
    unsigned i = 1;
    data_sort[0].elem = 0;
    data_sort[0].next = 1;
    
    for (i = 1; i <= lst->size; i++) {
        data_sort[i].elem = lst->data[next].elem;
        next = lst->data[next].next;
        data_sort[i].next = i + 1;
        data_sort[i].prev = i - 1;
    }

    lst->free = i;

    data_sort[0].prev = i - 1;
    data_sort[i - 1].next = 0;
    
    for (; i < lst->capacity; i++) {
        data_sort[i].elem = 0;
        data_sort[i].next = i + 1;
        data_sort[i].prev = -1;
    }
    data_sort[lst->capacity - 1].next = 0;

    free(lst->data);

    lst->data = data_sort;
    lst->is_sorted = true;
}

void list_realloc(list *lst) {
    assert(lst != nullptr && "null pointer");
    
    if (!lst->is_sorted) {
        list_sort(lst);
    }

    if (lst->is_sorted) {
        lst->capacity *= MULTIPLY;
        arr_list *data_copy = (arr_list *) calloc(lst->capacity, sizeof(arr_list));

        unsigned i = 0;

        for (; i < lst->capacity / MULTIPLY; i++) {
            data_copy[i].elem = lst->data[i].elem;
            data_copy[i].next = lst->data[i].next;
            data_copy[i].prev = lst->data[i].prev;
        }
        
        for (; i < lst->capacity; i++) {
            data_copy[i].elem = 0;
            data_copy[i].next = i + 1;
            data_copy[i].prev = -1;
        }

        data_copy[lst->capacity - 1].next = 0;
        free(lst->data);
        lst->data = data_copy;
    }
}

int list_insert(list *lst, int ind, elem_data_t value) {
    assert(lst != nullptr && "null pointer");

    if (lst->size == lst->capacity - 1) {
        list_realloc(lst);
    }

    lst->data[lst->free].elem = value;
    lst->data[lst->free].next = lst->data[ind].next;
    lst->data[lst->free].prev = ind;
    lst->data[lst->data[ind].next].prev = lst->free;
    lst->data[ind].next = lst->free; 

    lst->is_sorted = false;
    lst->size++;
    int count = 0;

    for (unsigned i = 1; i < lst->capacity; i++) {
        if (lst->data[i].prev == -1) {
            lst->free = i;
            count++;
            break;
        } 
    }
    
    if (count == 0) {
        list_realloc(lst);
    }

    return 0;
}

elem_data_t list_erase(list *lst, int ind) {

    assert(lst != nullptr && "null pointer");
    elem_data_t value = 0;

    int next, prev;
    value = lst->data[ind].elem;
    next  = lst->data[ind].next;
    prev  = lst->data[ind].prev;
    lst->data[next].prev = prev;
    lst->data[prev].next = next;

    lst->data[ind].elem = 0;
    // lst->data[ind].next = lst->free;
    lst->data[ind].next = ind + 1;

    lst->data[ind].prev = -1;
    lst->size--;

    for (unsigned i = 1; i < lst->capacity; i++) {
        if (lst->data[i].prev == -1) {
            lst->free = i;
            break;
        } else lst->free++;
    }

    return value;
}

int list_push_back(list *lst, elem_data_t value) {
    assert(lst != nullptr && "null pointer");
    list_insert(lst, lst->data[0].prev, value);
    return 0;
}

int list_push_front(list *lst, elem_data_t value) {
    assert(lst != nullptr && "null pointer");
    list_insert(lst, lst->head, value);
    return 0;
}

elem_data_t list_pop_back(list *lst) {
    assert(lst != nullptr && "null pointer");
    return list_erase(lst, lst->data[0].prev);
}

elem_data_t list_pop_front(list *lst) {
    assert(lst != nullptr && "null pointer");
    return list_erase(lst, lst->data[0].next);
}

