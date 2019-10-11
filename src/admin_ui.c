#include "include/common.h"
#include "include/admin_ui.h"
#include "include/issue_handler.h"
#include "include/user_handler.h"
#include "include/standard_input.h"
#include <stdio.h>
#include <string.h>

/* function: issue_lottery_ui
 * description: the gui interface to issue lottery
 * input:
 *    issue_head: a pointer to IssueList
 * output:
 *    NULL
 * return:
 *    NULL */
void issue_lottery_ui(IssueList *head)
{
    head_ui(VERSION);
    if(get_issue_state(head) == 0){
        _WARNING("The last lottery ticket hasn't been drawn yet.\0", "Please contact the notary!\0");
        return;
    }
    printf(" How much a ticket would you like to issue:");
    int prize = 0;
    while(1){
        prize = get_choise();
        if(prize > 0){
            break;
        }else{
            WARNING("Format error! Please input again.\0");
            BACK;BACK;BACK;BACK;
        }
    }
    issue_lottery(head, (u_short)prize);
    REMIND("Issue successfully!\0"); 
    return;
}

/* function: search_user_by_name_ui
 * description: the gui interface to search user by name
 * input:
 *    user_head: a pointer to UserList
 * output:
 *    NULL
 * return:
 *    NULL */
void search_user_by_name_ui(UserList *head)
{
    char name[VALID] = "\0";
    while(1){
        head_ui(ADMIN);
        printf(" Please enter the name you want to search:");
        if(!get_string(name, 19)){
            break;
        }
    }
    UserData *user_data = NULL;
    user_data = get_user_data(head, name);
    if(user_data == NULL){
        WARNING("No such user!\0");
    }else{
        UserInfo user_info;
        memset(&user_info, 0, sizeof(UserInfo));
        if(get_user_info(&user_info, name)){
            WARNING(" Please contact the developer by 18752116785!\0");
        }else{
            printf("\n");
            user_info_window_ui(name, user_data->balance, user_info.phone, user_info.idcode);
            printf("\n");
            CONTINUE;
        }
    }
}


/* function: search_user_by_balance_ui
 * description: the gui interface to search user by balance
 * input:
 *    user_head: a pointer to UserList
 * output:
 *    NULL
 * return:
 *    NULL */
void search_user_by_balance_ui(UserList *head)
{
    int start=0, end=0;
    while(1){
        head_ui(ADMIN);
        printf(" Please enter the interval you want to search.\n");
        printf(" What is the minimum balance interval:");
        start = get_choise();
        if(start < 0){
            WARNING("Please input a integer!\0");
            continue;
        }
        printf(" What is the maximum balance interval:");
        end = get_choise();
        if(end < 0){
            WARNING("Please input a integer!\0");
            continue;
        }
        if(start > end){
            WARNING("Format error!\0");
            continue;
        }
        break;
    }
    UserList *p = head->next;
    UserData *q = NULL;
    int flag = 0;
    head_ui(ADMIN);
    while(p != head){
        q = (UserData*)(p->data.data);
        int balance = q->balance;
        char name[20] = "\0";
        strcpy(name, q->name);
        if(balance>=start && balance<=end){
            flag = 1;
            UserInfo user_info;
            memset(&user_info, 0, sizeof(UserInfo));
            if(get_user_info(&user_info, name)){
                WARNING(" Please contact the developer by 18752116785!\0");
            }else{
                user_info_window_ui(name, balance, user_info.phone, user_info.idcode);
                printf("\n");
            }
        }
        p = p->next;
    }
    if(!flag){
        WARNING("No such user!\0");
        return;
    }
    CONTINUE;
}

/* function: sort_account_ui
 * description: the gui interface to sort account
 * input:
 *    user_head: a pointer to UserList
 * output:
 *    NULL
 * return:
 *    NULL */
void search_account_ui(UserList *head)
{
    if(head==NULL || head==head->next){
        WARNING("None users now!\0");
        return;
    }
    int flag = 0;
    while(!flag){
        head_ui(ADMIN);
        printf("\t\t1. search user by name\n");
        printf("\t\t2. search user by balance\n");
        printf("\t\t0. back");
        printf("\n\t\tPlease enter your choice:");
        int cmd = get_choise();
        switch(cmd)
        {
            case 1:
                search_user_by_name_ui(head);
                break;
            case 2:
                search_user_by_balance_ui(head);
                break;
            case 0:
                flag = 1;
                break;
            default:
                WARNING("Format error! Please input again.\0");
                break;
        }
    }
}

/* function: show_all_user_ui
 * description: the gui interface to show all user's information
 * input:
 *    user_head: a pointer to UserList
 * output:
 *    NULL
 * return:
 *    NULL */
void show_all_user_ui(UserList *head)
{
    head_ui(ADMIN);
    UserList *p = head->next;
    while(p != head){
        long balance = ((UserData*)(p->data.data))->balance;
        char name[20] = "\0";
        strcpy(name, ((UserData*)(p->data.data))->name);
        UserInfo user_info;
        memset(&user_info, 0, sizeof(UserInfo));
        if(get_user_info(&user_info, name)){
            WARNING(" Please contact the developer by 18752116785!\0");
            return;
        }else{
            user_info_window_ui(name, balance, user_info.phone, user_info.idcode);
            printf("\n");
        }
        p = p->next;
    }
    CONTINUE;
}

/* function: sort_account_ui
 * description: the gui interface to sort account
 * input:
 *    user_head: a pointer to UserList
 * output:
 *    NULL
 * return:
 *    NULL */
void sort_account_ui(UserList *user_head)
{
    if(user_head==NULL || user_head==user_head->next){
        WARNING("None users now!\0");
        return;
    }
    int flag = 0;
    while(!flag){
        head_ui(ADMIN);
        printf("\t\t1. sort user by name\n");
        printf("\t\t2. sort user by balance\n");
        printf("\t\t3. show all user's information\n");
        printf("\t\t0. back");
        printf("\n\t\tPlease enter your choice:");
        int cmd = get_choise();
        switch(cmd)
        {
            case 1:
                sort_user_by_name(user_head);
                show_all_user_ui(user_head);
                break;
            case 2:
                sort_user_by_balance(user_head);
                show_all_user_ui(user_head);
                break;
            case 3:
                show_all_user_ui(user_head);
                break;
            case 0:
                flag = 1;
                break;
            default:
                WARNING("Format error! Please input again.\0");
                break;
        }
    }
}
    
/* function: admin_ui
 * description: the gui interface for admin
 * input:
 *    user_head: a pointer to UserList
 *    issue_head: a pointer to IssueList
 * output:
 *    NULL
 * return:
 *    NULL */
void admin_ui(UserList *user_list, IssueList *issue_list)
{
    int flag = 0;
    while(!flag){
        set_welcome_title();
        head_ui(ADMIN);
        printf("\t\t1. issue the lottery\n");
        printf("\t\t2. search account\n");
        printf("\t\t3. sort account\n");
        printf("\t\t0. back");
        printf("\n\t\tPlease enter your choice:");
        int cmd = get_choise();
        switch(cmd)
        {
            case 1:
                issue_lottery_ui(issue_list);
                break;
            case 2:
                search_account_ui(user_list);
                break;
            case 3:
                sort_account_ui(user_list);
                break;
            case 0:
                flag = 1;
                break;
            default:
                WARNING("Format error! Please input again.\0");
                break;
        }
    }
}
