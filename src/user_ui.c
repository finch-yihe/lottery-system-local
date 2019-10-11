#include "include/user_ui.h"
#include "include/common.h"
#include "include/standard_input.h"
#include "include/user_handler.h"
#include "include/lottery_handler.h"
#include "include/issue_handler.h"
#include "include/game.h"
#include <string.h>
#include <stdio.h>
#include <time.h>
#include <stdlib.h>

/*function: show_personal_info
 * description: show personal info
 * input:
 *    user_head: head pointer to UserList
 *    name: a char pointer to user's name
 * output:
 *    NULL
 * return:
 *    NULL */
static void show_personal_info(UserList *user_head, const char *name)
{
    UserInfo user_info;
    memset(&user_info, 0, sizeof(UserInfo));
    get_user_info(&user_info, name);
    extern char welcome[70];
    head_ui(welcome);
	user_info_window_ui(name, get_user_balance(user_head, name), user_info.phone,user_info.idcode);
    printf("\n");
    CONTINUE;
}

/* function: modify_personal_info
 * description: modify personal information
 * input:
 *    name: a char pointer to user's name
 * output:
 *    NULL
 * return:
 *    NULL */
static void modify_personal_info(const char *name)
{
    extern char welcome[70];
    head_ui(welcome);
    char path[30] = USERDATAPATH;
    strcat(path, name);
    FILE *fp = fopen(path, "w+");
    UserInfo user_info;
    memset(&user_info, 0, sizeof(UserInfo));
    printf(" Please input your phohe:");
    while(get_string(user_info.phone, 11) != 0){
        WARNING("Format error! Please input again.\0");
        BACK;BACK;BACK;BACK;BACK;
        printf(" Please input your phohe:");
    }
    printf(" Please input your id code:");
    while(get_string(user_info.idcode, 18) != 0){
        WARNING("Format error! Please input again.\0");
        BACK;BACK;BACK;BACK;BACK;
        printf(" Please input your id code:");
    }
    fwrite(&user_info, sizeof(UserInfo), 1, fp);
    fclose(fp);
    printf("\n");
    CONTINUE;
    return;
}

/* function: change_passwd
 * description: change user's passwd
 * input:
 *    user_head: head pointer to UserList
 *    name: a char pointer to user's name
 * output:  
 *    NULL
 * return:
 *    NULL */
static void change_passwd(UserList *user_head, const char *name)
{
    UserData *p = get_user_data(user_head, name);
    int counter = 0;
    extern char welcome[70];
    while(1){
        head_ui(welcome);
        if(input_passwd(p->passwd, 2) == NULL){
            counter++;
        }else{
            REMIND("Succeed to change your password.\0");
            return;
        }
        if(counter == 3)
            return;
    }
}

/* function: top_up
 * description: show top up GUI
 * input:
 *    user_head: head pointer to UserList
 *    name: a char pointer to user's name
 * output:
 *    NULL
 * return:
 *    NULL */
static void top_up(UserList *user_head, const char *name)
{
    extern char welcome[70];
    while(1){
        head_ui(welcome);
        printf(" How much would you like to top-up:");
        int money = get_choise();
        if(money < 0){
            WARNING("Format error! Please input again.\0");
            continue;
        }else{
            change_balance(user_head, name, money);
            withdraw_ui();
            return;
        }
    }
}

/* function: withdraw
 * description: show withdraw GUI
 * input:
 *    user_head: head pointer to UserList
 *    name: a char pointer to user's name 
 * output:
 *    NULL
 * return:
 *    NULL */
static void withdraw(UserList *user_head, const char *name)
{
    extern char welcome[70];
    while(1){
        head_ui(welcome);
        printf(" How much would you like to withdraw:");
        int money = get_choise();
        if(money < 0){
            WARNING("Format error! Please input again.\0");
            return;
        }else{
            money = 0 - money;
            if(!change_balance(user_head, name, money)){
                withdraw_ui();
                return;
            }else{
                WARNING("Not enough balance!\0");
                continue;
            }
        }
    }
}

