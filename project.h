#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include<conio.h>
#define MAX_CUSTOMERS 100
#define FILE_NAME "customer_details.txt"
typedef struct {
    char name[100];
    int age;
    int pin;
    char aadharNumber[13];
    long long int accountNumber;
    char accountType[100];
    float balance;
    char dateOfBirth[11];
    float fixedDepositAmount;
    float loanAmount;
    float transactionHistory[100]; // Added transactionHistory array
    int numTransactions;
} Customer;
typedef struct {
    char username[20];
    char password[20];
} User;

Customer customers[MAX_CUSTOMERS];
int numCustomers = 0;
User users[10];
int userCount = 0;

void saveCustomerDetails() {
    FILE *file = fopen(FILE_NAME, "w");
    if (file == NULL) {
        printf("Failed to open file for writing.\n");
        return;
    }

    fwrite(customers, sizeof(Customer), numCustomers, file);
    fclose(file);
}
void loadCustomerDetails() {
    FILE *file = fopen(FILE_NAME, "r");
    if (file == NULL) {
        printf("No customer details found.\n");
        return;
    }

    numCustomers = fread(customers, sizeof(Customer), MAX_CUSTOMERS, file);
    fclose(file);
}
void addCustomerDetails(Customer newCustomer) {
    if (numCustomers == MAX_CUSTOMERS) {
        printf("Maximum number of customers reached.\n");
        return;
    }

    customers[numCustomers++] = newCustomer;
    saveCustomerDetails();
    printf("Customer details added successfully.\n");
}

void readCustomerDetails() {
	int m;
    if (numCustomers == MAX_CUSTOMERS) {
        printf("Maximum number of customers reached.\n");
        return;
    }
    
    Customer newCustomer;
    
    printf("Enter customer name(With out white spaces):");
    scanf("%s", newCustomer.name);
    
    printf("Enter customer age:");
    scanf("%d", &newCustomer.age);
    if(newCustomer.age>=18)
    {
    a:printf("Enter customer Aadhar number:");
    scanf("%s", newCustomer.aadharNumber);
    m=strlen(newCustomer.aadharNumber);
    if(m==12)
    {
     printf("Enter customer account number:");
    scanf("%lld", &newCustomer.accountNumber);
    
    printf("Enter account type:");
    scanf("%s", newCustomer.accountType);
    
    printf("Enter initial balance amount: ");
    scanf("%f", &newCustomer.balance);
    
    printf("Enter customer date of birth (YYYY-MM-DD): ");
    scanf("%s", newCustomer.dateOfBirth);
    
    printf("Enter PIN number: ");  // Prompt for PIN number
    scanf("%d", &newCustomer.pin);
    
    
    //customers[numCustomers++] = newCustomer;
    addCustomerDetails(newCustomer);
    //printf("Customer details added successfully.\n");
}
else
{
	printf("!!!The adhaar number should be upto 12 digits.\n");
	printf("So,enter correct adhaar number\n");
	goto a;
}
}
else
{
	printf("Sorry");
	printf("\nPlease wait for %d years",18-newCustomer.age);
}
}

