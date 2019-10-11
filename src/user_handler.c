#include "include/common.h"
#include "include/user_handler.h"
#include "include/issue_handler.h"
#include "include/linked_list.h"
#include "include/standard_input.h"
#include "include/user_ui.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

/* function: user_head_initialize
 * description: user list initize
 * input:
 *    user_head: address to UserList head pointer
 * output:
 *    0: success
 *    -1: error
 * return:
 *    called function state */
int user_list_initialize(UserList **user_head)
{
    if((*user_head = create_list(sizeof(UserData))) == NULL){
        printf("[ Error ] Failed to create user linked list!\n");
        return -1;
    }
    FILE *fp = fopen(USERLISTPATH, "ab+");
    if(fp == NULL){
        printf("[ Error ] Failed to open file!\n");
        return -1;
    }
    UserData user_data;
    while(fread(&user_data, sizeof(UserData), 1, fp)){
       insert_node(*user_head, create_node(*user_head, &user_data)); 
    }
    fclose(fp);
    return 0;
}

/* function: user_head_destory
 * description: destory user list
 * input:
 *    user_head: head pointer to UserList
 * output:
 *    NULL
 * return:
 *    NULL */
void user_list_destory(UserList *user_head)
{
    FILE *fp = fopen(USERLISTPATH, "w+");
    UserData user_data;
    while(!get_first_data(user_head, &user_data, sizeof(UserData))){
        fwrite(&user_data, sizeof(UserData), 1, fp);
    }
    fclose(fp);
    free(user_head);
    return;
}

/* function: compare_name
 * description: a function to compare name
 * input:
 *    p: a void pointer 
 *    q: a void pointer
 * output:
 *    1: the former > the latter
 *    -1: the former < the latter
 *    0: the former = the latter 
 * return:
 *    compare result */
static int compare_name(const void *p, const void *q)
{
    UserData *_p = (UserData*)p;
    UserData *_q = (UserData*)q;
    if(strcmp(_p->name, _q->name) == 0){
        return 0;
    }else if(strcmp(_p->name, _q->name) > 0)
        return 1;
    else
        return -1;
}

/* function: save_user
 * description: save user information in the file when user 
 *    register or change his or her information
 * input:
 *    user_data: a UserData pointer to user data
 * output:  
 *    NULL
 * return:
 *    NULL */
static void save_user(UserData *user_data)
{
    char path[30] = USERDATAPATH;
    strcat(path, user_data->name);
    FILE *fp = fopen(path, "w+");
    UserInfo user_info;
    memset(&user_info, 0, sizeof(UserInfo));
    strcpy(user_info.name, user_data->name);
    fwrite(&user_info, sizeof(UserInfo), 1, fp);
    fclose(fp);
}

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
int user_login(UserList *user_head)
{
    if(user_head == NULL){
        return -1;
    }
    UserData user;
    memset(&user, 0, sizeof(UserData));
    if(input_name(user.name) == NULL){
        return -1;
    }
    UserList *p = get_user_node(user_head, user.name);  
    if(p == NULL){
        return 1;
    }
    if(strcmp(get_user_passwd(user_head, user.name), input_passwd(user.passwd, 1)) != 0){
        return 2;
    }
    if(!identifyCode()){
        extern char current_user[VALID];
        strcpy(current_user, user.name);
        return 0;
    }else{
        return 3;
    }
}

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
int user_register(UserList *user_head, IssueList *issue_head)
{
    if(user_head==NULL || issue_head==NULL){
        return -1;
    }
    UserData user_data;
    memset(&user_data, 0, sizeof(UserData));
    if(input_name(user_data.name) == NULL){
        return -1;
    }
    if(get_user_node(user_head, user_data.name) != NULL){
        return 1;
    }
    if(input_passwd(user_data.passwd, 0) == NULL){
        return 2;
    }else{
        if(issue_head->next==issue_head || ((IssueData*)(issue_head->pre->data.data))->prize_pool<10){
            save_user(&user_data);
            insert_node(user_head, create_node(user_head, &user_data)); 
            return 3; 
        }else{
            ((IssueData*)(issue_head->pre->data.data))->prize_pool -= 10;
            user_data.balance = 10;
            save_user(&user_data);
            return insert_node(user_head, create_node(user_head, &user_data));        
        }
    }
}

