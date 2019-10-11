#include "include/lottery_handler.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* function: lottery_head_initialize
 * description: lottery list initize
 * input:
 *    lottery_head: address to LotteryList head pointer
 * output:
 *    0: success
 *    -1: error
 * return:
 *    called function state */
int lottery_list_initialize(LotteryList **lottery_head)
{
    if((*lottery_head = create_list(sizeof(LotteryData))) == NULL){
        printf("[ Error ] Failed to create lottery linked list!\n");
        return -1;
    }
    FILE *fp = fopen(LOTTERYPATH, "ab+");
    if(fp == NULL){
        printf("[ Error ] Failed to open file!\n");
        return -1;
    }
    LotteryData lottery_data;
    while(fread(&lottery_data, sizeof(LotteryData), 1, fp)){
       insert_node(*lottery_head, create_node(*lottery_head, &lottery_data)); 
    }
    fclose(fp);
    return 0;
}

/* function: lottery_head_destory
 * description: destory lottery list
 * input:
 *    user_head: head pointer to LotteryList
 * output:
 *    NULL
 * return:
 *    NULL */
void lottery_list_destory(LotteryList *lottery_head)
{
    FILE *fp = fopen(LOTTERYPATH, "w+");
    LotteryData lottery_data;
    while(!get_first_data(lottery_head, &lottery_data, sizeof(LotteryData))){
        fwrite(&lottery_data, sizeof(LotteryData), 1, fp);
    }
    fclose(fp);
    free(lottery_head);
    return;
}

/* function: get_lottery_buy_name
 * description: get user's name 
 * input: 
 *    p: a pointer to LotteryList node  
 * output:
 *    char*: a pointer to user's name 
 * return:
 *    user's name */
char* get_lottery_buy_name(LotteryList *p)
{
    if(p==NULL || p==p->next)
        return NULL;
    return ((LotteryData*)(p->data.data))->name;
}


/* function: quick_sort
 * description: sort lottery number in ascending code
 * input:
 *    a char pointer to number
 * output:
 *    NULL
 * return:
 *    NULL */
void quick_sort(u_short *number){
    for(int i=0; i<5; i++){
        int flag = 0;
        for(int j=5; j>i; j--){
            if(*(number+j) < *(number+j-1)){
                u_short temp = *(number+j);
                *(number+j) = *(number+j-1);
                *(number+j-1) = temp;
                flag = 1;
            }
        }
        if(!flag)
            break;
    }
}

/* function: generate_random_number
 * description: generate random number just one note
 * input:
 *    number: a char pointer to number
 * output:
 *    NULL
 * return:
 *    NULL */
void generate_random_number(u_short *number)
{
    for(int i=0; i<6; i++){
        u_short t = NUMBERRANGE;
        for(int j=0; j<i; j++){
            if(*(number+j) == t)
                break;
        }
        *(number+i) = t;
    }
    *(number+6) = NUMBERRANGE;
    quick_sort(number);
}

/* function: get_max_lottery_id
 * description: get max lottery id
 * input:
 *    head: head pointer to LotteryList
 *    lottery_issue: last lottery's issue
 * output:
 *    0: error
 * return:
 *    max lottery id */
static u_long get_max_lottery_id(LotteryList *head, u_int lottery_issue)
{
    if(head == NULL)
        return 0;
    if(head->next==head){
        return 1;
    }
    if(lottery_issue == ((LotteryData*)(head->pre->data.data))->lottery_issue)
        return ((LotteryData*)(head->pre->data.data))->id + 1;
    else{
        return 1;
    }
}

/* function: insert_lottery
 * description: insert lottery into LotteryList after user buy a ticket
 * input: 
 *    head: head pointer to LotteryList
 *    number: a 2-D array representing number user has bought
 *    name: user's name
 *    lottery_issue: lottery issue
 * output:
 *    0: success
 *    -1: failure
 * return:
 *    called function state */
int insert_lottery(LotteryList *head, u_short (*number)[7], u_short buy_number, const char *name, u_int lottery_issue)
{
    LotteryData data;
    memset(&data, 0, sizeof(LotteryData));
    memcpy(data.user_number, number, 5 * 7 * sizeof(u_short));
    data.buy_number = buy_number;
    strcpy(data.name, name);
    data.lottery_issue = lottery_issue;
    data.id = get_max_lottery_id(head, lottery_issue);
    return insert_node(head, create_node(head, &data));
}

/* function: delete_user_lottery
 * description: delete user's lottery when user delete user account
 * input:
 *    lottery_head: head pointer to LotteryList
 *    name: user's name
 * output:
 *    NULL
 * return:
 *    NULL */
extern void delete_user_lottery(LotteryList *lottery_head, const char *name)
{
    if(lottery_head == NULL || lottery_head->next == lottery_head)
        return;
    LotteryList *p = lottery_head->next;
    LotteryList *q = NULL;
    while(p != lottery_head){
        q = p;
        p = p->next;
        if(strcmp(((LotteryData*)(p->data.data))->name, name) == 0)
            delete_node(p);
    }
}