void withdrawAmount() {
    long long int accountNumber;
    float amount;
    int pin;
    int i;
    int found = 0;
    
    printf("Enter account number: ");
    scanf("%lld", &accountNumber);
    
    for (i = 0; i < numCustomers; i++) {
        if (customers[i].accountNumber == accountNumber) {
            found = 1;
            printf("Enter PIN number: ");  
            scanf("%d", &pin);

            if (customers[i].pin != pin) {  
                printf("Invalid PIN number. Withdrawal failed.\n");
                return;
            }
            printf("Enter amount to withdraw: ");
            scanf("%f", &amount);
            
            if (customers[i].balance >= amount) {
                customers[i].balance -= amount;
                printf("Amount withdrawn successfully.\n");
                customers[i].transactionHistory[customers[i].numTransactions] = -amount;
                customers[i].numTransactions++;
                saveCustomerDetails();
                printf("\nPresent bank balance:%0.2f",customers[i].balance);
            } else {
                printf("Insufficient balance.\n");
            }
            
            break;
        }
    }
    
    if (!found) {
        printf("Account number not found.\n");
    }
}
void displayTransactionHistory() {
    long long int accountNumber;
    int pin;
    int i,j;
    int found = 0;

    printf("Enter account number: ");
    scanf("%lld",&accountNumber);

    for (i = 0; i < numCustomers; i++) {
        if (customers[i].accountNumber == accountNumber) {
            found = 1;

            printf("Enter PIN number: ");
            scanf("%d", &pin);

            if (customers[i].pin != pin) {
                printf("Invalid PIN number. Access denied.\n");
                return;
            }

            printf("Transaction History for Account Number: %lld\n", customers[i].accountNumber);
            printf("----------------------------------------------------------------\n");
            printf("    S.No.         |     Transaction Amount     |    Type   \n");
            printf("----------------------------------------------------------------\n");

            for ( j = 0; j < customers[i].numTransactions; j++) {
                float amount = customers[i].transactionHistory[j];
                char* transactionType = amount < 0 ? ("Withdrawal"):("Deposit");
                printf("   %5d        |       %10.2f          |   %s\n", j + 1,amount,transactionType);
            }

            printf("----------------------------------------------------------------\n");

            break;
        }
    }

    if (!found) {
        printf("Account not found. Access denied.\n");
    }
}
void depositAmount() {
    long long int accountNumber;
    float amount;
    int i;
    int found = 0;
    
    printf("Enter account number: ");
    scanf("%lld", &accountNumber);
    
    for (i = 0; i < numCustomers; i++) {
        if (customers[i].accountNumber == accountNumber) {
            found = 1;
            printf("Enter amount to deposit: ");
            scanf("%f", &amount);
            customers[i].balance += amount;
            printf("Amount deposited successfully.\n");
            customers[i].transactionHistory[customers[i].numTransactions] = +amount;
            customers[i].numTransactions++;
            saveCustomerDetails();
            printf("\nPresent bank balance:%0.2f",customers[i].balance);
            break;
        }
    }
    
    if (!found) {
        printf("Account number not found.\n");
    }
}
void sortCustomersByAge(int order) {
int i, j;
Customer temp;
    for (i = 0; i < numCustomers - 1; i++){
        for (j = 0; j < numCustomers - i - 1; j++) {
            if ((order == 0 && customers[j].age > customers[j + 1].age) ||
                (order == 1 && customers[j].age < customers[j + 1].age)) {
                temp = customers[j];
                customers[j] = customers[j + 1];
                customers[j + 1] = temp;
            }
        }
    }
printf("Customer details sorted by age in %s order.\n", (order == 0 ? "ascending" : "descending"));
printf("-------------------------------------------------------------------\n");
printf("Name\t\tAge\tAadhar Number\tAccount Number\tCurrent balance\n");
printf("-------------------------------------------------------------------\n");
for (i = 0; i < numCustomers; i++) {
    printf("%s\t%d\t%lld\t%lld\t%f\n", customers[i].name, customers[i].age, customers[i].aadharNumber, customers[i].accountNumber, customers[i].balance);
}
printf("-------------------------------------------------------------------\n");
}

void sortCustomersByBalance(int order) {
int i, j;
Customer temp;
for (i = 0; i < numCustomers - 1; i++) {
    for (j = 0; j < numCustomers - i - 1; j++) {
        if ((order == 0 && customers[j].balance > customers[j + 1].balance) ||
            (order == 1 && customers[j].balance < customers[j + 1].balance)) {
            temp = customers[j];
            customers[j] = customers[j + 1];
            customers[j + 1] = temp;
        }
    }
}
printf("Customer details sorted by balance in %s order.\n", (order == 0 ? "ascending" : "descending"));
printf("-------------------------------------------------------------------\n");
printf("Name\t\tAge\tAadhar Number\tAccount Number\tCurrent balance\n");
printf("-------------------------------------------------------------------\n");

for (i = 0; i < numCustomers; i++) {
    printf("%s\t\t%d\t%lld\t%lld%f\n", customers[i].name, customers[i].age, customers[i].aadharNumber, customers[i].accountNumber,customers[i].balance);
}
printf("-------------------------------------------------------------------\n");
}

