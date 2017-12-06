#include <stdio.h>
#include <termios.h>
#include <string.h>
#include "getch.c"
// #include </usr/lib/ncurses.h>
#define ENTER 10 //13
#define TAB 9
#define BKSP 127 //8

// char pwd[100];

void masked_password(char pwd[]){
	int i = 0;
	char ch;

	// printf("Enter your password. Hit ENTER to confirm.\n");
	// printf("Password:");

	while(1){
		ch = getch();	//get key
		// printf("%d\n",ch);
		if(ch == ENTER || ch == TAB){
			pwd[i] = '\n';
			pwd[i+1] = '\0';
			break;
		}else if(ch == BKSP){
			if(i > 0){
				i--;
				printf("\b \b");		//for backspace
			}
		}else{
			pwd[i++] = ch;
			printf("* \b");				//to replace password character with *
		}
	}//while ends here
	int l = strlen(pwd);
	// printf("\n\nPassword:%s\nLength:%d\n\n", pwd, l);
	// return pwd;
}//main() ends here