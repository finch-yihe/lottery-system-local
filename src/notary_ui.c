#include "include/notary_ui.h"
#include "include/common.h"
#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <string.h>

/* function: is_run_lottery
 * description: judge whether notary can run the lottery 
 * input:
 *    head: head pointer to IssueList
 *    prize_pool: a pointer to prize pool
 * output:
 *    0: can
 *    -1: not can
 * return:
 *    whether can run lottery */
static int is_run_lottery(IssueList *head)
{
    if(head->next==head || head==NULL)
        return -1;
    if(((IssueData*)(head->pre->data.data))->state == 1)
        return -1;
    else{
        return 0;
    }
}

/* function: get_prize_level
 * description: get prize level
 * input: 
 *    data: a LotteryData pointer 
 *    number: lucky number
 * output:
 *    1: get at least one prize
 *    0: none prize
 * return:
 *    whether get prizes */
static int get_prize_level(LotteryData *data, u_short *number)
{
    int flag = 0;
    for(int i=0; i<data->buy_number; i++){
        int counter = 0, state = 0;
        for(int j=0; j<6; j++){
            for(int k=0; k<6; k++){
                if(*(number+k) > *(*((data->user_number)+i)+j))
                    break;
                if(*(number+k) == *(*((data->user_number)+i)+j))
                    counter++;
            }
        }
        if(*(*((data->user_number)+i)+6) == *(number+6))
            state = 1;
        else if(counter+state < 2)
            *(data->state+i) = 7;
        else if(counter+state>1 && counter+state<4)
            *(data->state+i) = 6;
        else if(counter+state == 4)
            *(data->state+i) = 5;
        else if(counter+state == 5)
            *(data->state+i) = 4;
        else if(counter==5 && state==1)
            *(data->state+i) = 3;
        else if(counter==6 && state==0)
            *(data->state+i) = 2;
        else
            *(data->state+i) = 1;
        if(counter+state>0)
            flag = 1;
    }
    return flag; 
}

/* function: run_lottery
 * description: run the lottery
 * input:
 *    lottery_head: head pointer to LotteryList
 *    issue_head: head pointer to IssueList
 *    winner_number: a 2-D array, the first is prize number and the second is reward 
 * output:
 *    NULL
 * return:
 *    NULL */
void run_lottery(LotteryList *lottery_head, IssueList *issue_head, u_long (*winner_number)[6])
{
    u_short lucky_number[7] = {0};
    srand(time(NULL));
    generate_random_number(lucky_number);
    memcpy(((IssueData*)(issue_head->pre->data.data))->lucky_number, lucky_number, 7 * sizeof(u_short));
    ((IssueData*)(issue_head->pre->data.data))->state = 1;
    LotteryList *p = lottery_head->next;
    LotteryData *q = NULL;
    while(((LotteryData*)(p->data.data))->lottery_issue != get_issue(issue_head)){
        p = p->next;
    }
    while(p != lottery_head){
        q = (LotteryData*)(p->data.data);
        memcpy(q->lucky_number, lucky_number, sizeof(lucky_number));
        if(get_prize_level(q, lucky_number)){
            int n = q->buy_number;
            for(int i=0; i<n; i++){
                if(*(q->state+i) == 7)
                    continue;
                else{
                    (*(*(winner_number)+(*(q->state+i))-1))++;
                }
            }
        }
        p = p->next;
    }
}

/* function: divide_money
 * description: divide money
 * input:
 *    user_head: head pointer to UserList
 *    lottery_head: head pointer to LotteryList
 *    prize_pool: a pointer to prize pool
 *    winner_number: a 2-D array, and the first is prize number, the second is prize reward
 * output:
 *    NULL
 * return:
 *    NULL */
int divide_money(UserList *user_head, LotteryList *lottery_head, IssueList *issue_head, u_long (*winner_number)[6])
{
    u_long *prize_pool = &(((IssueData*)(issue_head->pre->data.data))->prize_pool);
    u_long first_prize = (u_long)((*prize_pool) * PROPORTION_1);
    u_long second_prize = (u_long)((*prize_pool) * PROPORTION_2);
    u_long prize_money[6] = {first_prize, second_prize, THIRDBONUS, FOURTHBONUS, FIFTHBONUS, SIXTHBONUS};
    LotteryList *p = lottery_head->next;
    LotteryData *q = NULL;
    while(((LotteryData*)(p->data.data))->lottery_issue != get_issue(issue_head)){
        p = p->next;
    }
    while(p != lottery_head){
        q = (LotteryData*)(p->data.data);
        int n = q->buy_number;
        for(int i=0; i<n; i++){
            int flag = *(q->state+i);
            if(flag>6 || flag<1){
                continue;
            }else{
                if(*prize_pool >= prize_money[flag-1]){
                    *prize_pool -= prize_money[flag-1];
                }else{
                    return -1;
                }
                q->reward += prize_money[flag-1];
                (*(*(winner_number+1)+flag - 1)) += prize_money[flag-1];
                change_balance(user_head, q->name, prize_money[flag-1]);
            }
        }
        p = p->next;
    }
    return 0;
}

