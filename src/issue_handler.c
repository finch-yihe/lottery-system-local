#include "include/issue_handler.h"
#include "include/linked_list.h"
#include "include/common.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

/* function: issue_head_initialize
 * description: issue list initize
 * input:
 *    user_head: address to IssueList head pointer
 * output:
 *    0: success
 *    -1: error
 * return:
 *    called function state */
int issue_list_initialize(IssueList **issue_head)
{
    if((*issue_head = create_list(sizeof(IssueData))) == NULL){
        printf("[ Error ] Failed to create issue linked list!\n");
        return -1;
    }
    FILE *fp = fopen(ISSUEPATH, "ab+");
    if(fp == NULL){
        printf("[ Error ] Failed to open file!\n");
        return -1;
    }
    IssueData issue_data;
    while(fread(&issue_data, sizeof(IssueData), 1, fp)){
       insert_node(*issue_head, create_node(*issue_head, &issue_data)); 
    }
    fclose(fp);
    return 0;
}

/* function: issue_head_destory
 * description: destory issue list
 * input:
 *    user_head: head pointer to IssueList
 * output:
 *    NULL
 * return:
 *    NULL */
void issue_list_destory(IssueList *issue_head)
{
    FILE *fp = fopen(ISSUEPATH, "w+");
    IssueData issue_data;
    while(!get_first_data(issue_head, &issue_data, sizeof(IssueData))){
        fwrite(&issue_data, sizeof(IssueData), 1, fp);
    }
    fclose(fp);
    free(issue_head);
    return;
}

/* function: get_max_issue
 * description: get max issue
 * input: 
 *    head: a pointer to IssueList
 * output:
 *    -1: no initialize list
 *    1: no issue node
 * return:
 *    max issue */
int get_max_issue(IssueList *head)
{
    if(head == NULL)
        return -1;
    if(head->next == head)
        return 1;
    return ((IssueData*)(head->pre->data.data))->lottery_issue + 1;
}


/* function: get_current_issue
 * description: get current lottery issue
 * input: 
 *    head: a pointer to IssueList
 * output:
 *    0: no issue node or no initialize list
 * return:
 *    current lottery issue */
u_int get_issue(IssueList *head)
{
    if(head==NULL || head->next==head)
        return 0;
    return ((IssueData*)(head->pre->data.data))->lottery_issue;
}

/* function: get_prize_pool
 * description: get current issued lottery's ticket prize
 * input:
 *    head: a pointer to IssueList
 * output:
 *    -1: no initialize list
 *    STARTCAPITAL: start-up capital
 * return:
 *    prize pool */
int get_prize_pool(IssueList *head)
{
    if(head == NULL)
        return -1;
    if(head->next == head)
        return STARTCAPITAL;
    return ((IssueData*)(head->pre->data.data))->prize_pool;
}

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
int issue_lottery(IssueList *head, u_short prize)
{
    if(head==NULL) 
        return -1;
    if(head->next!=head && ((IssueData*)(head->pre->data.data))->state==0)
        return -1;
    IssueData issue_data;
    memset(&issue_data, 0, sizeof(IssueData));
    issue_data.lottery_issue = (u_int)get_max_issue(head);
    issue_data.lottery_prize = prize;
    issue_data.prize_pool = get_prize_pool(head);
    return insert_node(head, create_node(head, &issue_data));
}

/* function: deduct_reward
 * description: substract some amounts from prize pool
 * input:
 *    head: a pointer to IssueList
 *    amount: the money amount to lottery buyer
 * output: 
 *    NULL
 * return:
 *    NULL */
void deduct_reward(IssueList *head, u_long amount)
{
    if(head==NULL || head==head->next)
        return;
    ((IssueData*)(head->pre->data.data))->prize_pool -= amount;
        return;
}

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
u_short get_issue_state(IssueList* head)
{
    if(head==NULL || head==head->next)
        return 2;
    return ((IssueData*)(head->pre->data.data))->state;
}

/* function: get_lottery_prize
 * description: get current lottery prize
 * input:
 *    head: a pointer to IssueList
 * output:
 *    0: none lottery issue 
 * return:
 *    current lottery prize */
u_short get_lottery_prize(IssueList *head)
{
    if(head==NULL || head==head->next)
        return 0;
    return ((IssueData*)(head->pre->data.data))->lottery_prize;
}

/* function: sold_ticket
 * description: modify sold_number and prize_pool in current lottery issue
 * input:
 *    head: a pointer to issue list
 *    money: a ticket's sold prize
 * output:
 *    NULL
 * return:
 *    NULL */
void sold_ticket(IssueList *head, u_long money)
{
    ((IssueData*)(head->pre->data.data))->sold_number++;
    ((IssueData*)(head->pre->data.data))->prize_pool += money;
    return;
}
