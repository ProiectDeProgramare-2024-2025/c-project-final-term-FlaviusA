#include <stdio.h>
#include <math.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include "ProjectFunctions.c"
#include <windows.h>
#define userfile "users.txt"
#define username_length_max 16
void inregistrare_logare_utilizator();
User current_user;
int main()
{
system("cls");
inregistrare_logare_utilizator();
meniu(current_user);

return 0;
    
}

int Register() {
    char username[16], password[30];
    while (1) {
        printf("Register\n-------------------------\n");
        printf("Introdu username-ul tau (\"000\" pentru iesire): ");
        scanf("%15s", username);

        if (strcmp(username, "000") == 0)
            return 0;

        if ( Check_if_user_exists(userfile, username) ) {
            printf("Acest nume de utilizator este ocupat\n");
            system("pause");  system("cls");
            continue;
        }

        FILE *fptr = fopen(userfile, "a");
        if (!fptr) { perror("fopen"); return 0; }
        fprintf(fptr, "%s\n", username);
        fclose(fptr);

        printf("Introdu parola: ");
        scanf("%29s", password);
        fptr = fopen(userfile, "a");
        if (!fptr) { perror("fopen"); return 0; }
        fprintf(fptr, "%s\n", password);
        fclose(fptr);

        system("cls");
        return 1;
    }
}

int login() {
    while (1) {
        printf("Login\n----------------\n");
        printf("Introduceti numele de utilizator (\"000\" pentru iesire): ");
        scanf("%15s", current_user.username);
        if (strcmp(current_user.username, "000") == 0)
            return 0;

        if ( !Check_if_user_exists(userfile, current_user.username) ) {
            printf("Acest utilizator nu exista\n");
            system("pause");  system("cls");
            continue;
        }

        printf("Introdu parola: ");
        scanf("%29s", current_user.password);

        if ( find_user_and_validate(current_user.username, current_user.password) ) {
            system("cls");
            return 1;
        } else {
            printf("Parola a fost introdusa gresit\n");
            system("pause");  system("cls");
        }
    }
}

    




void inregistrare_logare_utilizator()
{
    char c;
    while(1)
    {
    
    printf("Register/login menu\n");
    printf("Introdu \"1\", daca vrei sa te loghezi\n");
    printf("Introdu \"2\" ,daca vrei sa te inregistrezi\n");
    scanf("%c",&c);
    system("cls");
    switch(c)
    {
        case '1':
            system("cls");
            if(login())
            {
                return;
            }
            break;
        case '2':
            system("cls");
            if(Register())
            {
                return; 
            }
            break;
        default:
            system("cls");
            break;

    }

    







    }

} 