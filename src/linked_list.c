#include "include/linked_list.h"
#include <stdlib.h>
#include <string.h>

/* function: create_list
 * description: create list and contain head
 * input:
 *    the size of data field in common node
 * output:
 *    List*: a pointer to head node
 * return:
 *    head node pointer */
List* create_list(int size)
{
    List *head = (List*)calloc(1, sizeof(List));
    if(head == NULL){
        return NULL;
    }
    head->next = head;
    head->pre = head;
    head->data.size = size;
    return head;
}

/* function: create_node
 * description: create node
 * input: 
 *    head: head pointer
 *    data: a pointer to data field
 * output:
 *    List*: a pointer to new node 
 * return:
 *    new node pointer */
List* create_node(List *head, const void *data)
{
    List* new_node = (List*)calloc(1, sizeof(List));
    if(new_node == NULL){
        return NULL;
    }
    new_node->data.data = calloc(1, head->data.size);
    memcpy(new_node->data.data, data, head->data.size);
    return new_node;
}

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
int insert_node(List *head, List *new_node)
{
    if(head == NULL){
        return -1;
    }
    if(new_node == NULL){
        return -1;
    }
    new_node->next = head;
    new_node->pre = head->pre;
    head->pre->next = new_node;
    head->pre = new_node;
    return 0;
}

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
List* find_node(List *head, const void *data, int(*cmp)(const void*, const void*))
{
    if(head == NULL){
        return NULL;
    }
    List *p = head->next;
    while(p != head){
        if(cmp(p->data.data, data) == 0){
            return p;
        }
        p = p->next;
    }
    return NULL;
}

/* function: delete_node
 * description: delete node
 * input: 
 *    del_node: deleted node pointer
 * output: 
 *    0: success
 *    -1: failure
 * return:
 *    called function state */
int delete_node(List* del_node)
{
    if(del_node == NULL || del_node->next == del_node){
        return -1;
    }
    del_node->pre->next = del_node->next;
    del_node->next->pre = del_node->pre;
    free(del_node->data.data);
    free(del_node);
    return 0;
}

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
void sort_node(List *head, List *start, List *end,  int(*cmp)(const void*, const void*))
{
    if(head==NULL || start->next==head || end->next==start || start==end)
        return;
    List *p = start;
    List *q = end;
    void *data = p->data.data;
    while(p != q){
        while(cmp(q->data.data, data)>0 && p!=q){
            q = q->pre;
        }
        p->data = q->data;
        while(cmp(p->data.data, data)<0 && p!=q){
            p = p->next;
        }
        q->data = p->data;
    }
    p->data.data = data;
    sort_node(head, start, p->pre, cmp);
    sort_node(head, p->next, end, cmp);
}

/* function: free_list
 * description: free list
 * input:
 *    head: head pointer
 * output:
 *    NULL
 * return:
 *    NULL */
void free_list(List *head)
{
    if(head == NULL){
        return;
    }
    List *p = head->next;
    while(p != head){
        p = p->next;
        free(p->pre->data.data);
        free(p->pre);
    }
    free(head);
}


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
int get_first_data(List *head, void *data, int size)
{
    if(head == NULL || head->next == head){
        return -1;
    }
    memcpy(data, head->next->data.data, size);
    delete_node(head->next);
    return 0;
}