void sortCustomersByAccountNumber(int order) {
int i, j;
Customer temp;
for (i = 0; i < numCustomers - 1; i++) {
    for (j = 0; j < numCustomers - i - 1; j++) {
        if ((order == 0 && customers[j].accountNumber > customers[j + 1].accountNumber) ||
            (order == 1 && customers[j].accountNumber < customers[j + 1].accountNumber)) {
            temp = customers[j];
            customers[j] = customers[j + 1];
            customers[j + 1] = temp;
        }
    }
}
printf("Customer details sorted by account number in %s order.\n", (order == 0 ? "ascending" : "descending"));
printf("--------------------------------------------------------------------\n");
printf("Name\t\tAge\tAadhar Number\tAccount Number\tCurrent balance\n");
printf("--------------------------------------------------------------------\n");

for (i = 0; i < numCustomers; i++) {
    printf("%s\t\t%d\t%lld\t%lld\t%f\n", customers[i].name, customers[i].age, customers[i].aadharNumber, customers[i].accountNumber,customers[i].balance);
}

printf("--------------------------------------------------------------------\n");
}

void searchCustomersByName() {
char searchName[100];
int i;
int found = 0;
printf("Enter the name to search:");
scanf("%s", searchName);

printf("Search results:\n");
printf("--------------------------------------------------------------------\n");
printf("Name\t\tAge\tAadhar Number\tAccount Number\tCurrent Balance\n");
printf("--------------------------------------------------------------------\n");
for (i = 0; i < numCustomers; i++) {
    if (strcmp(searchName, customers[i].name) == 0) {
found = 1;
printf("%s\t\t%d\t%lld\t%lld\t%f\n", customers[i].name, customers[i].age, customers[i].aadharNumber, customers[i].accountNumber,customers[i].balance);
}
}
if(!found) {
    printf("No customers found with the given name.\n");
}

printf("--------------------------------------------------------------------\n");
}
void searchCustomersByAge() {
int searchAge;
int i;
int found = 0;
printf("Enter the age to search: ");
scanf("%d", &searchAge);

printf("Search results:\n");
printf("-------------------------------------------------------------------------\n");
printf("Name\t\tAge\tAadhar Number\tAccount Number\tCurrent Balance\n");
printf("-------------------------------------------------------------------------\n");

for (i = 0; i < numCustomers; i++) {
    if (customers[i].age == searchAge) {
        found = 1;
        printf("%s\t\t%d\t%lld\t%lld\t%f\n",customers[i].name, customers[i].age,customers[i].aadharNumber, customers[i].accountNumber,customers[i].balance);
    }
}

if (!found) {
    printf("No customers found with the given age.\n");
}

printf("------------------------------------------------------------------------\n");
}