/* function: delete_user
 * description: delete user account GUI
 * input:
 *    user_head: head pointer to UserList
 *    name: a char pointer to user's name
 * output:
 *    0: success
 *    1: user choose cancel
 *    2: error
 * return:
 *    called function state */
static int delete_user(UserList *user_head, const char *name)
{
    char answer[1] = "\0";
    while(1){
        extern char current_user[VALID];
        extern char welcome[70];
        head_ui(welcome);
        printf(" Are you sure to delete your account(y/n):");
        get_string(answer, 1);
        if(answer[0] == 'y' || answer[0] == 'Y'){
            if(get_user_balance(user_head, name) != 0){
                WARNING("Please withdraw all your money!\0");
                return 2;
            }
            delete_node(get_user_node(user_head, name));
            char cmd[30] = "rm userdata/";
            strcat(cmd, current_user);
            system(cmd);
            return 0;
        }else if(answer[0] == 'n' || answer[0] == 'N'){
            return 1;
        }else{
            WARNING("Format error! Please input again.\0");
        }
    }
}

/* funtion: judge_number
 * description: judge whether number's format is right
 * input:
 *    n: the note of lottery
 *    number: lottery number
 * output:
 *    0: right
 *    -1: wrong
 * return:
 *    lottery number's format state */
static int judge_number(int n, int (*number)[7])
{
    for(int i=0; i<n; i++){
        for(int j=0; j<7; j++){
            if(*(*(number+i)+j)<1 || *(*(number+i)+j)>99)
                    return -1;
        }
    }
    return 0;
}

/* function: manual_enter_number
 * description: manual enter number GUI
 * input:
 *    user_head: head pointer to UserList
 *    issue_head: head pointer to IssueList
 *    number: a 2-D representing lottery number users buy
 *    lottery_prize: lottery prize
 *    balance: user's current balance in the system
 * output:
 *    u_short: the numbers of lottery user buy
 * return:
 *    the lottery buy number */
static u_short manual_enter_number(UserList *user_head, IssueList *issue_head, u_short (*number)[7], u_short lottery_prize, int balance)
{
    extern char welcome[70];
    extern char current_user[VALID];
    while(1){
        head_ui(welcome);
        int flag = 0;
        int _number[5][7] = {{0}};
        printf(" How many numbers would you like to buy:");
        int n = get_choise();
        if(n * lottery_prize > balance){
            WARNING("No enough money!\0");
            continue;
        }
        flag = 0;
        if(n < 1 || n > 5){
            WARNING("Format error! Please input again.\0");
            continue;
        }
        printf(" Please enter %d sets of lottery number one by one.\n", n);
        for(int i=0; !flag && i<n; i++){
            printf(" ");
            for(int j=0; !flag && j<7; j++){
                if(scanf(" %d", (*(_number+i)+j)) != 1){
                    flag = 1;
                    WARNING("Format error! Please input again.\0");
                    break;
                }
            }
            FLUSH;
            for(int j=0; !flag && j<7; j++){
                int temp = *(*(_number+i)+j);
                for(int k=j+1; !flag && k<7; k++){
                    if(temp == *(*(_number+i)+k)){
                        flag = 1;
                        WARNING("Format error! Please input again.\0");
                        break;
                    }
                }
            }
        }
        if(flag){
            continue;
        }
        if(!judge_number(n, _number)){
            for(int i=0; i<5; i++){
                for(int j=0; j<7; j++){
                    *(*(number+i)+j) = (u_short)(*(*(_number+i)+j));
                }
            }
            for(int i=0; i<5; i++)
                quick_sort(*(number+i));
            int money = 0 - n * lottery_prize;
            sold_ticket(issue_head, (u_long)(n * lottery_prize));
            change_balance(user_head, current_user, money);
            return (u_short)n;
        }else{
            FLUSH;
            _WARNING("Value range is [0, 99]!\0","Please input again!\0");
            continue;
        }
    }
}


