#ifndef COMMON_H_
#define COMMON_H_


#define VALID 20
#define PHONELEN 11
#define IDCODELEN 18
#define STARTCAPITAL 1000000

#define VERSION "version : 1.0.0-dev    by : YouthFaith\0"
#define ADMIN "Welcome to lottery system, administer!\0"
#define NOTARY "Welcome to lottery system, notary!\0"

#define USERLISTPATH "data/user_list.bin"
#define LOTTERYPATH "data/lottery_list.bin"
#define ISSUEPATH "data/issue_list.bin"

#define USERDATAPATH "userdata/"

#define LOTTERY_BIT 5
#define NUMBERRANGE rand()%9+1

#define SIXTHBONUS 5
#define FIFTHBONUS 10
#define FOURTHBONUS 200
#define THIRDBONUS 3000
#define PROPORTION_2 0.2
#define PROPORTION_1 0.5

#define DEFAULTCOLOR printf("\033[0m") 
#define REDCOLOR printf("\033[1;31;40m")
#define YELLOECOLOR printf("\033[1;33m")
#define BLUECOLOR printf("\033[0;32;34m")
#define GREENCOLOR printf("\033[0;32;32m")
#define GLITTERCOLOR printf("\e[5m")

#define BACK printf("\033[1A\033[K")
#define ENTER printf("\n");
#define FLUSH {char c = 0;  while((c = getchar()) != '\n' && c != EOF);}
#define CONTINUE print("Press any key to continue!\0");FLUSH

#define REMIND(x) ENTER;print(x);CONTINUE
#define WARNING(x) REDCOLOR;ENTER;print(x);CONTINUE;set_welcome_title()
#define _WARNING(x,y) REDCOLOR;ENTER;print(x);print(y);CONTINUE;set_welcome_title()
#define GLITTER(x) GLITTERCOLOR;ENTER;print(x);CONTINUE;set_welcome_title()

#define NOTARYNAME "notary"
#define NOTARYPASSWD "123456"

#define ADMINNAME "admin"
#define ADMINPASSWD "123456"

typedef unsigned short u_short;
typedef unsigned int u_int;
typedef unsigned long u_long;

/* function: window_adjust
 * description: adjust window
 * input:
 *    NULL
 * output:
 *    NULL
 * return:
 *    NULL */
extern void window_adjust(void);

/* function: head_ui
 * description: show the title head of lottery system
 * input:
 *    string: a string to be used to show under the title label
 * output:
 *    NULL
 * return:
 *    NULL */
extern void head_ui(const char *string);

/* function: withdraw_ui
 * description: show a QR code to withdraw from user's balance, and
 *    my alipay collect QR code is showed here
 * input:
 *    NULL
 * output:
 *    NULL
 * return:
 *    NULL */
extern void withdraw_ui(void);

/* function: get_choise
 * description: read a integer number from standard input and check
 *    whether the character input is a integer or not
 * input:
 *    NULL
 * output:
 *    0: succeed to read an integer number
 *    -1: error occurs
 * return:
 *    called funtion state */
extern int get_choise(void);

/* function: input_name
 * description: be used to read name from standard input
 * input:
 *    name: a pointer to 'name'
 * output:
 *    char*: a pointer to 'name'
 * return:
 *    a first address to 'name' */
extern char* input_name(char *name);

/*function: input_passwd
 * description: be used to read password from standard input,
 *    state 1 is used to register, 2 is used to login and 3 is
 *    used to change password
 * input:
 *    passwd: a pointer to 'password'
 *    state: function choise
 * output:
 *    char*: a pointer to 'password'
 * return: 
 *    a first address to 'password' */
extern char* input_passwd(char *passwd, int state);

/* function: print
 * description: print string in the middle
 * input:
 *    string: a pointer to a string
 * output:
 *    NULL
 * return:
 *    NULL */
extern void print(const char *string);

/* function: user_info_window_ui
 * description: show user's personal information
 * input:
 *    name: user's name
 *    balane: user's balance
 *    phone: user's phone
 *    idcode: user's idcode
 * output:
 *    NULL
 * return:
 *    NULL */
extern void user_info_window_ui(const char *name , long balance, const char *phone, const char *idcode);

/* function: set_welcome_title
 * description: set the color and welcome statement
 * intput:
 *    NULL
 * output:
 *    NULL
 * return: 
 *    NULL */
extern void set_welcome_title(void);

/* function: identifyCode
 * description: generate identify code, and show the ui
 * input:
 *    NULL
 * output:
 *    0: identify success
 *    -1: identify failure
 * return:
 *    whether identify is successful */
extern int identifyCode(void);

#endif
