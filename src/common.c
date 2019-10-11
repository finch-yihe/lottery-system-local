#include "include/common.h"
#include "include/standard_input.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

/* function: window_adjust
 * description: adjust window
 * input:
 *    NULL
 * output:
 *    NULL
 * return:
 *    NULL */
void window_adjust(void)
{
    if(system("resize -s 34 64") != 0){
        printf("[ Lottery system ] %s [ Warn ] Failed to enable xterm, resize is not executable!\n", __TIME__);
        FLUSH;
    }else{
        return;
    }
}

/* function: print
 * description: print string in the middle
 * input:
 *    string: a pointer to a string
 * output:
 *    NULL
 * return:
 *    NULL */
void print(const char *string)
{
    int len = strlen(string);
    int i = 32-len/2;
    printf("\033[%dC%s\n", i, string);
    return;
}

/* function: set_welcome_title
 * description: set the color and welcome statement
 * intput:
 *    NULL
 * output:
 *    NULL
 * return: 
 *    NULL */
void set_welcome_title(void)
{
    extern char current_user[20];
    extern char welcome[70];
    if(strlen(current_user) == 0){
        DEFAULTCOLOR;
    }
    else if(!strcmp(current_user, ADMINNAME)){
        YELLOECOLOR;
    }else if(!strcmp(current_user, NOTARYNAME)){
        GREENCOLOR;
    }else{
        BLUECOLOR;
    }
    memset(welcome, 0, 70);
    strcat(welcome, "Welcome to use this system,");
    strcat(welcome, current_user);
    strcat(welcome, "!\0");
    return;
}

/* function: head_ui
 * description: show the title head of lottery system
 * input:
 *    string: a string to be used to show under the title label
 * output:
 *    NULL
 * return:
 *    NULL */
void head_ui(const char *message)
{
    system("clear");
    printf("\n");
    printf(" ██╗       ██████╗ ████████╗████████╗████████╗███████╗ ██╗   ██╗\n");
    printf(" ██║      ██╔═══██╗╚══██╔══╝╚══██╔══╝██╔═════╝██╔═══██╗╚██╗ ██╔╝\n");
    printf(" ██║      ██║   ██║   ██║      ██║   ███████╗ ███████╔╝ ╚████╔╝\n");
    printf(" ██║      ██║   ██║   ██║      ██║   ██╔════╝ ██╔═══██╗  ╚██╔╝\n");
    printf(" ████████╗╚██████╔╝   ██║      ██║   ████████╗██║   ██║   ██║\n");
    printf(" ╚═══════╝ ╚═════╝    ╚═╝      ╚═╝   ╚═══════╝╚═╝   ╚═╝   ╚═╝\n");
    printf("\n");
    print(message);
    printf("\n");
}

/* function: withdraw_ui
 * description: show a QR code to withdraw from user's balance, and
 *    my alipay collect QR code is showed here
 * input:
 *    NULL
 * output:
 *    NULL
 * return:
 *    NULL */
void withdraw_ui(void)
{
    extern char welcome[70];
	head_ui(welcome);
	print("Please scan the following qr code by alipay!\0");
    printf("\n");
	printf("\t      █████████████████████████████████████\n");
	printf("\t      ████ ▄▄▄▄▄ █▀▀ ██ ▄ ██ ▄▀█ ▄▄▄▄▄ ████\n");
	printf("\t      ████ █   █ █▄▀██▀██ █▄ ▄▄█ █   █ ████\n");
	printf("\t      ████ █▄▄▄█ █ ▄ █ ▄█   ▄▀▄█ █▄▄▄█ ████\n");
	printf("\t      ████▄▄▄▄▄▄▄█ █ ▀▄█ █▄▀ █ █▄▄▄▄▄▄▄████\n");
	printf("\t      ████▄▄▀ ▀█▄ █▀█  ▄▄█ █▀▄▀▀ ▄▄▀▄▄▀████\n");
	printf("\t      ████  ▀▄██▄█▄▀▀    ▀▀█▄▄█ ▄▄▄▄  █████\n");
	printf("\t      ████▄██▀  ▄▀█▀▄ █ █▄▄     ▄██▄█▄▄████\n");
	printf("\t      ████▀▀▄▀▀▄▄▀█▄▄ █ ▀█▄ ▄█▄██▄▀ ▄ ▄████\n");
	printf("\t      █████▄█▄██▄ ▀▄▀█ █▀▄▀▄ ▄▄▄▀██▀█▄▀████\n");
	printf("\t      ████▄█▀ █▀▄█▄▄█▄ ▄▀▀ ▀▄▀ ▀ ▀███  ████\n");
	printf("\t      ████▄███▄▄▄█  ▀▀▄ ▄█▀▀   ▄▄▄ █ ▀▀████\n");
	printf("\t      ████ ▄▄▄▄▄ █▄▄▀█▄▀█▀██ ▀ █▄█ ▀▀▄█████\n");
	printf("\t      ████ █   █ █▀ █▄█▄▀▄▄▄ ▀▄▄ ▄ ▀▀ █████\n");
	printf("\t      ████ █▄▄▄█ █▀█▄ ▀ ▄█▄  █ ▀██▄▄▄▀▄████\n");
	printf("\t      ████▄▄▄▄▄▄▄█▄▄▄███▄█▄▄▄█▄▄██▄██▄█████\n");
	printf("\t      █████████████████████████████████████\n");
	printf("\n");
    CONTINUE;
}

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
int get_choise()
{
    int cmd = 0;
    if(scanf("%d", &cmd) != 1){
	    FLUSH;
        return -1;
    }else{
	    FLUSH;
    	return cmd;
    }
}

