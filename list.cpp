#include "list.hpp"
FILE *log_file;
const char *LOG_FILE = "log.txt";

void list_ctor(list *lst, int capacity) {
    assert(lst != nullptr && "null pointer");

    lst->data = (arr_list *) calloc(capacity + 1, sizeof(arr_list));
    lst->size = 0;
    lst->head = 1;
    lst->free = 1;
    lst->tail = 1;
    lst->is_sorted = true;
    lst->capacity = capacity;
    for (unsigned i = 0; i < lst->capacity; i++) {
        lst->data[i].elem = 0;
        lst->data[i].next = -1;
        lst->data[i].prev = i - 1;
    }
    lst->data[0].next = 0;
    lst->data[0].prev = 0;
    // lst->data[capacity - 1].next = 0;
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

void dump(list *lst) {
    assert(lst != nullptr && "null pointer");

    // FILE *log = fopen(LOG_FILE, "w");

    fprintf(log_file, "size:     %lu\n", lst->size);
    fprintf(log_file, "capacity: %lu\n", lst->capacity);
    fprintf(log_file, "head:     %d\n", lst->head);
    fprintf(log_file, "tail:     %d\n", lst->tail);
    fprintf(log_file, "free:     %d\n", lst->free);


    fprintf(log_file, "n:\n");
    for (unsigned i = 0; i < lst->capacity; i++)
        fprintf(log_file, "%10d", i);
    fprintf(log_file, "\n\n");

    fprintf(log_file, "data:\n");
    for (unsigned i = 0; i < lst->capacity; i++)
        fprintf(log_file, "%10d", lst->data[i].elem);
    fprintf(log_file, "\n\n");

    fprintf(log_file, "next:\n");
    for (unsigned i = 0; i < lst->capacity; i++)
        fprintf(log_file, "%10d", lst->data[i].next);
    fprintf(log_file, "\n\n");

    fprintf(log_file, "prev:\n");
    for (unsigned i = 0; i < lst->capacity; i++)
        fprintf(log_file, "%10d", lst->data[i].prev);
    fprintf(log_file, "\n\n");
}

void list_realloc(list *lst) {
    assert(lst != nullptr && "null pointer");

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
        data_copy[i].next = -1;
        data_copy[i].prev = i - 1;
    }
    free(lst->data);
    lst->data = data_copy;
    }
}

int list_insert(list *lst, int ind, elem_data_t value) {
    assert(lst != nullptr && "null pointer");

    if (lst->size == lst->capacity - 1) {
        list_realloc(lst);
    }
    if (ind == 0) {
        printf("you are trying to put an element at 0\n");
        return 0;
    } else if (ind == lst->head && ind == lst->tail) {
        lst->data[ind].elem = value; 
        lst->data[ind].next = lst->head + 1;
        lst->data[ind].prev = 0;
        lst->tail++;
    }else if (ind == lst->head) {
        lst->data[ind].elem = value; 
        lst->data[ind].next = lst->head + 1;
        lst->data[ind].prev = 0;
    } else if (ind == lst->tail) {
        lst->data[ind].elem = value;
        for (unsigned i = 1; i < lst->capacity; i++) {
            if (lst->data[i].next == 0) {
                lst->data[i].next = lst->tail;
                lst->data[ind].prev = i;
                break;
            }
        }
        lst->data[ind].next = 0;
        lst->tail++;
    } else {
        int next = lst->data[ind].next;
        int prev = lst->data[ind + 1].prev;

        lst->data[lst->free].elem = value;
        lst->data[ind].next = lst->free;
        lst->data[ind + 1].prev = lst->free;

        lst->data[lst->free].next = next;
        lst->data[lst->free].prev = prev;

        lst->tail++;
        lst->is_sorted = false;
    }

    lst->size++;
    for (unsigned i = 1; i < lst->capacity; i++) {
        if (lst->data[i].next == -1) {
            lst->free = i;
            break;
        } else lst->free++;
    }
    return 0;
}

elem_data_t list_erase(list *lst, int ind) {
    assert(lst != nullptr && "null pointer");
    elem_data_t value = 0;
    int next, prev;
    if (ind == lst->head) {
        value = lst->data[ind].elem;
        next  = lst->data[ind].next;
        lst->data[next].prev = 0;
        lst->data[ind].elem  = 0;
        lst->data[ind].next  = -1;
        
        if (lst->head == 1) lst->data[ind].prev = lst->capacity - 1;
        else lst->data[ind].prev = lst->head - 1;
        lst->head = next;
    } else if (ind == lst->tail - 1) {
        value = lst->data[ind].elem;
        prev =  lst->data[ind].prev;

        lst->data[ind].elem = 0;

        lst->data[prev].next = 0;
        lst->data[ind].next  = -1;

        lst->tail = prev + 1; 
    } else {
        value = lst->data[ind].elem;
        next  = lst->data[ind].next;
        prev  = lst->data[ind].prev;

        lst->data[next].prev = prev;
        lst->data[prev].next = next;
        lst->data[ind].elem = 0;
        lst->data[ind].next = -1;
        lst->data[ind].prev = lst->free - 1;
    }
    lst->size--;
    for (unsigned i = 1; i < lst->capacity; i++) {
        if (lst->data[i].next == -1) {
            lst->free = i;
            break;
        } else lst->free++;
    }

    return value;
}
