#ifndef LINKED_LIST_H
#define LINKED_LIST_H
#include <stdbool.h>

typedef struct node {
       int val;
       struct node * next;
} node_t;

bool isEmpty(node_t * first); 
void print_list(node_t * first); 
void add_to_end(node_t ** first, int to_add); 
void add_to_front(node_t ** first, int to_add); 
node_t * create_new_node(int val); 
void add_after_idx(node_t ** first, int toAdd, int idx); 
void add_before_idx(node_t ** first, int toAdd, int idx); 
void delete_first(node_t ** first); 
void delete_last(node_t ** first); 
void delete_value(node_t ** first, int val); 
void delete_idx(node_t ** first, int idx); 
void reverse(node_t ** first); 
#endif