/* function: identifyCode
 * description: generate identify code, and show the ui
 * input:
 *    NULL
 * output:
 *    0: identify success
 *    -1: identify failure
 * return:
 *    whether identify is successful */
int identifyCode(void)
{
    char array[100]="ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789";
    char system_code[5]="\0";
    char user_code[5]="\0";
    while(1){
        srand(time(NULL));
        system_code[0] = array[rand()%26];
        system_code[1] = array[rand()%26+26];
        system_code[2] = array[rand()%10+52];
        system_code[3] = array[rand()%10+52];
        system_code[4] = '\0';
        printf(" Verification code:%s\n", system_code);
        printf(" Please enter the verification code:");
        int res = get_string(user_code, 4); 
        if(res != 0){
            WARNING("Format error! Please input again.\0");
            BACK;BACK;BACK;BACK;BACK;BACK;
        }else{
            if(strcmp(user_code, system_code) != 0){
                WARNING("Verification code error, please input again!\0");
                BACK;BACK;BACK;BACK;BACK;BACK;
            }else{
                return 0;
            }
        }        
    }
}

/* function: input_name
 * description: be used to read name from standard input
 * input:
 *    name: a pointer to 'name'
 * output:
 *    char*: a pointer to 'name'
 * return:
 *    a first address to 'name' */
char* input_name(char *name)
{
    head_ui(VERSION);
    printf(" Please input your name:");
    int res = get_string(name, 19);
    if(res<0 || res >0){
        WARNING("Format error! Please input again.\0");
        return NULL;
    }else{
        return name;
    }
}

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
char* input_passwd(char *passwd, int status)
{
    if(status == 0){
        printf(" Please input your password:");
        char _passwd[VALID] = "\0";
        get_passwd(_passwd);
        printf(" Please input your confirmation password:");
        char _confirPasswd[VALID] = "\0";
        get_passwd(_confirPasswd);
        if(strcmp(_passwd, _confirPasswd) == 0){
            memcpy(passwd, _passwd, VALID);
            return passwd;
        }else{
            return NULL;
        }
    }else if(status == 1){
        printf(" Please input your password:");
        char _passwd[VALID] = "\0";
        get_passwd(_passwd);
        memcpy(passwd, _passwd, VALID);
        return passwd;
    }else if(status == 2){
        printf(" Please input your old passwprd:");
        char _passwd[VALID] = "\0";
        get_passwd(_passwd);
        if(strcmp(passwd, _passwd) != 0){
            WARNING("Incorrect password! Please input again.\0");
            return NULL;
        }
        while(1){
            printf(" Please input your new password:");
            get_passwd(_passwd);
            printf(" Please input your new password again:");
            char _confirPasswd[VALID] = "\0";
            get_passwd(_confirPasswd);
            if(strcmp(_passwd, _confirPasswd) == 0){
                if(strcmp(_passwd, passwd) == 0){
                    _WARNING("The new password is the same as the old one.\0", "Please enter it again!\0");
                    BACK;BACK;BACK;BACK;BACK;BACK;BACK;
                    continue;
                }
                memcpy(passwd, _passwd, VALID);
                return passwd;
            }else{
                WARNING("Password do not match! Please input again.\0");
                return NULL;
            } 
        }
    }
    return NULL;
}

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
void user_info_window_ui(const char *name, long balance, const char *phone, const char *idcode)
{
    print("*******************************\0");
    printf("\t\t * Name: %-19s   *\n", name);
    printf("\t\t * Balance: %-19ld*\n", balance);
    printf("\t\t * Phone: %-19s  *\n", phone);
    printf("\t\t * Id code: %-19s*\n", idcode);
    print("*******************************\0");
}
