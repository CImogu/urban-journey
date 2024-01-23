#include <iostream>
#include <string>
#include <vector>
#include <functional>

#define IS_TRUE(x) {if (!(x)) std::cout << __FUNCTION__ << "failed on line " << __LINE__ << std::endl;}

using namespace std;

// ACCOUNTS 

class Account {
private:
    string _id, userId;
    int balance;
    vector<string> transactions;
public:
    // Create an account
    Account(string userId){
        balance = 0;
        this->userId = userId;
    };
    
    string getBalance(){
        return to_string(this->balance);
    };
        
    void depositBalance(int amountToDeposit){
        this->balance += amountToDeposit;
        this->transactions.push_back("Deposited " + to_string(amountToDeposit));
    };
        
    string withdrawBalance(int withdrawAmount){
        const int minimumBalance = 20;
    if ((this->balance - withdrawAmount) < minimumBalance){
        return "failed";
    }
    this->balance -= withdrawAmount;
    this->transactions.push_back("Withdrew " + to_string(withdrawAmount));
    return "success";
    };
};

void test_accountCreate(){
    Account test_account = Account("u_test010");
    IS_TRUE(test_account.getBalance().compare("0") == 0);
}

void test_accountWithdrawal(){
    Account test_account = Account("u_txet982");
    test_account.depositBalance(50);
    IS_TRUE(test_account.withdrawBalance(20).compare("success") == 0);
    IS_TRUE(test_account.getBalance().compare("30") == 0);
    IS_TRUE(test_account.withdrawBalance(20).compare("failed") == 0);
    IS_TRUE(test_account.getBalance().compare("30") == 0);
}


// BANK USERS

class User
{
private:
    string _id, familyName, givenName;
    vector<Account> accounts;
    int userPin;

public:
    User(string familyName, string givenName){
        srand((unsigned) time(NULL));
        this->_id = "u_test"+to_string(rand());
        // ...query secure database of users to see if randomly selected user_id has been chosen
        this->familyName = familyName;
        this->givenName = givenName;

        // By default every new user has one account
        Account new_account = Account(this->_id);
        accounts.push_back(new_account);

    };

    string getDisplayName(bool leftToRight){
        if (leftToRight){
            return this->givenName + " " + this->familyName;
        } else {
            return this->familyName + " " + this->givenName;
        }
    }

    // Access accounts if PIN has been verified - switch with bank API later
    vector<Account> getAccounts(function<bool()> verification){
        if (verification()) {
            return accounts;
        } else {
            throw 404;
        }
    }

    // Delete when bank API introduced
    vector<Account> getAccounts(int attemptedPin){
        if (attemptedPin == this->userPin) {
            return accounts;
        } else {
            throw 404;
        }
    }

    void setPin(int newPin) {
        userPin = newPin;
    }
};

// Dummy function to use in test cases
bool pinAlwaysValid() {return true;}

void test_userCreate(){
    User test_user = User("foo", "bar");
    for (Account a: test_user.getAccounts(&pinAlwaysValid)) {
        IS_TRUE(a.getBalance().compare("0") == 0);
    } 
}

void test_userCheckPin(){
    User test_user = User("foo", "bar");
    test_user.setPin(8745);
    vector<Account> accounts;
    try{
        test_user.getAccounts(5342);
        cout << "Expected an error";
    } 
    catch(int error) {
        accounts = test_user.getAccounts(8745);
    }
    accounts = test_user.getAccounts(8745);
    IS_TRUE(accounts.size() > 0);
}

// OVERALL ATM CONTROLLER

// The card is connected to a particular user which is determined by the card reader
void ATM_controller(User cardUser, int attemptedPin){
    int ATM_state = 0;
    vector<Account> userAccounts;
    int chosenIndex;
    bool finished = false;

    while (!finished) {
        switch(ATM_state){
            case 0: { // Check Pin
                try {
                    userAccounts = cardUser.getAccounts(attemptedPin);
                    cout << "Found accounts" << endl;
                    ATM_state = 1;
                }
                catch(...) {}
                break;
            }
            case 1: {// Select Account
                cout << "\n" +  cardUser.getDisplayName(true) + "\'s Accounts:" << endl;
                for (int i = 0; i < userAccounts.size(); i++) {
                    cout << to_string(i) << endl;
                    // Could also display associated account names
                }
                cin >> chosenIndex;
                if (chosenIndex < userAccounts.size()){
                    ATM_state++;
                }
                break;
            }
            case 2: {// Manage Account
                cout << "____________\n";
                cout << "1. Get Balance \n2. Deposit \n3. Withdraw \n4. Quit" << endl;
                int nextStep;
                cin >> nextStep;
                if (nextStep == 1) {
                    ATM_state = 3;
                } else if (nextStep == 2) {
                    ATM_state = 4;
                } else if (nextStep == 3) {
                    ATM_state = 5;
                } else if (nextStep == 4) {
                    ATM_state = 6;
                }
                else {
                    cout << "Invalid input" << endl;
                }
                break;
            }
            case 3: {// Get Balance
                cout << "Balance: " + userAccounts[chosenIndex].getBalance() << endl;
                ATM_state = 2;
            }
            case 4: {// Deposit
                int depositAmount;
                userAccounts[chosenIndex].depositBalance(depositAmount);
                ATM_state = 2;
                break;
            }
            case 5: {// Withdraw
                int withdrawAmount;
                string output;
                output = userAccounts[chosenIndex].withdrawBalance(withdrawAmount);
                cout << output << endl;
                ATM_state = 2;
                break;
            }
            case 6: {// Finish
                cout << "Complete";
                break;
            }
    } }
}

void test_ATMController(){
    User test_user = User("foo", "bar");
    test_user.setPin(1234);
    ATM_controller(test_user, 1234);
}


int main(int argc, char const *argv[]){
    test_ATMController();
}