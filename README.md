# AuthenticationSystemInC
C program that implements the password functionality (similar to that in Ubuntu)


Registering a user

nehaj@nehaj-thinkpad:~$ ./passwd -r <br />
Enter Username: nehaj <br />
Enter Password: ****** <br />
// Note: asterisks get printed <br />

// Authentication <br />
nehaj@nehaj-thinkpad:~$ ./passwd -a <br />
Enter Username: abcd <br />
[error] User not registered <br />

// Ok second Try <br />
nehaj@nehaj-thinkpad:~$ ./passwd -a <br />
Enter Username: nehaj <br />
Enter Password: ****** <br />
[success] Authenticated

---------------------------------------------------------------------------------
To run the code, please compile the code as follows:  
gcc main.c -o main -lssl -lcrypto  

For registration, run the script:  
./main -r   

For authentication, run the script:  
./main -a  
  
---------------------------------------------------------------------------------------------------------------------------  
# NOTE:  
  
1. I have used the following ASCII values for Enter, Tab and backspace (because these were working on my system).  
In case they do not work, change the value for ENTER to 13 and that of Backspace to 8.  
  
#define ENTER 10 //13  
#define TAB 9  
#define BKSP 127 //8  

