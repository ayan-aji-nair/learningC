#include "linkedlist.h"
#include <stdio.h>
#include <stdlib.h>

bool isEmpty(node_t * first) {
        if(first == NULL) {
                return true;
        }
        return false;
}

void print_list(node_t * first) {
        node_t * current = first;
        if(current == NULL) {
                printf("NULL");
                return;
        }
        while(current != NULL) {
                if(current->next != NULL) {
                        printf("%d->", current->val);
                }
                else {
                        printf("%d", current->val);
                }
                current = current->next;
        }
}

void add_to_end(node_t ** first, int to_add) {
        // double pointer so dereference to get the first node
        node_t * current = *first;
        // create the node that we want to add
        node_t * new_node = (node_t *) malloc(sizeof(node_t));
        new_node->next = NULL;
        new_node->val = to_add;
        // if the first node is null
        if(*first == NULL) {
                *first = new_node;
                return;
        }
        // otherwise loop to the end
        while(current->next != NULL) {
                current = current->next;
        }
        // once we are at the end then add the new node
        current->next = new_node;
}

void add_to_front(node_t ** first, int to_add) {
        // no pointers necessary, we only need the first node
        // two cases - first node empty and first node not empty
        // but first we have to create our new node
        node_t * new_node = (node_t *) malloc(sizeof(node_t));
        new_node->next = NULL;
        new_node->val = to_add;
        // now we deal w case 1: the first node is empty
        if(*first == NULL) {
                *first = new_node;
                return;
        }
        // case 2: first node is not empty
        // so our new node becomes the new front of the list, so we 
        // put new_node in front of first and then reassign our first node
        // to point to the new node we created
        new_node->next = *first;
        *first = new_node;
}

node_t * create_new_node(int val) {
        node_t * new_node = (node_t *) malloc(sizeof(node_t));
        new_node->val = val;
        new_node->next = NULL;
        return new_node;
}

void add_after_idx(node_t ** first, int toAdd, int idx) {
        node_t * current = *first;
        node_t * toInsert = create_new_node(toAdd);
        if(idx == 0) {
                node_t * next = current->next;
                current->next = toInsert;
                return;
        }
        int i;
        for(i = 0; i < idx; i++) {
                if(current->next != NULL) {
                        current = current->next;
                }
                else {
                        return;
                }
        }
        node_t * temp = current->next;
        current->next = toInsert;
        toInsert->next = temp;
}

void add_before_idx(node_t ** first, int toAdd, int idx) {
        node_t * current = *first;
        node_t * toInsert = create_new_node(toAdd);
        if(idx == 0) {
                toInsert->next = current;
                *first = toInsert;
        }
        int i;
        for(i = 0; i < idx - 1; i++) {
                if(current->next != NULL) {
                        current = current->next;
                }
                else {
                        return;
                }
        }
        node_t * temp = current->next;
        current->next = toInsert;
        toInsert->next = temp;
}

void delete_first(node_t ** first) {
        if((*first) == NULL) {
                return;
        }
        if((*first)->next == NULL) {
                node_t * temp = *first;
                *first = NULL;
                free(temp);
                return;
        }
        node_t * temp = (*first);
        *first = (*first)->next;
        free(temp);
}

void delete_last(node_t ** first) {
        if((*first) == NULL) {
                return;
        }
        if((*first)->next == NULL) {
                delete_first(first);
                return;
        }
        node_t * current = *first;
        node_t * prev = NULL;
        while(current->next != NULL) {
                prev = current;
                current = current->next;
        }
        prev->next = current->next;
        free(current);
}

void delete_value(node_t ** first, int val) {
        node_t * current = *first;
        // if the first node is null then do nothing
        if(current == NULL) {
                return;
        }
        // if the value is in the first node then remove the first node
        if(current->val == val) {
                // if the next node is not null, then set the next node
                // to be the new first node
                delete_first(first);
                return;
        }
        // otherwise we want to look through the list
        while(current->next != NULL) {
                // if we find a value in the linked list equal to the value we 
                // want to delete, then delete it and end
                if(current->next->val == val) {
                        node_t * temp = current->next;
                        current->next = temp->next;
                        free(temp);
                }
                // advance the pointer
                current = current->next;
        }
}

