#ifndef NOTARY_UI_H_
#define NOTARY_UI_H_
#include "include/issue_handler.h"
#include "include/user_handler.h"
#include "include/lottery_handler.h"

/* function: notary_ui
 * description: notary GUI
 * input:
 *    user_head: head pointer to UserList
 *    lottery_head: head pointer to LotteryList
 *    issue_head: head pointer to IssueList
 * output:
 *    NULL
 * return:
 *    NULL */
extern void notary_ui(UserList *user_head, LotteryList *lottery_head, IssueList *issue_head);
#endif
