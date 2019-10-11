#ifndef ADMIN_UI_H_
#define ADMIN_UI_H_
#include "include/issue_handler.h"
#include "include/user_handler.h"

/* function: admin_ui
 * description: admin GUI
 * input:
 *    user_head: head pointer to UserList
 *    issue_head: head pointer to IssueList
 * output:  
 *    NULL
 * return:
 *    NULL */
extern void admin_ui(UserList *user_head, IssueList *issue_head);

/* function: issue_lottery_ui
 * description: the gui interface to issue lottery
 * input:
 *    issue_head: a pointer to IssueList
 * output:
 *    NULL
 * return:
 *    NULL */
extern void issue_lottery_ui(IssueList *issue_head);

/* function: search_user_by_name_ui
 * description: the gui interface to search user by name
 * input:
 *    user_head: a pointer to UserList
 * output:
 *    NULL
 * return:
 *    NULL */
extern void search_user_by_name_ui(UserList *user_head);

/* function: search_user_by_balance_ui
 * description: the gui interface to search user by balance
 * input:
 *    user_head: a pointer to UserList
 * output:
 *    NULL
 * return:
 *    NULL */
extern void search_user_by_balance_ui(UserList *user_head); 

/* function: sort_account_ui
 * description: the gui interface to sort account
 * input:
 *    user_head: a pointer to UserList
 * output:
 *    NULL
 * return:
 *    NULL */
extern void sort_account_ui(UserList *user_head);

/* function: show_all_user_ui
 * description: the gui interface to show all user's information
 * input:
 *    user_head: a pointer to UserList
 * output:
 *    NULL
 * return:
 *    NULL */
extern void show_all_user_ui(UserList *user_head); 

#endif
