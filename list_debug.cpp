#include "list_debug.hpp"

static int number_png = 0;

void dump(list *lst) {
    assert(lst != nullptr && "null pointer");

    fprintf(log_file, "<pre>\n");

    fprintf(log_file, "size:     %lu\n", lst->size);
    fprintf(log_file, "capacity: %lu\n", lst->capacity);
    fprintf(log_file, "head:     %d\n", lst->head);
    fprintf(log_file, "tail:     %d\n", lst->tail);
    fprintf(log_file, "free:     %d\n", lst->free);


    // fprintf(log_file, "n:\n");
    // for (unsigned i = 0; i < lst->capacity; i++)
    //     fprintf(log_file, "%10d", i);
    // fprintf(log_file, "\n\n");

    // fprintf(log_file, "data:\n");
    // for (unsigned i = 0; i < lst->capacity; i++)
    //     fprintf(log_file, "%10d", lst->data[i].elem);
    // fprintf(log_file, "\n\n");

    // fprintf(log_file, "next:\n");
    // for (unsigned i = 0; i < lst->capacity; i++)
    //     fprintf(log_file, "%10d", lst->data[i].next);
    // fprintf(log_file, "\n\n");

    // fprintf(log_file, "prev:\n");
    // for (unsigned i = 0; i < lst->capacity; i++)
    //     fprintf(log_file, "%10d", lst->data[i].prev);
    // fprintf(log_file, "\n\n\n\n");

    dump_grapviz(lst);

    fprintf(log_file, "<img src=\"../src/output%d.png\" width=\"10000\" height=\"20987654300\">\n", number_png);
}

void dump_grapviz(list *lst) {
    assert(lst != nullptr && "null pointer");
    const char *GRAF_FILE = "/mnt/c/Users/User/Desktop/programs/list/src/graph.dot";
    FILE *graph = fopen(GRAF_FILE, "w");
    fprintf(graph, "digraph {\n");
    fprintf(graph, "\t\nnodesep = 1\n\tsplines = ortho\n\tnode [shape=record]\n\trankdir=LR\n\n");

    for (unsigned i = 0; i < lst->capacity; i++) {
        fprintf(graph, "\tstruct%d [label=\"%d|%d|{%d|%d}\"]\n", i, i, lst->data[i].elem, lst->data[i].next, lst->data[i].prev);
    }
    fprintf(graph, "\n");

    for (unsigned i = 0; i < lst->capacity - 1; i++) {
        fprintf(graph, "\tstruct%d -> struct%d [weight=1000, style=\"invis\"] \n", i, i + 1);
    }
    fprintf(graph, "\n");

    for (unsigned i = 0; i < lst->capacity && lst->data[i].next != -1 ; i++) {
        fprintf(graph, "\tstruct%d -> struct%d [color=\"red\", constraint=fasle] \n", i, lst->data[i].next);
    }
    fprintf(graph, "\n");

    for (unsigned i = 1; i < lst->capacity; i++) {
        fprintf(graph, "\tstruct%d -> struct%d [color=\"blue\", constraint=fasle]\n", i, lst->data[i].prev);
    }
    fprintf(graph, "\n");

    // fprintf(graf, "\tfree [shape=rectangle, fillcolor=#98FB98]\n");

    fprintf(graph, "\tfree -> struct%d [color=\"green\"] {rank = same; free; struct%d;};\n", lst->free, lst->free);

    fprintf(graph, "}\n");
    fclose(graph);

    char cmd[100] = "";
    sprintf(cmd, "dot src/graf.dot -Tpng -o src/output%d.png", number_png);
    system(cmd);
    number_png++;
}