/*
void delete_value(node_t ** head, int val) {
    node_t *previous, *current;

    if (*head == NULL) {
            return;
    }

    if ((*head)->val == val) {
            node_t * temp = (*head);
            (*head) = (*head)->next;
            free(temp);
    }
    previous = *head;
    current = (*head)->next;
    while (current) {
        if (current->val == val) {
            previous->next = current->next;
            free(current);
        }
        previous = current;
        current  = current->next;
    }
}
*/

void delete_idx(node_t ** first, int idx) {
        node_t * current = *first;
        // do nothing if the current node is null
        if(current == NULL) {
                return;
        }
        // two cases: idx in front and idx not in front
        // if the index is in front, then just delete the first nodd
        if(idx == 0) {
                *first = current->next;
                free(current);
                return;
        }
        // otherwise we scan through list up to the node before the index
        // we want to delete
        int i;
        for(i = 0; i < idx - 1; i++) {
               // only continue while there is a next node to scan
               // otherwise end the program
               if(current->next != NULL){
                        current = current->next;
               }
               else {
                       return;
               }
        }
        // delete the middle node temp
        node_t * temp = current->next;
        current->next = temp->next;
        free(temp);
}

void reverse(node_t ** first) {
        node_t * prev = NULL;
        node_t * current = *first;
        node_t * next = NULL;
        while(current != NULL) {
                next = current->next;
                current->next = prev;
                prev = current;
                current = next;
        }
        *first = prev;
}

int main() {
        /*
         * MANUAL INSERT
        node_t * test_list = (node_t *) malloc(sizeof(node_t));
        test_list->val = 1;
        test_list->next = (node_t *) malloc(sizeof(node_t));
        test_list->next->val = 2;
        test_list->next->next = (node_t *) malloc(sizeof(node_t));
        test_list->next->next->val = 3;
        test_list->next->next->next = (node_t *) malloc(sizeof(node_t));
        test_list->next->next->next->val = 4;
        test_list->next->next->next->next = NULL;
        */
        // better insert using add_to_end
        node_t * first = create_new_node(-1);
        printf("before inserting: ");
        print_list(first);
        printf("\n");
        int i;
        for(i=1; i < 10; i++) {
                if(i % 2 == 1) {
                        add_to_end(&first, i);
                }
        }
        printf("after inserting: ");
        print_list(first);
        add_to_front(&first, -2);
        printf("\n");
        printf("after adding to front: ");
        print_list(first);
        printf("\n");
        printf("after deleting 3: ");
        delete_value(&first, 3);
        print_list(first);
        printf("\n");
        printf("after reversing the list: ");
        reverse(&first);
        print_list(first);
        printf("\n");
        printf("after inserting value 11 after index 2: ");
        add_after_idx(&first, 11, 2);
        print_list(first);
        printf("\n");
        printf("after inserting value 12 before index 2: ");
        add_before_idx(&first, 12, 2);
        print_list(first);
        printf("\n");
        printf("after deleting first: ");
        delete_first(&first);
        print_list(first);
        printf("\n");
        printf("after deleting last: ");
        delete_last(&first);
        print_list(first);
        printf("\n");
        /*
        int j;
        for(j=5; j >=  0; j--) {
                printf("after deleting index %d: ", j);
                delete_idx(&first, j);
                print_list(first);
                printf("\n");
        }
        */

        node_t * null_list = NULL;
        printf("before inserting: ");
        print_list(null_list);
        printf("\n");
        printf("after inserting 50: ");
        add_to_end(&null_list, 50);
        print_list(null_list);
        printf("\n");
        delete_value(&null_list, 50);
        printf("after deleting 50: ");
        print_list(null_list);
        printf("\n");
        /*
        printf("after deleting 0: ");
        
        
        delete_value(&null_list, 0);
        print_list(null_list);
        */
}
