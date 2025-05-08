#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>
void app_catalog();
void install_apps();
void app_stats();
void uninstall();
void setColor(int color) {
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
}

#define inst "Installed.txt"
#define catalog_aplicatii "app_catalog.txt"
typedef struct 
{
    char category[20];
    char name[20];
} app;
typedef struct {
  char username[16];
  char password[30];
} User;



void trimNewline(char *str) {
    size_t len = strlen(str);
    if (len > 0 && str[len - 1] == '\n') {
        str[len - 1] = '\0';
    }
}
int find_user_and_validate(const char *username, const char *password) {
    FILE *fp = fopen("users.txt", "r");
    if (!fp) {
        perror("Nu am putut deschide fisierul");
        return 0;
    }

    char fileUser[20];
    char filePass[20];


    while (fgets(fileUser, sizeof fileUser, fp) &&
           fgets(filePass, sizeof filePass, fp))
    {
        trimNewline(fileUser);
        trimNewline(filePass);

        if (strcmp(fileUser, username) == 0) {
            fclose(fp);
            if (strcmp(filePass, password) == 0) {
                return 1;   
            } else {
                return 0;   
            }
        }
    }

    fclose(fp);
    return 0;  
}

int Check_Existence(const char *filename, const char *text);
void Not_Installed_apps()
{
        char line[50];
        FILE *file=fopen(catalog_aplicatii, "r");
    
    while(fgets(line,50,file))
    {
        
        line[strcspn(line,"\n")]='\0';
        if(Check_Existence(inst,line))
        {
        printf("%s\n",line);
        }
    }
    fclose(file);

}

void else_case() {
    printf("Aplicatia e deja instalata\n");
    system("pause");
}
int Check_Existence(const char *filename, const char *text)
{
    char line[100];
    FILE *file=fopen(filename, "r" );
    while (fgets(line, sizeof(line), file))
    {   
        line[strcspn(line, "\n")]='\0';
        if(strcmp(line, text)==0)
        {
            fclose(file);
            return 0;
        }

    }
    fclose(file);
    return 1;
}
void install_app_by_name(app catalog[], int total) {
    char name[50];
    printf("\nIntroduceti numele aplicatiei pe care doriti sa o instalati(doar numele): ");
    scanf(" %[^\n]", name);  
    for (int i = 0; i < total; i++) {
        if (strcmp(catalog[i].name, name) == 0) {
            printf("Se instaleaza aplicatia \"%s\" din categoria \"%s\"...\n", 
                   catalog[i].name, catalog[i].category);

            FILE *f = fopen("installed.txt", "a");
            if (f) {
                fprintf(f, "%s\n%s\n", catalog[i].category, catalog[i].name);
                fclose(f);
            } else {
                perror("Nu s-a putut deschide fisierul pentru instalare");
            }
            printf("\nAplicatia ");
            setColor(3);
            printf("%s ",name);
            setColor(7);
            printf("a fost instalata cu succes");
            system("pause");
            system("cls");
            return;
        }
    }
    system("cls");
    printf("Aplicatia \"%s\" nu a fost gasita in catalog.\n", name);
    system("pause");
}

int Check_if_user_exists(const char *userfile,const char *username) {
    FILE *fp = fopen(userfile, "r");
    if (!fp) return 0;  
    char fileUser[16], filePass[30];
    while (fgets(fileUser, sizeof(fileUser), fp) &&
           fgets(filePass, sizeof(filePass), fp)) {
        
        fileUser[strcspn(fileUser, "\n")] = '\0';
        if (strcmp(fileUser, username) == 0) {
            fclose(fp);
            return 1;  
        }
    }
    fclose(fp);
    return 0;  
}

