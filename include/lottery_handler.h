#ifndef LOTTERY_HANDLER_H_
#define LOTTERY_HANDLER_H_

#include "include/linked_list.h"
#include "include/common.h"
typedef struct 
{
    u_short state[5];
    u_short lucky_number[7];
    u_short user_number[5][7];
    u_short buy_number;
    char name[20];
    u_int lottery_issue;
    u_long id;
    u_long reward;
}LotteryData;

typedef struct list LotteryList;

/* function: get_lottery_buy_name
 * description: get user's name 
 * input: 
 *    p: a pointer to LotteryList node  
 * output:
 *    char*: a pointer to user's name 
 * return:
 *    user's name */
extern char* get_lottery_buy_name(LotteryList*);

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
extern int insert_lottery(LotteryList *head, u_short (*number)[7], u_short buy_number, const char *name, u_int lottery_issue);

/* function: generate_random_number
 * description: generate random number just one note
 * input:
 *    number: a char pointer to number
 * output:
 *    NULL
 * return:
 *    NULL */
extern void generate_random_number(u_short *number); 

/* function: quick_sort
 * description: sort lottery number in ascending code
 * input:
 *    a char pointer to number
 * output:
 *    NULL
 * return:
 *    NULL */
extern void quick_sort(u_short *number);

/* function: lottery_list_initialize
 * description: lottery list initize
 * input:
 *    lottery_head: address to LotteryList head pointer
 * output:
 *    0: success
 *    -1: error
 * return:
 *    called function state */
extern int lottery_list_initialize(LotteryList **lottery_head);

/* function: lottery_list_destory
 * description: destory lottery list
 * input:
 *    user_head: head pointer to LotteryList
 * output:
 *    NULL
 * return:
 *    NULL */
extern void lottery_list_destory(LotteryList *lottery_head);

/* function: delete_user_lottery
 * description: delete user's lottery when user delete user account
 * input:
 *    lottery_head: head pointer to LotteryList
 *    name: user's name
 * output:
 *    NULL
 * return:
 *    NULL */
extern void delete_user_lottery(LotteryList *lottery_head, const char *name);

#endif