/* function: show_reward_users_info
 * description: user reward GUI
 * intput:
 *    winner_number: a 2-D array, and the first is prize number, the second is prize reward
 * output: 
 *    NULL
 * return:
 *    NULL */
void show_reward_users_info(u_long (*winner_number)[6])
{
    head_ui(NOTARY);
    print("***********first prize***********\0");
    if(winner_number[0][0] == 0){
        print("None!");
        printf("\n");
    }else{
        printf("\t\t    number: %-4ld prize: %-7ld \n", winner_number[0][0], winner_number[1][0]);
        printf("\n");
    }
    print("**********second  prize**********\0");
    if(winner_number[0][1] == 0){
        print("None!");
        printf("\n");
    }else{
        printf("\t\t    number: %-4ld prize: %-7ld \n", winner_number[0][1], winner_number[1][1]);
        printf("\n");
    }
    print("***********third prize***********\0");
    if(winner_number[0][2] == 0){
        print("None!");
        printf("\n");
    }else{
        printf("\t\t    number: %-4ld prize: %-7ld \n", winner_number[0][2], winner_number[1][2]);
        printf("\n");
    }
    print("**********fourth  prize**********\0");
    if(winner_number[0][3] == 0){
        print("None!");
        printf("\n");
    }else{
        printf("\t\t    number: %-4ld prize: %-7ld \n", winner_number[0][3], winner_number[1][3]);
        printf("\n");
    }
    print("***********fifth prize***********\0");
    if(winner_number[0][4] == 0){
        print("None!");
        printf("\n");
    }else{
        printf("\t\t    number: %-4ld prize: %-7ld \n", winner_number[0][4], winner_number[1][4]);
        printf("\n");
    }
    print("***********sixth prize***********\0");
    if(winner_number[0][5] == 0){
        print("None!");
        printf("\n");
    }else{
        printf("\t\t    number: %-4ld prize: %-7ld \n", winner_number[0][5], winner_number[1][5]);
        printf("\n");
    }
    printf("\n");
    CONTINUE;
}

/* function: run_lottery_ui
 * description: run lottery GUI
 * input:
 *    user_head: head pointer to UserList
 *    lottery_head: head pointer to LotteryList
 *    issue_head: head pointer to IssueList
 * output:
 *    NULL
 * return:
 *    NULL */
void run_lottery_ui(UserList *user_head, LotteryList *lottery_head, IssueList *issue_head)
{
    u_long winner_number[2][6] = {{0}};
    memset(winner_number, 0, 12 * sizeof(u_long));
    if(is_run_lottery(issue_head) < 0){
        WARNING("No lottery is issued!\0");
    }else{
        run_lottery(lottery_head, issue_head, winner_number);
        if(divide_money(user_head, lottery_head, issue_head, winner_number) == -1){
            WARNING("No enough prize!\0");
            return;
        }
        show_reward_users_info(winner_number);
    }
}

/* function: show_issue_history
 * description: show issue history
 * input:
 *    head: head pointer to IssueList
 * output:
 *    NULL
 * return:
 *    NULL */
static void show_issue_history(IssueList *head)
{
    if(head==NULL || head==head->next){
        WARNING("None lottery has been issued!\0");
        return;
    }
    extern char welcome[70];
    head_ui(welcome);
    IssueList *p = head->next;
    IssueData *q = NULL;
    while(p != head){
        q = (IssueData*)(p->data.data);
        printf("\t\t********************************\n");
        printf("\t\t* issue number: %-14d *\n", q->lottery_issue);
        if(q->state == 0)
            printf("\t\t* state: unpublished           *\n");
        else{
            printf("\t\t* state: published             *\n");
        }
        if(q->lucky_number[0] == 0)
            printf("\t\t* Lucky Number: None           *\n");
        else{
            printf("\t\t* Lucky Number:                *\n\t\t*    ");
            for(int i=0; i<6; i++){
                printf(" %02d", *(q->lucky_number+i));
            }
            REDCOLOR;
            printf(" %02d", *(q->lucky_number+6));
            GREENCOLOR;
            printf("     *\n");
        }
        printf("\t\t* Ticket Prize: %-14d *\n", q->lottery_prize);
        printf("\t\t* Sold Number: %-15ld *\n", q->sold_number);
        printf("\t\t* Prize Pool: %-16ld *\n", q->prize_pool);
        printf("\t\t********************************\n\n");
        p = p->next;
    }
    CONTINUE;
}

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
void notary_ui(UserList *user_list, LotteryList *lottery_list, IssueList *issue_list)
{
    int flag = 0;
    while(!flag){
        set_welcome_title();
        head_ui(NOTARY);
        printf("\t\t1. run the lottery\n");
        printf("\t\t2. show historical release record\n");
        printf("\t\t0. back");
        printf("\n\t\tPlease enter your choice:");
        int cmd = get_choise();
        switch(cmd)
        {
            case 1:
                run_lottery_ui(user_list, lottery_list, issue_list);
                break;
            case 2:
                show_issue_history(issue_list);
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
