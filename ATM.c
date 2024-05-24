#include <stdio.h>
#include <string.h>

void checkBalance(float balance);
void withdrawMoney(float *balance);
void depositMoney(float *balance);
void loadBalance(float *balance);
void saveBalance(float balance);

#define BALANCE_FILE "balance.txt"

int main() {
    int choice;
    char continueTransaction[4] = "Yes";
    float balance = 0.0;

    // Load balance from file
    loadBalance(&balance);

    while (strcmp(continueTransaction, "Yes") == 0 || strcmp(continueTransaction, "yes") == 0) {
        printf("\n==== ATM Menu ====\n");
        printf("1. Check Balance\n");
        printf("2. Deposit Money\n");
        printf("3. Withdraw Money\n");
        printf("4. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                checkBalance(balance);
                break;
            case 2:
                depositMoney(&balance);
                saveBalance(balance);
                break;
            case 3:
                withdrawMoney(&balance);
                saveBalance(balance);
                break;
            case 4:
                printf("Thank you for using the AUM Bank ATM!\n");
                return 0;
            default:
                printf("Invalid choice! Please try again.\n");
        }

        printf("\nDo you want to perform another transaction? : ");
        scanf(" %s", continueTransaction);
    }

    printf("Thank you for using the AUM Bank ATM!\n");
    return 0;
}

void checkBalance(float balance) {
    printf("Current Balance is $%.3f\n", balance);
}

void withdrawMoney(float *balance) {
    float withdrMoney;
    
    printf("Enter the Amount to Withdraw : $");
    scanf(" %f", &withdrMoney);
    if (withdrMoney > 0 && withdrMoney <= *balance) {
        *balance -= withdrMoney;
        printf("Your New balance is $%.3f\n", *balance);
    } else if (withdrMoney > *balance) {
        printf("Insufficient balance!\n");
    } else {
        printf("Invalid Input!\n");
    }
}

void depositMoney(float *balance) {
    float depoMoney;
    
    printf("Enter the Amount to Deposit : $");
    scanf(" %f", &depoMoney);
    if (depoMoney > 0) {
        *balance += depoMoney;
        printf("Your New balance is $%.3f\n", *balance);
    } else {
        printf("Invalid Input!\n");
    }
}

void loadBalance(float *balance) {
    FILE *file = fopen(BALANCE_FILE, "r");
    if (file == NULL) {
        // File does not exist, initialize balance to 1000
        *balance = 1000.0;
    } else {
        fscanf(file, "%f", balance);
        fclose(file);
    }
}

void saveBalance(float balance) {
    FILE *file = fopen(BALANCE_FILE, "w");
    if (file != NULL) {
        fprintf(file, "%.3f", balance);
        fclose(file);
    } else {
        printf("Error saving balance!\n");
    }
}
