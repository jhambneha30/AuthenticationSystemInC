#include "passwd.h"
#include <openssl/sha.h>
#include "unistd.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

// Create SHA256 hash for password using OpenSSL functions

bool CreateSha256Hash(void* input, unsigned long length, unsigned char* md, char *buf)
{
    SHA256_CTX context;
    
    if(!SHA256_Init(&context))
        return false;

    if(!SHA256_Update(&context, (unsigned char*)input, length))
        return false;

    if(!SHA256_Final(md, &context))
        return false;
    int i;
    for (i=0; i < SHA_DIGEST_LENGTH; i++) {
        sprintf((char*)&(buf[i*2]), "%02x", md[i]);
    }
    // int buf_len = strlen(buf);
    // buf[buf_len] = '\0';
    // printf("hashed: %s\n", buf);
    return true;
}


const char* getfield(char* line, int num)
{
    const char* tok;
    for (tok = strtok(line, ":");
            tok && *tok;
            tok = strtok(NULL, ";\n"))
    {
        if (!--num)
            return tok;
    }
    return NULL;
}

static int is_registered(char *uname) {
	// Open your passwd storage file
	// Find if the User is present
	FILE *stream;
	// printf("-------------------inside 2");
	stream = fopen("pw_store.txt", "r");
	char line[1024];
	while (fgets(line, 1024, stream)) 
    {
        char* tmp = strdup(line);
        // printf("Field 1 would be un: %s\n", getfield(tmp, 1));
        if(strcmp(getfield(tmp, 1), uname) == 0) {
        	fclose(stream);
        	return 1;
        }
        	
        // NOTE strtok clobbers tmp
        free(tmp);
    }
	// return 1 if found
	// else return 0
	fclose(stream);
	return 0;
}


int register_user(char *uname, char *passwd) {
	FILE *fptr;
	char fname[25] = "pw_store.txt";
	char * line = NULL;
    size_t len = 0;
    // printf("uname: %s\n", uname);
    // printf("passwd: %s\n", passwd);
    unsigned char hashed[SHA256_DIGEST_LENGTH]; //32 bytes
    char hashed_buf[SHA_DIGEST_LENGTH*2];
    memset(hashed_buf, 0x0, SHA_DIGEST_LENGTH*2);
    int pw_len = strlen(passwd);
    if(!CreateSha256Hash(passwd, pw_len, hashed, hashed_buf)) {
    	printf("Couldn't hash the password!\n");
    	return 0;
    }
    // printf("hashed pw: %s\n", hashed_buf);
	// fptr=fopen("password_store.txt", "r");
	// Check if password store file is present

	// Create it if not present
	// Look for sane permission on file
	
	
	if(access(fname, F_OK)!= -1) {
		//File exists, so scan it
		// printf("File exists: In if------------------\n");
		int x = is_registered(uname);
		// printf("result is: %d\n", x);
		if(x!=0) {
			fprintf(stderr, "Choose another username\n");
			return 0;
		}
		else {
			// FILE *pw_file;
			fptr = fopen("pw_store.txt", "a+");
			size_t len1 = strlen(uname)-1;
			size_t len2 = strlen(hashed_buf);

			char * collection = malloc(len1 + len2 + 2);
			memcpy(collection, uname, len1);
			collection[len1] = ':';
			memcpy(collection + len1 + 1, hashed_buf, len2 + 1);
			
			fprintf(fptr, "%s\n", collection);
			printf("\nUser Registered!\n");
			// printf("collection is: %s\n", collection);
			
		}
	}
	else {
		// Open the password file and append the username and password
		// Dont append the password in plain text. Try something obscure.
		// If you are out of ideas look for how unix implements passwords.
		//File doesn't exist, so directly add the username and password to it
		// printf("File doesnt exist: In else------------------\n");
		fptr = fopen("pw_store.txt", "a+");
		size_t len1 = strlen(uname)-1;
		size_t len2 = strlen(hashed_buf);

		char * collection = malloc(len1 + len2 + 2);
		memcpy(collection, uname, len1);
		collection[len1] = ':';
		memcpy(collection + len1 + 1, hashed_buf, len2 + 1);
		// strcat(auth_info,passwd);
		// printf("collection is: %s\n", collection);
		fprintf(fptr, "%s\n", collection);
		
	}
	fclose(fptr);
	return 1;
}

int check_auth(char *uname, char *hashed_passwd) {
	// Open your passwd storage file
	// Find if the password matches
	FILE *stream;
	// printf("-------------------inside 2");
	stream = fopen("pw_store.txt", "r");
	char line[1024];
	while (fgets(line, 1024, stream)) 
    {
        char* tmp = strdup(line);
        // printf("Field 1 would be un: %s\n", getfield(tmp, 1));
        if(strcmp(getfield(tmp, 2), hashed_passwd) == 0) {
        	fclose(stream);
        	return 1;
        }
        	
        // NOTE strtok clobbers tmp
        free(tmp);
    }
	// return 1 if found
	// else return 0
	fclose(stream);
	return 0;
}

int auth_user(char *uname, char *passwd) {
	// check if password store is present
	// if not return 0
	// printf("In authorization function: %s\n", uname);
	char *pos;
	if ((pos=strchr(uname, '\n')) != NULL) {
		*pos = '\0';
	}
	// printf("In authorization function:processed uname: %s\n", uname);
	int x = is_registered(uname);
	// printf("res in auth_user is: %d\n", x);
	if(x==0) {
		fprintf(stderr, "\nUser not registered\n");
		return 0;
	}
	else {
		//First hash the password and then compare it with the password in the pw_storage file
		unsigned char hashed[SHA256_DIGEST_LENGTH]; //32 bytes
	    char hashed_buf[SHA_DIGEST_LENGTH*2];
	    memset(hashed_buf, 0x0, SHA_DIGEST_LENGTH*2);
	    int pw_len = strlen(passwd);
	    if(!CreateSha256Hash(passwd, pw_len, hashed, hashed_buf)) {
	    	printf("Couldn't hash the password!\n");
    		return 0;
   		}
    	// printf("hashed pw: %s\n", hashed_buf);
		// Parse the file and then compare username and password supplied.
		// If you recall password is not plain text...
		
		//return 0/1 depending on if the password was correct or not
		int authotrized = check_auth(uname, hashed_buf);
		if(authotrized) {
			printf("\nUser: %s has been authorized!\n", uname);
		}
	}
	// if (is_registered(uname)) {
	// 	fprintf(stderr, "User not registered\n");
	// 	return 0;
	// }

	
}