/* function: machine_select_number
 * description: machine select number GUI
 * input:
 *    user_head: head pointer to UserList
 *    issue_head: head pointer to IssueList
 *    number: a 2-D representing lottery number users buy
 *    lottery_prize: lottery prize
 *    balance: user's current balance in the system
 * output:
 *    u_short: the numbers of lottery user buy
 * return:
 *    the lottery buy number */
static u_short machine_select_number(UserList *user_head, IssueList *issue_head, u_short (*number)[7], u_short lottery_prize, int balance)
{
    extern char welcome[70];
    extern char current_user[VALID];
    while(1){
        head_ui(welcome);
        printf(" How many numbers would you like to buy:");
        int n = get_choise();
        if(n < 0 || n > 5){
            WARNING("Format error! Please input again.\0");
            continue;
        }
        if(n * lottery_prize > balance){
            WARNING("No enough money!\0");
            continue;
        }
        srand(time(NULL));
        for(int i=0; i<n; i++){
            generate_random_number(*(number+i));
        }
        int money = 0 - n * lottery_prize;
        sold_ticket(issue_head, (u_long)(n * lottery_prize));
        change_balance(user_head, current_user, money);
        return (u_short)n;
    }
}

/* function: show_buy_number
 * description: show buy number user purchase
 * input:
 *    buy_number: the number of lottery users buy
 *    number: a 2-D array representing lottery number
 * output: 
 *    NULL
 * return:
 *    NULL */
static void show_buy_number(u_short buy_number, u_short (*number)[7])
{
    printf("\t\t********************************\n");
    for(int i=0; i<buy_number; i++){
        printf("\t\t*  %02d  %02d  %02d  %02d  %02d  %02d  \033[1;31;40m%02d\033[0;32;34m  *\n",
                *(*(number+i)+0), *(*(number+i)+1), *(*(number+i)+2), *(*(number+i)+3), 
                *(*(number+i)+4), *(*(number+i)+5), *(*(number+i)+6));  
    }
    printf("\t\t********************************\n");
}

/* function: buy_lottery_ui
 * description: buy lottery GUI
 * input:
 *    user_head: head pointer to UserList
 *    lottery_head: head pointer to LotteryList
 *    issue_head: head pointer to IssueList
 *    lottery_issue: the current lottery issue
 *    lottery_prizeL the current lottery prize
 * output:
 *    NULL
 * return:
 *    NULL */
static void buy_lottery_ui(UserList *user_head, LotteryList *lottery_head, IssueList *issue_head, u_int lottery_issue, u_short lottery_prize)
{
    int flag = 0;
    u_short number[5][7] = {{0}}; 
    u_short buy_number = 0;
    extern char current_user[VALID]; 
    int balance = get_user_balance(user_head, current_user);
    while(!flag){
        extern char welcome[70];
        head_ui(welcome);
        printf("\t\tCurrent issue: %u, ticket prize: %hu\n", ((IssueData*)(issue_head->pre->data.data))->lottery_issue, lottery_prize);
        printf("\t\t1. Manually enter\n");
        printf("\t\t2. Machine select\n");
        printf("\t\t0. quit\n");
        printf("\n\t\tPlease input your choice:");
        int cmd = get_choise();
        switch(cmd){
            case 1:
                buy_number = manual_enter_number(user_head, issue_head, number, lottery_prize, balance);
                head_ui(welcome);
                show_buy_number(buy_number, number);
                printf("\n");
                CONTINUE;
                flag = 1;
                break;
            case 2:
                buy_number = machine_select_number(user_head, issue_head, number, lottery_prize, balance);
                head_ui(welcome);
                show_buy_number(buy_number, number);
                printf("\n");
                CONTINUE;
                flag = 1;
                break;
            case 0:
                return;
            default:
                WARNING("Format error! Please input again.\0");
                break;
        }
    }
    insert_lottery(lottery_head, number, buy_number, current_user, lottery_issue);
}

/* function: show_lottery_info
 * description: show lottery information
 * input:
 *    data: a LotteryData pointer 
 * output:
 *    NULL
 * return:
 *    NULL */
