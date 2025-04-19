#include <stdio.h>
#include <string.h>

#define MAX_CUSTOMERS 10   // Maximum number of customers allowed
#define MIN_BALANCE 2000   // Minimum balance required for any account

// Structure to hold customer details
typedef struct {
    char name[50];          // Customer's name
    int accountNumber;      // Unique account number
    char panCard[15];       // Customer's PAN card number
    float balance;          // Customer's current account balance
} Customer;

// Function prototypes
void addCustomer(Customer customers[], int *customerCount);
void deposit(Customer customers[], int customerCount);
void withdraw(Customer customers[], int customerCount);
void checkBalance(Customer customers[], int customerCount);
int findCustomer(Customer customers[], int customerCount, int accountNumber);

int main() {
    Customer customers[MAX_CUSTOMERS]; // Array to store customer data
    int customerCount = 0;             // Current number of customers
    int choice;                        // User's choice for operation

    do {
        // Display menu for user interaction
        printf("\n** Bank Management System **\n");
        printf("1. Add New Customer\n");
        printf("2. Deposit Money\n");
        printf("3. Withdraw Money\n");
        printf("4. Check Account Balance\n");
        printf("5. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        // Perform the chosen operation
        switch (choice) {
            case 1:
                addCustomer(customers, &customerCount); // Add new customer
                break;
            case 2:
                deposit(customers, customerCount); // Deposit money
                break;
            case 3:
                withdraw(customers, customerCount); // Withdraw money
                break;
            case 4:
                checkBalance(customers, customerCount); // Check balance
                break;
            case 5:
                printf("Exiting the program. Thank you!\n"); // Exit message
                break;
            default:
                printf("Invalid choice! Please try again.\n"); // Invalid choice handling
        }
    } while (choice != 5); // Loop until user chooses to exit

    return 0;
}

// Function to add a new customer
void addCustomer(Customer customers[], int *customerCount) {
    if (*customerCount >= MAX_CUSTOMERS) {
        printf("Cannot add more customers. Maximum limit reached.\n");
        return; // Stop if maximum customer limit is reached
    }

    Customer newCustomer;  // Temporary variable to hold new customer data

    // Ask for customer details
    printf("Enter customer name: ");
    scanf(" %[^\n]", newCustomer.name); // Read full name (including spaces)
    printf("Enter account number: ");
    scanf("%d", &newCustomer.accountNumber);
    printf("Enter PAN card number: ");
    scanf(" %[^\n]", newCustomer.panCard); // Read PAN card number
    printf("Enter initial balance (minimum %.2f): ", (float)MIN_BALANCE);
    scanf("%f", &newCustomer.balance);

    // Validate the minimum balance requirement
    if (newCustomer.balance < MIN_BALANCE) {
        printf("Error: Minimum balance should be %.2f. Customer not added.\n", (float)MIN_BALANCE);
        return;
    }

    // Add the new customer to the list
    customers[*customerCount] = newCustomer;
    (*customerCount)++; // Increase customer count
    printf("Customer added successfully.\n");
}

// Function to deposit money into an account
void deposit(Customer customers[], int customerCount) {
    int accountNumber;
    float amount;

    // Ask for account number and find the customer
    printf("Enter account number: ");
    scanf("%d", &accountNumber);

    int index = findCustomer(customers, customerCount, accountNumber); // Search for customer by account number
    if (index == -1) {
        printf("Account not found!\n"); // Handle if account is not found
        return;
    }

    // Ask for deposit amount and update balance
    printf("Enter amount to deposit: ");
    scanf("%f", &amount);

    if (amount <= 0) {
        printf("Error: Deposit amount must be positive.\n"); // Handle invalid deposit amount
        return;
    }

    customers[index].balance += amount; // Add the deposit to the balance
    printf("Amount deposited successfully. Updated balance: %.2f\n", customers[index].balance);
}

// Function to withdraw money from an account
void withdraw(Customer customers[], int customerCount) {
    int accountNumber;
    float amount;

    // Ask for account number and find the customer
    printf("Enter account number: ");
    scanf("%d", &accountNumber);

    int index = findCustomer(customers, customerCount, accountNumber); // Search for customer by account number
    if (index == -1) {
        printf("Account not found!\n"); // Handle if account is not found
        return;
    }

    // Ask for withdrawal amount and validate
    printf("Enter amount to withdraw: ");
    scanf("%f", &amount);

    if (amount <= 0) {
        printf("Error: Withdrawal amount must be positive.\n"); // Handle invalid withdrawal amount
        return;
    }

    // Check if withdrawal maintains the minimum balance
    if (customers[index].balance - amount < MIN_BALANCE) {
        printf("Error: Insufficient balance. Minimum balance of %.2f must be maintained.\n", (float)MIN_BALANCE);
        return; // Stop if insufficient balance
    }

    // Deduct the amount from the balance
    customers[index].balance -= amount;
    printf("Amount withdrawn successfully. Updated balance: %.2f\n", customers[index].balance);
}

// Function to check the account balance of a customer
void checkBalance(Customer customers[], int customerCount) {
    int accountNumber;

    // Ask for account number and find the customer
    printf("Enter account number: ");
    scanf("%d", &accountNumber);

    int index = findCustomer(customers, customerCount, accountNumber); // Search for customer by account number
    if (index == -1) {
        printf("Account not found!\n"); // Handle if account is not found
        return;
    }

    // Display the current balance
    printf("Account Balance for %s (Account No: %d): %.2f\n",
           customers[index].name, customers[index].accountNumber, customers[index].balance);
}

// Function to find a customer by account number
int findCustomer(Customer customers[], int customerCount, int accountNumber) {
    for (int i = 0; i < customerCount; i++) {
        if (customers[i].accountNumber == accountNumber) {
            return i; // Return the index of the customer if found
        }
    }
    return -1; // Return -1 if customer is not found
}
