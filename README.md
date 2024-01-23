# urban-journey

Hello! Thank you so much for taking the time to go through my code! :)
You can run the C++ file using the commands

```
g++ -o my_program main.cpp
./my_program 
```

The largest testcase is already in the main() function, and other unit test cases
are placed after the classes of interest.

Design considerations:
1. Ideally only the bank should be able to add and remove accounts and users, but for purposes of the controller, the constructor was included.
2. I debated between throwing an error at the Account.withdrawBalance() method when the user had an insuffient balance, but decide to 
go with returning a status string.
3. Generating a randomID for users helps with some security issues, but we would need to query the actual bank database to make sure
that they do not exist.
4. For the same of the demo, I decided to store the pin in the User's Profile, but ideally this would be encryted and verified using the bank API.

Thank you again! I had fun working on the exercises.