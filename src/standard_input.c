#include "include/standard_input.h"
#include <stdio.h>  
#include <string.h>  
#include <unistd.h>  
#include <assert.h>
# include<termios.h>  

static int getch()  
{  
	int c=0;  
	struct termios org_opts, new_opts;  
	int res=0;  
	
	res=tcgetattr(STDIN_FILENO, &org_opts);  
    assert(res==0);
    memcpy(&new_opts, &org_opts, sizeof(new_opts));  
	new_opts.c_lflag &= ~(ICANON | ECHO | ECHOE | ECHOK | ECHONL | ECHOPRT | ECHOKE | ICRNL);  
	tcsetattr(STDIN_FILENO, TCSANOW, &new_opts);  
	c=getchar();  
	res=tcsetattr(STDIN_FILENO, TCSANOW, &org_opts);  
    assert(res==0);
	return c;  
}  

/* function: get_passwd
 * description: get the password from the terminal, while the 
 *    terminal displays '*', the maximum number of characters 
 *    is 19.
 * input: 
 *    passwd: a pointer to 'password' variable
 * output: 
 *    NULL
 * return:
 *    NULL */
void get_passwd(char *pcPWD)
{
    int ch=0;
    int i=0;
    for(i=0; i<20;){
        ch=getch();
        if(ch == -1){
            continue;
        }
        if((ch==127 || ch==8) && i>0){
            putchar('\b');
            putchar(' ');
            putchar('\b');	
            i--;		
        }else if(ch==10 || ch==13){
            pcPWD[i]='\0';
            putchar('\n');
            return;
        }else if(i==0 && (ch==127 || ch==8)){
            printf("\a");
        }else if(i < 19){
            pcPWD[i]=(char)ch;
            putchar('*');
            i++;
        }else{
            printf("\a");				        
        }
    }
}

/* function: get_string
 * description: Used to read the string from the terminal, and store in the 
 *    locations pointed to by the arguments, and the maximum number of string
 *    is limited by the secend argument.
 * input: 
 *	  string: a pointer to stored location
 *    n: limit the number of string
 * output:
 *    0: normal 
 *    -1: <ESC> or <ENTER> at first 
 * return: 
 *    called function state */
int get_string(char *code, int n)
{
    int ch=0;
    int i=0;
    for(i=0; i<n+1;){
        ch=getch();
        if(ch==-1){
            continue;
        }
        if((ch==27 || ch==10 || ch==13) && i == 0){
            printf("\n");
            return -1;
        }
        if((ch==127 || ch==8) && i>0){
            putchar('\b');
            putchar(' ');
            putchar('\b');	
            i--;		
        }else if(ch==10 || ch==13){
            code[i]='\0';
            putchar('\n');
            return 0;
        }else if(i==0 && (ch==127 || ch==8)){
            printf("\a");
        }else if(i < n){
            code[i]=(char)ch;
            putchar(ch);
            i++;
        }else{
            printf("\a");				        
        }
    }
    return 0;
}
