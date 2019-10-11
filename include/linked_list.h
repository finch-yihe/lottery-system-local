#ifndef LINKED_LIST_H_
#define LINKED_LIST_H_


union value
{
    void *data;
    int size;
};

typedef struct list
{
    union value data;
    struct list *pre;
    struct list *next;
}List;


/* function: create_list
 * description: create list and contain head
 * input:
 *    the size of data field in common node
 * output:
 *    List*: a pointer to head node
 * return:
 *    head node pointer */
extern List* create_list(int size);

/* function: create_node
 * description: create node
 * input: 
 *    head: head pointer
 *    data: a pointer to data field
 * output:
 *    List*: a pointer to new node 
 * return:
 *    new node pointer */
extern List* create_node(List *head, const void *data);

/* function: insert_node
 * description: insert node
 * input:
 *    head: head pointer
 *    new_node: new_node pointer
 * output:
 *    0: success
 *    -1: failure
 * return:
 *    called function state */
extern int insert_node(List *head, List *new_node);

/* function: delete_node
 * description: delete node
 * input: 
 *    del_node: deleted node pointer
 * output: 
 *    0: success
 *    -1: failure
 * return:
 *    called function state */
extern int delete_node(List *del_node);

/* function: find_node
 * description: find node
 * input:
 *    head: head node
 *    data: a pointer to data field in common 
 *    cmp: a function to pick the node you want to delete
 * output:
 *    0: success
 *    -1: failure
 * return:
 *    called function state */
extern List* find_node(List *head, const void *data, int(*cmp)(const void*, const void *));

/* function: sort_node
 * description: sort node
 * input:
 *    head: head pointer
 *    start: start pointer
 *    end: end pointer
 *    cmp: a function to compare two node
 * output:
 *    NULL
 * return: 
 *    NULL */
extern void sort_node(List *head, List *start, List *end, int(*cmp)(const void*, const void*));

/* function: free_list
 * description: free list
 * input:
 *    head: head pointer
 * output:
 *    NULL
 * return:
 *    NULL */
extern void free_list(List *head);

/* function: get_first_data
 * description: get the data in the first common node
 * input:
 *    head: head pointer
 *    data: a data field pointer to a node you want to store data from list 
 * output:
 *    0: success
 *    -1: failure
 * return: 
 *    called function state */
extern int get_first_data(List *head, void *data, int size);

#endif