static void show_lottery_info(LotteryData *data)
{
    int counter = 0;
    printf("\t\t********************************\n");
    printf("\t\t* id: %-24ld *\n", data->id);
    printf("\t\t* issue number: %-14d *\n", data->lottery_issue);
    printf("\t\t* name: %-22s *\n", data->name);
    if(data->state[0] == 0)
        printf("\t\t* state: unpublished           *\n");
    else{
        printf("\t\t* prize: ");
        for(int i=0; i<5; i++){
            if(*(data->state+i)>0 && *(data->state+i)<7){
                printf("%-2d ", *(data->state+i));
                counter++;
            }
        }
        if(counter == 0)
            printf("                     ");
        else{
            for(int i=0; i<21-3*counter; i++)
                printf(" ");
        }
        printf(" *\n");
    }
    if(data->lucky_number[0] == 0)
        printf("\t\t* Lucky Number: None           *\n");
    else{
        printf("\t\t* Lucky Number:                *\n\t\t*    ");
        for(int i=0; i<6; i++){
           printf(" %02d", *(data->lucky_number+i));
        }
        REDCOLOR;
        printf(" %02d", *(data->lucky_number+6));
        BLUECOLOR;
        printf("     *\n");
    }
    show_buy_number(data->buy_number, data->user_number);
    printf("\t\t* reward: %-20ld *\n", data->reward);
    printf("\t\t********************************\n\n");
}

/* function: show_purchase_history
 * description: show purchase history
 * input:
 *    head: head pointer to LotteryList
 *    name: a char pointer to user's name
 * out:
 *    -1: none lottery has been issued
 *    0: success
 * return:
 *    called function state */
int show_purchase_history(LotteryList *head, const char *name)
{
    extern char welcome[70];
    head_ui(welcome);
    if(head==NULL || head->next==head){
        WARNING("None lottery has been issued!\0");
        return -1;
    }
    LotteryList *p = head->next;
    LotteryData *q = NULL;
    int flag = 0;
    while(p != head){
        q = (LotteryData*)(p->data.data);
        if(!strcmp(q->name, name)){
            show_lottery_info(q);
            flag = 1;
        }
        p = p->next;
    }
    CONTINUE;
    if(!flag){
        WARNING("None purchase history!\0");
    }
    return 0;
}

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
void user_ui(UserList *user_head, LotteryList *lottery_head, IssueList *issue_head)
{
    set_welcome_title();
    extern char welcome[70];
    extern char current_user[VALID];
    int flag = 0;
    while(!flag){
	    head_ui(welcome);
        printf("\t\t1. buy a lottery ticket\n");
        printf("\t\t2. show personal information\n");
        printf("\t\t3. update personal information\n");
        printf("\t\t4. show purchase history\n");
        printf("\t\t5. change the password\n");
        printf("\t\t6. top-up\n");
        printf("\t\t7. withdraw\n");
        printf("\t\t8. game\n");
        printf("\t\t9. delete account\n");
        printf("\t\t0. back\n");
        printf("\n\t\tPlease input your choice:");
        int cmd = get_choise();
        switch(cmd){
            case 1:
                if(get_issue_state(issue_head) != 0){
                    WARNING("No available lottery!\0");
                    break;
                }
                if(get_lottery_prize(issue_head) > get_user_balance(user_head, current_user)){
                    WARNING("No enough balance!\0");
                    break;
                }
                buy_lottery_ui(user_head, lottery_head, issue_head, get_issue(issue_head), get_lottery_prize(issue_head));
                break;
            case 2:
                show_personal_info(user_head, current_user);
                break;
            case 3:
                modify_personal_info(current_user);
                break;
            case 4:
                show_purchase_history(lottery_head, current_user);
                break;
            case 5:
                change_passwd(user_head, current_user);
                break;
            case 6:
                top_up(user_head, current_user);
                break;
            case 7:
                withdraw(user_head, current_user);
                break;
            case 8:
                game();
                break;
            case 9:
                if(delete_user(user_head, current_user) == 0){
                    flag = 1;
                    break;
                }else
                    break;
            case 0:
                flag = 1;
                break;
            default:
                WARNING("Format error! Please input again.\0");
                break;
        }
    }
    return;
}
