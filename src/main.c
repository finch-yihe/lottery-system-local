#include "include/common.h"
#include "include/menu_ui.h"
#include "include/user_handler.h"
#include "include/lottery_handler.h"
#include "include/issue_handler.h"
#include "include/admin_ui.h"
#include "include/notary_ui.h"
#include <stdlib.h>
#include <stdio.h>


char current_user[VALID];
char welcome[70];

int main(void)
{
    window_adjust();
    UserList *user_list = NULL;
    LotteryList *lottery_list = NULL;
    IssueList *issue_list = NULL;
    if(user_list_initialize(&user_list)){
        free(user_list);
    }
    if(lottery_list_initialize(&lottery_list)){
        free(lottery_list);
    }
    if(issue_list_initialize(&issue_list)){
        free(issue_list);
    }
    int flag = 0, res = 0;
    while(!flag){
        int cmd = choose_role_ui();
        switch(cmd)
        {
            case 1:
                res = choose_admin_ui();
                if(res == 1){
                    admin_ui(user_list, issue_list);
                    break;
                }
                else if(res == 2){
                    notary_ui(user_list, lottery_list, issue_list);
                    break;
                }else{
                    break;
                } 
            case 2:
                login_or_register_ui(user_list, lottery_list, issue_list);
                break;
            case 0:
                flag = 1;
                break;
            default:
                WARNING("Format error! Please input again.\0");
                break;
        }
    }
    user_list_destory(user_list);
    lottery_list_destory(lottery_list);
    issue_list_destory(issue_list);
}