void searchCustomersByAccountNumber() {
long long int searchAccountNumber;
int i;
int found = 0;
printf("Enter the account number to search: ");
scanf("%lld", &searchAccountNumber);

printf("Search results:\n");
printf("----------------------------------------------------------------------\n");
printf("Name\t\tAge\tAadhar Number\tAccount Number\tCurrent Balance\n");
printf("----------------------------------------------------------------------\n");

for (i = 0; i < numCustomers; i++) {
    if (customers[i].accountNumber == searchAccountNumber) {
        found = 1;
        printf("%s\t\t%d\t%lld\t%lld\t%f\n", customers[i].name, customers[i].age, customers[i].aadharNumber, customers[i].accountNumber,customers[i].balance);
    }
}

if (!found) {
    printf("No customers found with the given account number.\n");
}

printf("----------------------------------------------------------------------\n");
}
void calculateFixedDeposit() {
    long long int accountNumber;
    float amount;
    int i;
    int found = 0;
    
    printf("Enter account number: ");
    scanf("%lld", &accountNumber);
    
    for (i = 0; i < numCustomers; i++) {
        if (customers[i].accountNumber == accountNumber) {
            found = 1;
            printf("Enter fixed deposit amount: ");
            scanf("%f", &amount);
            
            // Calculate interest based on fixed deposit plans
            float interestRate;
            int timePeriod;
            printf("Enter fixed deposit interest rate: ");
            scanf("%f", &interestRate);
            printf("Enter fixed deposit time period in years: ");
            scanf("%d", &timePeriod);
            
            float interest = (amount * interestRate * timePeriod) / 100;
            float totalAmount = amount + interest;
            
            customers[i].balance += totalAmount;
            customers[i].fixedDepositAmount += totalAmount;
            saveCustomerDetails();
            printf("Fixed deposit amount: %0.2f\n", amount);
            printf("Interest earned: %0.2f\n", interest);
            printf("Total amount after maturity: %0.2f\n", totalAmount);
            printf("\nPresent bank balance: %0.2f", customers[i].balance);
            break;
        }
    }
    if (!found) {
        printf("Account number not found.\n");
    }
}
void calculateLoan() {
    long long int accountNumber;
    float amount;
    int i;
    int found = 0;
    
    printf("Enter account number: ");
    scanf("%lld", &accountNumber);
    
    for (i = 0; i < numCustomers; i++) {
        if (customers[i].accountNumber == accountNumber) {
            found = 1;
            printf("Enter loan amount: ");
            scanf("%f", &amount);
            
            // Calculate interest based on loan plans
            float interestRate;
            int timePeriod;
            printf("Enter loan interest rate: ");
            scanf("%f", &interestRate);
            printf("Enter loan time period in years: ");
            scanf("%d", &timePeriod);
            
            float interest = (amount * interestRate * timePeriod) / 100;
            float totalAmount = amount + interest;
            
            if (totalAmount <= customers[i].balance) {
                customers[i].balance -= totalAmount;
                customers[i].loanAmount += totalAmount;
                saveCustomerDetails();
                printf("Loan amount: %0.2f\n", amount);
                printf("Interest payable: %0.2f\n", interest);
                printf("Total amount to be repaid: %0.2f\n", totalAmount);
                printf("\nPresent bank balance: %0.2f", customers[i].balance);
            } else {
                printf("Insufficient balance to grant the loan.\n");
            }
            
            break;
        }
    }
    
    if (!found) {
        printf("Account number not found.\n");
    }
}
void printCustomerDetails() {
int i;
printf("Customer details:\n");
printf("----------------------------------------------------------------------\n");
printf("Name\t\tAge\tAadhar Number\tAccount Number\tCurrent balance\n");
printf("----------------------------------------------------------------------\n");
for (i = 0; i < numCustomers; i++) {
    printf("%s\t\t%d\t%lld\t%lld\t%f\n", customers[i].name, customers[i].age, customers[i].aadharNumber, customers[i].accountNumber,customers[i].balance);
}

printf("----------------------------------------------------------------------\n");
}
int bank() {
loadCustomerDetails();
int choice,ach,bch,order;
do {
    printf("*----------------------------Bank Management System---------------------*\n");
    printf("1. Read customer details\n");
    printf("2. Withdraw amount\n");
    printf("3. Deposit amount\n");
    printf("4. Sort customer details\n");
    printf("5. Search customer details\n");
    printf("6. Print customer details\n");
    printf("7. For fixed deposit\n");
    printf("8. For loan\n");
    printf("9. For Transaction histroy\n");
    printf("0. Exit\n");
    printf("Enter your choice: ");
    scanf("%d", &choice);
    
    switch (choice) {
        case 1:
            readCustomerDetails();
            break;
        case 2:
            withdrawAmount();
            break;
        case 3:
            depositAmount();
            break;
        case 4:
            //sortCustomers();
            printf("\n1.Sort by age");
            printf("\n2.Sort by balance");
            printf("\n3.Sort by accountNumber");
            printf("\nEnter your choice:");
            scanf("%d",&ach);
            switch(ach)
            {
                case 1:printf("\npress 0 for ascending order");
                       printf("\nPress 1 for desending order\n");
                       scanf("%d",&order);
                       sortCustomersByAge(order);
                       break;
                case 2:printf("\npress 0 for ascending order");
                       printf("\nPress 1 for desending order\n");
                       scanf("%d",&order);
                       sortCustomersByBalance(order);
                       break;
                case 3:printf("\npress 0 for ascending order");
                       printf("\nPress 1 for desending order\n");
                       scanf("%d",&order);
                       sortCustomersByAccountNumber(order);
                       break;
            }
            break;
        case 5:
            //searchCustomers();
            printf("\n1.Search by name");
            printf("\n2.Search by age");
            printf("\n3.Search by Account number");
            printf("\nEnter your choice:");
            scanf("%d",&bch);
            switch(bch)
            {
                case 1:searchCustomersByName();
                       break;
                case 2:searchCustomersByAge();
                       break;
                case 3:searchCustomersByAccountNumber();
                       break;
            }
            break;
        case 6:printCustomerDetails();
               break;
        case 7:calculateFixedDeposit() ;
               break;
        case 8:calculateLoan();
               break;
        case 9:displayTransactionHistory();
        	    break;
        case 0:printf("Exiting...\n");
               break;
        default:printf("Invalid choice. Please try again.\n");
                break;
    }
    printf("\n");
} while (choice != 0);
return 0;
}
void registerUser() {
    printf("Registration\n");
    printf("Enter username: ");
    scanf("%s", users[userCount].username);

    printf("Enter password: ");
    int i = 0;
    while (1) {
        char ch = getch();
        if (ch == 13)  // Enter key
            break;
        putchar('*');  // Print asterisks instead of the actual character
        users[userCount].password[i++] = ch;
    }
    users[userCount].password[i] = '\0';

    FILE *file = fopen("users.txt", "a");
    if (file == NULL) {
        printf("\nError opening file.\n");
        return;
    }

    fprintf(file, "%s %s\n", users[userCount].username, users[userCount].password);
    fclose(file);

    userCount++;
    printf("\nRegistration successful!\n");
}

