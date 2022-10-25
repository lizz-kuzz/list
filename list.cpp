#include "list.hpp"

FILE *log_file;
const char *LOG_FILE = "log.txt";

void list_ctor(list *lst, int capacity) {
    assert(lst != nullptr && "null pointer");

    lst->data = (arr_list *) calloc(capacity + 1, sizeof(arr_list));
    lst->size = 0;
    lst->head = 1;
    lst->free = 1;
    lst->tail = 2;
    lst->capacity = capacity;
    for (unsigned i = 0; i < lst->capacity; i++) {
        lst->data[i].elem = 0;
        lst->data[i].next = i + 1;
        lst->data[i].prev = -1;
    }
    lst->data[0].next = 0;
    lst->data[0].prev = 0;
    lst->data[capacity - 1].next = 0;
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
    fprintf(log_file, "tail:     %d\n", lst->tail);
    fprintf(log_file, "free:     %d\n", lst->free);
    fprintf(log_file, "head:     %d\n", lst->head);


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

void list_insert(list *lst, int id, elem_data_t value) {
    assert(lst != nullptr && "null pointer");

    if (lst->size == lst->capacity - 1) {
        // realloc
    }
    if (id == lst->head) {
        lst->data[id].elem = value; 
        lst->free++;
        lst->size++;
        lst->data[id].prev = id - 1;
    } else if (id == lst->tail) {
        lst->data[id].elem = value;
        lst->tail++;
        lst->free++;
        lst->size++;
        lst->data[id].prev = lst->data[id - 1].next;
    } else {
        lst->data[id].elem = value;
        lst->data[id].next = id;
        lst->data[id].prev = id - 2;
        lst->tail++;
        lst->size++;

    }
}