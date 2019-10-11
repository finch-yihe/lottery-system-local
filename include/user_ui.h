#ifndef USER_UI_H_
#define USER_UI_H_

#include "include/user_handler.h"
#include "include/lottery_handler.h"

/* function: user_ui
 * description: user GUI
 * input: 
 *    user_head: head pointer to UserList
 *    lottery_head: head pointer to LotteryList
 *    issue_head: head pointer to IssueList
 * output:
 *    NULL
 * return:
 *    NULL */
extern void user_ui(UserList *user_head, LotteryList *lottery_head, IssueList *issue_head);


#endif
