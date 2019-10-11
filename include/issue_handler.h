#ifndef ISSUE_HANDLER_H_
#define ISSUE_HANDLER_H_

#include "include/common.h"

typedef struct 
{
    u_short state; //0: unpublished 1:published 
    u_short lucky_number[7];  
    u_short lottery_prize;
    u_int lottery_issue;
    u_long sold_number;
    u_long prize_pool;
}IssueData;

typedef struct list IssueList;


/* function: get_issue_state
 * description: check whether last lottery has been published
 * input: 
 *	  head: a pointer to the IssueList
 * output: 
 *    0: unpublished
 *    1: published
 *    2: none lottery issue 
 * return:
 *    issue state */
extern u_short get_issue_state(IssueList* head);

/* function: issue_lottery
 * description: be used to issue lottery by admin
 * input:
 *    head: a pointer to IssueList
 *    prize: lottery prize
 * output: 
 *    0: success
 *    -1: the last lottery is unpiblished or none lottery issue
 * return:
 *    function calling state */
extern int issue_lottery(IssueList *head, u_short prize);

/* function: deduct_reward
 * description: substract some amounts from prize pool
 * input:
 *    head: a pointer to IssueList
 *    amount: the money amount to lottery buyer
 * output: 
 *    NULL
 * return:
 *    NULL */
extern void deduct_reward(IssueList* head, u_long amount);

/* function: get_lottery_prize
 * description: get current lottery prize
 * input:
 *    head: a pointer to IssueList
 * output:
 *    0: none lottery issue 
 * return:
 *    current lottery prize */
extern u_short get_lottery_prize(IssueList *head);

/* function: get_current_issue
 * description: get current lottery issue
 * input: 
 *    head: a pointer to IssueList
 * output:
 *    0: no issue node or no initialize list
 * return:
 *    current lottery issue */
extern u_int get_issue(IssueList *head);

/* function: sold_ticket
 * description: modify sold_number and prize_pool in current lottery issue
 * input:
 *    head: a pointer to issue list
 *    money: a ticket's sold prize
 * output:
 *    NULL
 * return:
 *    NULL */
extern void sold_ticket(IssueList *head, u_long money);

 /* function: issue_list_initialize
 * description: issue list initize
 * input:
 *    user_head: address to IssueList head pointer
 * output:
 *    0: success
 *    -1: error
 * return:
 *    called function state */
extern int issue_list_initialize(IssueList **issue_head);

/* function: issue_list_destory
 * description: destory issue list
 * input:
 *    user_head: head pointer to IssueList
 * output:
 *    NULL
 * return:
 *    NULL */
extern void issue_list_destory(IssueList *issue_head);
#endif
