#include "include/common.h"
#include "include/standard_input.h"
#include "include/menu_ui.h"
#include "include/user_handler.h"
#include "include/lottery_handler.h"
#include "include/user_ui.h"
#include "include/admin_ui.h"
#include "include/notary_ui.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>



/* function: admin_login
 * description: admin login GUI
 * input:
 *    NULL
 * output:
 *    0: success
 *    -1: format error
 *    1: name or passwd input error
 * return:
 *    called function state */
int admin_login()
{
    char name[20] = "\0";
    char passwd[20] = "\0";
    if(input_name(name)==NULL || input_passwd(passwd, 1)==NULL){
        return -1;
    }
    if(strcmp(name, ADMINNAME)!=0 || strcmp(passwd, ADMINPASSWD)!=0){
        return 1;
    }
    return 0;
}

/* function: notary_login
 * description: notary login GUI
 * input:
 *    NULL
 * output:
 *    0: success
 *    -1: format error
 *    1: name or passwd input error
 * return:
 *    called function state */
int notary_login()
{
    char name[20] = "\0";
    char passwd[20] = "\0";
    if(input_name(name)==NULL || input_passwd(passwd, 1)==NULL){
        return -1;
    }
    if(strcmp(name, NOTARYNAME)!=0 || strcmp(passwd, NOTARYPASSWD)!=0){
        return 1;
    }
    return 0;
}

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
int choose_role_ui(void)
{
    int flag = 0;
    while(!flag){
        extern char current_user[VALID];
        memset(current_user, 0, VALID);
        set_welcome_title();
        head_ui(VERSION);
        printf("\t\t1. login in as an admin\n");
        printf("\t\t2. login in as a user\n");
        printf("\t\t0. quit\n");
        printf("\n\t\tPlease input your choice:");
        int cmd = get_choise();
        switch(cmd){
            case 1:
                return 1;
            case 2:
                return 2;
            case 0:
                return 0;
            default:
                WARNING("Format error! Please input again.\0");
                break;
        }
    }
    return -1;
}

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
int choose_admin_ui(void)
{
    while(1){
        extern char current_user[VALID];
        memset(current_user, 0, VALID);
        set_welcome_title();
        head_ui(VERSION);
        printf("\t\t1. sign in as an system admin\n");
        printf("\t\t2. sign in as notary\n");
        printf("\t\t0. back\n");
        printf("\n\t\tPlease enter your choice:");
        int cmd = get_choise();
        switch(cmd)
        {
            case 1:
                {
                    int counter = 0;
                    int _flag = 0;
                    while(!_flag){
                        head_ui(VERSION);
                        switch(admin_login()){
                            case 0:
                                memset(current_user, 0, VALID);
                                strcpy(current_user, ADMINNAME);
                                return 1;
                            case 1:
                                counter++;
                                WARNING("Incorrect password! Please input again.\0");
                                break;
                            default:
                                WARNING("Format error! Please input again.\0");
                                break;
                        }
                        if(counter == 3){
                            return -1;
                        }
                    }
                    
                }
            case 2:
                {
                    int counter = 0;
                    int _flag = 0;
                    while(!_flag){
                        head_ui(VERSION);
                        switch(notary_login()){
                            case 0:
                                memset(current_user, 0, VALID);
                                strcpy(current_user, NOTARYNAME);
                                return 2;
                            case 1:
                                counter++;
                                WARNING("Incorrect password! Please input again.\0");
                                break;
                        }  
                        if(counter == 3){
                            return -1;
                        }
                    }
                }
            case 0:
                return 0;
                break;
            default:
                WARNING("Format error! Please input again.\0");
                break;
        }
    }
}


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
void login_or_register_ui(UserList *user_head, LotteryList *lottery_head, IssueList *issue_head)
{
    int flag = 0;
    while(!flag){
        extern char current_user[VALID];
        memset(current_user, 0, VALID);
        set_welcome_title();
        head_ui(VERSION);
        printf("\t\t1. sign in\n");
        printf("\t\t2. sign up\n");
        printf("\t\t0. back\n");
        printf("\n\t\tPlease enter your choice:");
        int cmd = get_choise();
        switch(cmd)
        {        
            case 1:
                {
                    int counter = 0;
                    int _flag = 0;
                    while(!_flag){
                        head_ui(VERSION);
                        switch(user_login(user_head)){
                            case 1:
                                WARNING("No such user! Please input again.\0");
                                counter++;
                                break;
                            case 2:
                                counter++;
                                WARNING("Incorrect password! Please input again.\0");
                                break;
                            case 3:
                                _flag = 1;
                                break;
                            case 0:
                                user_ui(user_head, lottery_head, issue_head);
                                _flag = 1;
                                break;
                        }
                        if(counter == 3){
                            head_ui(VERSION);
                            printf("\t\t    I'm so sorry for you!\n");
                            break;
                        }
                    }
                }
                break;
            case 2:
                {
                    int _flag = 0;
                    while(!_flag){
                        head_ui(VERSION);
                        switch(user_register(user_head, issue_head)){
                            case 1:
                                WARNING("User name already exists! Please input again.\0");
                                break;
                            case 2:
                                WARNING("Password do not match! Please input again.\0");
                                break;
                            case 3:
                                GLITTER("Register sucessfully!\0");
                                _flag = 1;
                                break;
                            case 0:
                                GLITTER("Register sucessfully! 10 RMB is sent to your wallet.\0");
                                _flag = 1;
                                break;
                        }
                    }
                }
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
