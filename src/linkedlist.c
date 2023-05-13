#include <stdio.h>
#include <stdlib.h>

typedef struct node {
       int val;
       struct node * next;
} node_t;

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
        new_node->val = to_add;
        // if the first node is null
        if(current == NULL) {
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
        return new_node;
}

void delete_value(node_t ** first, int val) {
        node_t * current = *first;
        // if the first node is null then do nothing
        if(current == NULL) {
                return;
        }
        // if the value is in the first node then remove the first node
        if(current->val == val) {
                free(current);
                // if the next node is not null, then set the next node
                // to be the new first node
                if(current->next != NULL) {
                        *first = current->next;
                }
        }
        while(current->next != NULL) {
                if(current->next->val == val) {
                        node_t * temp = current->next;
                        current->next = temp->next;
                        free(temp);
                }
                current = current->next;
        }
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
