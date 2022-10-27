#ifndef LIST_DEBUG_HPP_INCLUDED
#define LIST_DEBUG_HPP_INCLUDED
#include "utils.hpp"

extern FILE *log_file;

void dump(list *lst);

void dump_grapviz(list *lst);

#endif