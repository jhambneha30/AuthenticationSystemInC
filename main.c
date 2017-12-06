#include <stdio.h>
#include "passwd.h"
#include "password_field.c"
#define NAME_LENGTH 50
#define PW_LENGTH 30


int main(int argc, char *argv[])
{
	// Handle options using getopt
	int option;
	char username[NAME_LENGTH];
    char password[PW_LENGTH];
	while ((option = getopt(argc, argv,"ar")) != -1) {
        switch (option) {
            case 'r' : printf("Enter username: ");
            	fgets(username,NAME_LENGTH,stdin);
            	printf("Enter password. Hit ENTER to confirm.\n");
                masked_password(password); 

            	int res = register_user(username, password);
                break;
            case 'a' : 
                printf("Enter username: ");
                fgets(username,NAME_LENGTH,stdin);
                printf("Enter password: Hit ENTER to confirm.\n ");
                masked_password(password); 
                // fgets(password,PW_LENGTH,stdin);
                int auth_res = auth_user(username, password);
                break;
            default: printf("Enter a valid flag!");
        }
    }
	//
	// Process aut/reg
	// exit cleanly if all was well
	// else exit with a non-0 return val
	return 0;
}
