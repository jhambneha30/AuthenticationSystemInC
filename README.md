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
