#ifndef MENU_UI_H_
#define MENU_UI_H_

#include "include/lottery_handler.h"
#include "include/user_handler.h"
#include "include/issue_handler.h"

/* function: choose_role_ui
 * description: choose role GUI
 * input:
 *    NULL
 * output:
 *    1: admin login ui
 *    2: user login ui
 *    0: quit
 *    -1: error
 * return:
 *    called function state */
extern int choose_role_ui(void);

/* function: choose_admin_ui
 * description: choose admin GUI
 * input: 
 *    NULL
 * output:
 *    1: admin login ui
 *    2: notary login ui
 *    0: back
 *    -1: error
 * return:
 *    called function state */
extern int choose_admin_ui(void);

/* function: login_or_register_ui
 * description: login or register GUI
 * input:
 *    user_head: head pointer to UserList
 *    lottery_head: head pointer to LotteryList
 *    issue_head: head pointer to IssueList
 * output:
 *    NULL
 * return:
 *    NULL */
extern void login_or_register_ui(UserList*, LotteryList*, IssueList*);

#endif
