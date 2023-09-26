#include<stdio.h>
#include"project.h"
int main() {
    int choice;

    do {
        printf("Bank Management System\n");
        printf("1. Login In\n");
        printf("2. Sign In\n");
        printf("3. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                if (signIn()) {
                    printf("\nLogined in successfully!\n");
                    bank();
                }
                else {
                    printf("\nInvalid username or password. Please try again.\n");
                }
                break;
            case 2:
                registerUser();
                break;
            case 3:
                printf("\nThank you! Visit Again...\n");
                return 0;
            default:
                printf("Invalid choice. Please try again.\n");
        }
    } while (choice != 3);

    return 0;
}