void appendToFile(const char *filename, const char *text) {
    FILE *file = fopen(filename, "a"); 
    if (!file) {
        perror("Nu am putut deschide fisierul");
        return;
    }
    fprintf(file, "%s\n", text);
    fclose(file);
}
void meniu(User current_user)
{   
    while (1)
    {
        char input;
        printf("Salut! ");
        setColor(14);
        printf("%s\n", current_user.username);
        setColor(7);
        printf("Meniu\n");
        printf("-------------------\n");
        printf("1. Aplicatii disponibile\n");
        printf("2.Instaleaza aplicatie\n");
        printf("3. Dezinstaleaza aplicatii\n");
        printf("4. Statistica aplicatiilor instalate\n");
        printf("5. Paraseste meniul\n");
        scanf("%c",&input);
        system("cls");
        
        
        switch(input)
        {
            
            case '1':
                app_catalog();
                break;
            case '2':
                install_apps();
                break;
            case '3':
                uninstall();
                break;
            case '4':
                app_stats();
                break;
            case '5':
                return;
            default:
                system("cls");
                break;
        }    
    }
}
void app_catalog()
{   char input;
    char line[100];
    app catalog[50];
    while(1)
    {
        FILE *file=fopen(catalog_aplicatii, "r");
        printf("Catalogul Aplicatiilor\n---------------------\n");
        int i=0;
    while(fgets(line,50,file))
    {
        line[strcspn(line,"\n")]='\0';
        strcpy(catalog[i].category,line);
        fgets(line,50,file);
        line[strcspn(line,"\n")]='\0';
        strcpy(catalog[i].name,line);
        i++;

    }
    fclose(file);
    viewAppsByCategory(catalog, i);

    printf("-------------------------------------------\n");
    printf("1. Pentru a iesi din submeniu\n");
    scanf("%c",&input);


   if(input=='1')
    {   
        system("cls");
        return;
    }
        system("cls");

    }
}



void install_apps() {
    char line[50];
    app catalog[50], catalog_inst[50], uninstalled[50];

    while (1) {
        
        int i = 0;
        FILE *f1 = fopen("app_catalog.txt", "r");
        if (!f1) { perror("Nu s-a putut deschide catalogul"); return; }
        while (i < 50 && fgets(line, sizeof line, f1)) {
            line[strcspn(line, "\n")] = '\0';
            strcpy(catalog[i].category, line);
            if (!fgets(line, sizeof line, f1)) break;
            line[strcspn(line, "\n")] = '\0';
            strcpy(catalog[i].name, line);
            i++;
        }
        fclose(f1);
        int total_catalog = i;

        
        int j = 0;
        FILE *f2 = fopen(inst, "r");
        if (!f2) { perror("nu am putut deschide fisierile instalate"); return; }
        while (j < 50 && fgets(line, sizeof line, f2)) {
            line[strcspn(line, "\n")] = '\0';
            strcpy(catalog_inst[j].category, line);
            if (!fgets(line, sizeof line, f2)) break;
            line[strcspn(line, "\n")] = '\0';
            strcpy(catalog_inst[j].name, line);
            j++;
        }
        fclose(f2);
        int total_installed = j;

        
        int k = 0;
        for (int a = 0; a < total_catalog; a++) {
            int found = 0;
            for (int b = 0; b < total_installed; b++) {
                if (strcmp(catalog[a].name, catalog_inst[b].name) == 0) {
                    found = 1;
                    break;
                }
            }
            if (!found && k < 50) {
                uninstalled[k++] = catalog[a];   
                printf("%s ", catalog[a].category);
                setColor(5);
                printf("%s\n", catalog[a].name);
                setColor(7);
            }
        }

        
        install_app_by_name(uninstalled, k);

        printf("Pentru a iesi din submeniu tastati \"1\": ");
        char c;
        scanf(" %c", &c);
        if (c == '1') {
            system("cls");
            return;
        }
        system("cls");
    }
}


    

