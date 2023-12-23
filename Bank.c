#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#define MAX_ACCOUNTS 100

int loggedInUserIndex = -1; 

typedef struct {
    char username[7];
    char password[50];
    double balance;
} Account;

Account accounts[MAX_ACCOUNTS];
int totalAccounts = 0;

bool logIn(char *username, char *password);
void createAccount(char *username, char *password, double initialDeposit);
void depositMoney(char *username, double amount);
void withdrawMoney(char *username, double amount);

int main() {
    int choice;
    char username[7], password[50];
    double amount;

    while (1) {
        printf("Please select the function you want:\n");
        printf("1. Log in to my account.\n");
        printf("2. Create a new account.\n");
        printf("3. Deposit money.\n");
        printf("4. Withdraw money.\n");
        printf("5. Exit system.\n");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Enter username:\n");
                scanf("%6s", username);
                printf("Enter password:\n");
                scanf("%49s", password);
                if (logIn(username, password)) {
                    printf("Successful login.\n");
                }
                break;
            case 2:
                printf("Enter username (6 digits):\n");
                scanf("%6s", username);
                printf("Enter password:\n");
                scanf("%49s", password);
                printf("Enter initial deposit amount:\n");
                scanf("%lf", &amount);
                createAccount(username, password, amount);
                printf("Account created successfully.\n");
                break;
            case 3:
                if (loggedInUserIndex != -1) {
                    printf("Enter deposit amount:\n");
                    scanf("%lf", &amount);
                    depositMoney(accounts[loggedInUserIndex].username, amount);
                    printf("Deposit successful.\n");
                } else {
                    printf("Please log in first to deposit money.\n");
                }
                break;
            case 4:
                if (loggedInUserIndex != -1) {
                    printf("Enter withdrawal amount:\n");
                    scanf("%lf", &amount);
                    withdrawMoney(accounts[loggedInUserIndex].username, amount);
                    printf("Withdrawal successful.\n");
                } else {
                    printf("Please log in first to withdraw money.\n");
                }
                break;
            case 5:
                printf("Successfully exited the system, welcome to your next visit!\n");
                return 0;
            default:
                printf("Invalid choice, please try again.\n");
        }
    }

    return 0;
}


bool logIn(char *username, char *password) {
    for (int i = 0; i < totalAccounts; i++) {
        if (strcmp(accounts[i].username, username) == 0) {
            if (strcmp(accounts[i].password, password) == 0) {
                loggedInUserIndex = i; 
                printf("Login successful.\n");
                return true;
            } else {
                printf("Wrong password.\n");
                return false;
            }
        }
    }
    printf("Account does not exist.\n");
    return false;
}

void createAccount(char *username, char *password, double initialDeposit) {
    // Check for duplicate usernames
    for (int i = 0; i < totalAccounts; i++) {
        if (strcmp(accounts[i].username, username) == 0) {
            printf("An account with this username already exists.\n");
            return;
        }
    }
    // Check if we can add more accounts
    if (totalAccounts >= MAX_ACCOUNTS) {
        printf("Maximum number of accounts reached.\n");
        return;
    }

    strcpy(accounts[totalAccounts].username, username);
    strcpy(accounts[totalAccounts].password, password);
    accounts[totalAccounts].balance = initialDeposit;
    totalAccounts++;

    printf("Account created successfully.\n");
}


void depositMoney(char *username, double amount) {
    if (amount <= 0) 
    {
        printf("Invalid deposit amount.\n");
        return;
    }

    for (int i = 0; i < totalAccounts; i++) {
        if (strcmp(accounts[i].username, username) == 0) 
        {
            accounts[i].balance += amount;
            printf("Deposit successful. New balance: %.2f\n", accounts[i].balance);
            return;
        }
    }

    printf("Account not found.\n");
}


void withdrawMoney(char *username, double amount) {
    if (amount <= 0) 
    {
        printf("Invalid withdrawal amount.\n");
        return;
    }

    for (int i = 0; i < totalAccounts; i++) 
    {
        if (strcmp(accounts[i].username, username) == 0) 
        {
            if (accounts[i].balance >= amount) 
            {
                accounts[i].balance -= amount;
                printf("Withdrawal successful. New balance: %.2f\n", accounts[i].balance);
                return;
            } 
            else 
            {
                printf("Insufficient funds.\n");
                return;
            }
        }
    }

    printf("Account not found.\n");
}