//define MAX_ATTEMPTS 3

int signIn() {
    printf("Sign In\n");
    char username[20];
    char password[20];

    printf("Enter username: ");
    scanf("%s", username);

    printf("Enter password: ");
    int i = 0;
    while (1) {
        char ch = getch();
        if (ch == 13)  // Enter key
            break;
        putchar('*');  
        password[i++] = ch;
    }
    password[i] = '\0';

    FILE *file = fopen("users.txt", "r");
    if (file == NULL) {
        printf("\nError opening file.\n");
        return 0;
    }

    char fileUsername[20];
    char filePassword[20];
    int attempts = 0;
    int isLoggedIn = 0;
    int MAX_ATTEMPTS=3;

    while (fscanf(file, "%s %s", fileUsername, filePassword) != EOF) {
        if (strcmp(username, fileUsername) == 0 && strcmp(password, filePassword) == 0) {
            isLoggedIn = 1;
            break;
        }
    }

    fclose(file);

    if (isLoggedIn) {
        printf("\nWelcome, %s!\n", username);
        return 1;  // Sign-in successful
    } else {
        printf("\nInvalid username or password. Please try again.\n");
        attempts++;

        if (attempts == MAX_ATTEMPTS) {
            printf("Too many failed attempts. Exiting...\n");
            return 0;  // Sign-in failed
        } else {
            return signIn();  // Recursive call to try again
        }
    }
}