void uninstall() {
    app installed[50];
    int total_installed;
    char line[100];
    char choice[50];

    while (1) {
        FILE *f = fopen(inst, "r");
        if (!f) {
            perror("Nu am putut deschide fisierul de aplicatii instalate");
            return;
        }
        total_installed = 0;
        while (total_installed < 50
               && fgets(line, sizeof line, f)
               && fgets(installed[total_installed].name, sizeof installed[0].name, f)) {
            line[strcspn(line, "\n")] = '\0';
            strcpy(installed[total_installed].category, line);
            installed[total_installed].name[strcspn(installed[total_installed].name, "\n")] = '\0';
            total_installed++;
        }
        fclose(f);

        printf("Dezinstalarea aplicatiilor\n");
        printf("--------------------------\n");
        for (int i = 0; i < total_installed; i++) {
            setColor(2);
            printf("%2d) %s : %s\n", i+1,
                   installed[i].category,
                   installed[i].name);
            setColor(7);
        }
        printf("\nIntroduceti numele aplicatiei de dezinstalat (sau \"1\" pentru iesire): ");
        scanf(" %[^\n]", choice);

        if (strcmp(choice, "1") == 0) {
            system("cls");
            return;
        }

        int idx = -1;
        for (int i = 0; i < total_installed; i++) {
            if (strcmp(installed[i].name, choice) == 0) {
                idx = i;
                break;
            }
        }

        if (idx < 0) {
            system("cls");
            printf("Aplicatia \"%s\" nu a fost gasita in lista instalata.\n", choice);
            system("pause");
            system("cls");
            continue;   
        }
        for (int j = idx; j < total_installed - 1; j++) {
            installed[j] = installed[j+1];
        }
        total_installed--;

        
        f = fopen(inst, "w");
        if (!f) {
            perror("Nu am putut rescrie fisierul instalate");
            return;
        }
        for (int i = 0; i < total_installed; i++) {
            fprintf(f, "%s\n%s\n",
                    installed[i].category,
                    installed[i].name);
        }
        fclose(f);

    
        printf("Aplicatia \"%s\" a fost dezinstalata cu succes.\n", choice);
        system("pause");
        system("cls");
       
    }
}
void app_stats() {
    app installed[100];
    int total = 0;
    char line[100];
    FILE *f = fopen(inst, "r");
    if (!f) {
        perror("Nu am putut deschide fisierul de aplicatii instalate");
        system("pause");
        system("cls");
        return;
    }
    while (total < 100
           && fgets(line, sizeof line, f)
           && fgets(installed[total].name, sizeof installed[0].name, f)) {
        line[strcspn(line, "\n")] = '\0';
        strcpy(installed[total].category, line);
        installed[total].name[strcspn(installed[total].name, "\n")] = '\0';
        total++;
    }
    fclose(f);

    char categories[100][50];
    int counts[100] = {0};
    int catCount = 0;

    for (int i = 0; i < total; i++) {
        int idx = -1;
        for (int j = 0; j < catCount; j++) {
            if (strcmp(categories[j], installed[i].category) == 0) {
                idx = j;
                break;
            }
        }
        if (idx == -1) {
        
            idx = catCount;
            strcpy(categories[catCount], installed[i].category);
            counts[catCount] = 0;
            catCount++;
        }
        counts[idx]++;
    }


    printf("Statistica aplicatiilor instalate per categorie\n");
    printf("------------------------------------------------\n");
    for (int c = 0; c < catCount; c++) {
        printf("%s : ", categories[c]);
        setColor(13);
        printf("%d\n",counts[c]);
        setColor(7);
    }
    printf("\n1. Pentru a iesi din submeniu\n");
    char input;
    do {
        scanf(" %c", &input);
    } while (input != '1');
    system("cls");
}

void viewAppsByCategory(app apps[], int n) {
    char seenCats[20][20];
    int  catCount = 0;

    
    for (int i = 0; i < n; i++) {
        int found = 0;
        for (int j = 0; j < catCount; j++) {
            if (strcmp(apps[i].category, seenCats[j]) == 0) {
                found = 1;
                break;
            }
        }
        if (!found) {
            strncpy(seenCats[catCount++], apps[i].category, 20);
        }
    }

    
    for (int c = 0; c < catCount; c++) {
        printf("\n=== %s ===\n", seenCats[c]);
        for (int i = 0; i < n; i++) {
            if (strcmp(apps[i].category, seenCats[c]) == 0) {
                setColor(12);
                printf("  %s\n", apps[i].name);
                setColor(7);
            }
        }
    }
}
