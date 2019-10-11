#ifndef USER_HANDLER_H_
#define USER_HANDLER_H_

#include "include/linked_list.h"
#include "include/common.h"
#include "include/issue_handler.h"

typedef struct 
{
    char name[VALID];
    char passwd[VALID];
    int balance;
}UserData;

typedef struct list UserList;

typedef struct
{
    char name[VALID];
    char phone[PHONELEN+1];
    char idcode[IDCODELEN+1];
}UserInfo;

/* function: user_login
 * description: user login
 * input:
 *    user_head: head pointer to UserList
 * output:
 *    -1: error
 *    1: input name format error
 *    2: fail to match password 
 *    3: identify code failure
 * return:
 *    called function state */
extern int user_login(UserList *user_head);

/* function: user_register
 * description: user register
 * input:
 *    user_head: head pointer to UserList
 *    issue_head: head pointer to IssueList
 * output:
 *    -1: format error
 *    1: user no exist
 *    2: passwd no match
 *    3: insert node error
 *    0: success
 * return:
 *    called fucntion state */
extern int user_register(UserList*, IssueList*);

/* function: get_user_info
 * description: get user's information
 * input:
 *    user_info: a pointer to UserInfo data to store user information
 *    name: a char pointer to user's name
 * output: 
 *    -1: file stream error
 *    0: success
 * return:
 *    whether get the user's information */
extern int get_user_info(UserInfo*, const char*);

/* function: get_user_node
 * description: get user node
 * input: 
 *    user_head: head pointer to UserList
 *    name: a char pointer to user's name
 * output:
 *    UserList*: a UserList pointer to store UserData
 * return:
 *    a UserList pointer */
extern UserList* get_user_node(UserList*, const char*); 

/* function: get_user_balance
 * description: get user's balance
 * input: 
 *    user_head: head pointer to UserList
 *    name: a char pointer to user's name
 * output:
 *    int: user's balance
 * return: 
 *    user's balance */
extern int get_user_balance(UserList*, const char*);

/* function: change_balance
 * description: change user's balance
 * input:
 *    user_head: head pointer to UserList
 *    name: a char pointer to user's name
 *    money: a number to add to user's balance
 * output:
 *    -1: error
 *    0: success
 * return:
 *    called function state */
extern int change_balance(UserList*, const char*, int);

/* function: get_user_data
 * description: get user's data
 * input:
 *    user_head: head pointer to UserList
 *    name: a char pointer to user's name
 * output:
 *    UserData*: a UserData pointer to store user data
 * return:
 *    user's data */
extern UserData* get_user_data(UserList*, const char*);

/* function: get_user_passwd
 * description: get user passwd
 * input:
 *    user_head: head pointer to UserList
 *    name: a char pointer to user's passwd
 * output:
 *    char*: a char pointer to user's passwd
 * return:
 *    user's passwd */
extern char* get_user_passwd(UserList*, const char*); 

/* function: sort_user_by_name
 * description: sort user list by name
 * input:
 *    user_head: head pointer to UserList
 * output:
 *    NULL
 * return:
 *    NULL */
extern void sort_user_by_name(UserList*);

/* function: sort_user_by_balance
 * description: sort user list by balance
 * input:
 *    user_head: head pointer to UserList
 * output:
 *    NULL
 * return:
 *    NULL */
extern void sort_user_by_balance(UserList*);

/* function: user_list_initialize
 * description: user list initize
 * input:
 *    user_head: address to UserList head pointer
 * output:
 *    0: success
 *    -1: error
 * return:
 *    called function state */
extern int user_list_initialize(UserList **user_head);

/* function: user_list_destory
 * description: destory user list
 * input:
 *    user_head: head pointer to UserList
 * output:
 *    NULL
 * return:
 *    NULL */
extern void user_list_destory(UserList *user_head);
#endif
