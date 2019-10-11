#ifndef GET_PASSWD_H_
#define GET_PASSWD_H_

/* function: get_passwd
 * description: get the password from the terminal, while the 
 *    terminal displays '*', the maximum number of characters 
 *    is 19
 * input: 
 *    passwd: a pointer to 'password' variable
 * output: 
 *    NULL
 * return:
 *    NULL */
extern void get_passwd(char *passwd);

/* function: get_string
 * description: Used to read the string from the terminal, and store in the 
 *    locations pointed to by the arguments, and the maximum number of string
 *    is limited by the secend argument
 * input: 
 *	  string: a pointer to stored location
 *    n: limit the number of string
 * output:
 *    0: normal 
 *    -1: <ESC> or <ENTER> at first 
 * return: 
 *    called function state */
extern int get_string(char *string, int n);

#endif


