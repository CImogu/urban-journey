# urban-journey

Hello! Thank you so much for taking the time to go through my code! :)
You can run the C++ file using the commands

```
g++ -o my_program main.cpp
./my_program 
```

The largest test case is already in the main() function and other unit test cases
are placed after the classes of interest.

Design considerations:
1. Ideally only the bank should be able to add and remove accounts and users, but for testing the controller, the constructor was included.
2. I debated between throwing an error at the Account.withdrawBalance() method when the user has an insufficient balance, but I decided to 
go with returning a status string.
3. Generating a random ID for users helps with some security issues, but we would need to query the actual bank database to make sure
that they do not already exist.
4. For the demo, I decided to store the pin in the User's Profile, but ideally this would be encrypted and verified using the bank API.
5. Lastly, since depositing and withdrawing need to take in the amount as input, and the description mentioned a UI was not the main focus of the controller, I initialized variables that can be updated with the actual UI.

Thank you again! I had fun working on the exercises.