/* function: compare_balance
 * description: a function to compare user's balance
 * input:
 *    p: a void pointer 
 *    q: a void pointer
 * output:
 *    1: the former <= the latter
 *    -1: the former > the latter
 * return:
 *    compare result */
static int compare_balance(const void *p, const void *q)
{
    UserData *_p = (UserData*)p;
    UserData *_q = (UserData*)q;
    if(_p->balance <= _q->balance)
        return 1;
    return -1;
}

/* function: get_user_data
 * description: get user's data
 * input:
 *    user_head: head pointer to UserList
 *    name: a char pointer to user's name
 * output:
 *    UserData*: a UserData pointer to store user data
 * return:
 *    user's data */
UserData* get_user_data(UserList *user_head, const char *name)
{
    UserData user;
    memset(&user, 0, sizeof(UserData));
    strcpy(user.name, name);
    if(find_node(user_head, &user, compare_name) == NULL)
        return NULL;
    return (UserData*)(find_node(user_head, &user, compare_name)->data.data);
}

/* function: get_user_node
 * description: get user node
 * input: 
 *    user_head: head pointer to UserList
 *    name: a char pointer to user's name
 * output:
 *    UserList*: a UserList pointer to store UserData
 * return:
 *    a UserList pointer */
UserList* get_user_node(UserList *user_head, const char *name)
{
    UserData user_data;
    memset(&user_data, 0, sizeof(UserData));
    strcpy(user_data.name, name);
    return find_node(user_head, &user_data, compare_name);
}

/* function: get_user_passwd
 * description: get user passwd
 * input:
 *    user_head: head pointer to UserList
 *    name: a char pointer to user's passwd
 * output:
 *    char*: a char pointer to user's passwd
 * return:
 *    user's passwd */
char* get_user_passwd(UserList *user_head, const char *name)
{
    UserData *p = get_user_data(user_head, name);
    if(p == NULL)
        return NULL;
    return p->passwd;
}

/* function: get_user_balance
 * description: get user's balance
 * input: 
 *    user_head: head pointer to UserList
 *    name: a char pointer to user's name
 * output:
 *    int: user's balance
 * return: 
 *    user's balance */
int get_user_balance(UserList *user_head, const char *name)
{
    UserData *p = get_user_data(user_head, name);
    if(p == NULL)
        return -1;
    return p->balance;
}

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
int change_balance(UserList *user_head, const char *name, int money)
{
    UserData *p = get_user_data(user_head, name);
    int res = p->balance + money;
    if(res < 0){
        return -1;
    }else{
        p->balance = res;
        return 0;
    }
}

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
int get_user_info(UserInfo *user_info, const char *name)
{
    char path[30] = USERDATAPATH;
    strcat(path, name);
    FILE *fp = fopen(path, "r+");
    if(fp == NULL){
        return -1;
    }else{
        fread(user_info, sizeof(UserInfo), 1, fp);
        fclose(fp);
        return 0;
    }
}

/* function: sort_user_by_name
 * description: sort user list by name
 * input:
 *    user_head: head pointer to UserList
 * output:
 *    NULL
 * return:
 *    NULL */
void sort_user_by_name(UserList *user_head)
{
    sort_node(user_head, user_head->next, user_head->pre, compare_name);
}

/* function: sort_user_by_balance
 * description: sort user list by balance
 * input:
 *    user_head: head pointer to UserList
 * output:
 *    NULL
 * return:
 *    NULL */
void sort_user_by_balance(UserList *user_head)
{
    sort_node(user_head, user_head->next, user_head->pre, compare_balance);
}




