#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

typedef struct User {

    int nr, nr2;
    char Aplicatii[100][100]; //nr
    char AplicatiiInstalate[100][100]; //nr2
    char numeutilizator[50];
    int status;
}User;

void DeInstalare(User* user, int optiune, int j) {
    int i;

    if (optiune == 1) {  // Instalare
        strcpy(user->AplicatiiInstalate[user->nr2], user->Aplicatii[j]);
        user->nr2++;

        for (i = j; i < user->nr - 1; i++) {
            strcpy(user->Aplicatii[i], user->Aplicatii[i + 1]);
        }
        user->nr--;
    }

    else if (optiune == 2) {  // Dezinstalare
        strcpy(user->Aplicatii[user->nr], user->AplicatiiInstalate[j]);
        user->nr++;

        for (i = j; i < user->nr2 - 1; i++) {
            strcpy(user->AplicatiiInstalate[i], user->AplicatiiInstalate[i + 1]);
        }
        user->nr2--;
    }
}

void StoreData(User* user) {
    FILE* fout = fopen("zzzFisier.txt", "w");
    if (!fout) {
        printf("EROARE: Printing Failed \n");
        return;
    }

    fprintf(fout, "%s\n", user->numeutilizator);
    fprintf(fout, "%d\n", user->nr + user->nr2);

    for (int i = 0; i < user->nr2; i++) {
        char appName[100], version[50];
        char* lastSpace = strrchr(user->AplicatiiInstalate[i], ' ');

        if (lastSpace != NULL) {
            *lastSpace = '\0';
            strcpy(appName, user->AplicatiiInstalate[i]);
            strcpy(version, lastSpace + 1);
        }
        else {
            strcpy(appName, user->AplicatiiInstalate[i]);
            version[0] = '\0';
        }

        fprintf(fout, "%s\n", appName);
        fprintf(fout, "%s\n", version);
        fprintf(fout, "I\n");
    }

    for (int i = 0; i < user->nr; i++) {
        char appName[100], version[50];
        char* lastSpace = strrchr(user->Aplicatii[i], ' ');

        if (lastSpace != NULL) {
            *lastSpace = '\0';
            strcpy(appName, user->Aplicatii[i]);
            strcpy(version, lastSpace + 1);
        }
        else {
            strcpy(appName, user->Aplicatii[i]);
            version[0] = '\0';
        }

        fprintf(fout, "%s\n", appName);
        fprintf(fout, "%s\n", version);
        fprintf(fout, "N\n");
    }

    fclose(fout);
}

void debgg(User* user)
{
    int i; int a=0; if (user->status == 1) a = 1;
    if (user->numeutilizator[0] == '\0' || user->numeutilizator[0] == '\n' || user->numeutilizator[0] == ' ') user->status = 1;
    for (i = 0; i < user->nr; i++) {
        if (user->Aplicatii[i][0] == '\0' || user->Aplicatii[i][0] == '\n' || user->Aplicatii[i][0] == ' ') user->status = 1;
    }
    for (i = 0; i < user->nr2; i++) {
        if (user->AplicatiiInstalate[i][0] == '\0' || user->AplicatiiInstalate[i][0] == '\n' || user->AplicatiiInstalate[i][0] == ' ') user->status = 1;
    }
    if (a == 0 && user->status == 1) printf("EROARE: Data procesing failed");
}
void procesaredate(User* user)
{
    int n=0; //user->nr = 0; user->nr2 = 0;
    FILE* fin = fopen("zzzFisier.txt", "r"); char temp[100]; int i=1;
    if (fgets(temp, sizeof(temp), fin)) temp[strcspn(temp, "\n")] = 0; strcpy(user->numeutilizator, temp); //Nume
        if (fgets(temp, sizeof(temp), fin)) { n = atoi(temp); } //NR
        for (i = 0; i < n; i++)
        {
            char Nume[100], ver[10], bul;
            if (!fgets(Nume, sizeof(Nume), fin)) { user->status = 1; printf("EROARE: Data procesing failed"); break; } Nume[strcspn(Nume, "\n")] = 0;
            if (!fgets(ver, sizeof(ver), fin) || ver[0] == "\0" || ver[0] == '\n' || ver[0] == ' ') { user->status = 1; printf("EROARE: Data procesing failed"); break; } ver[strcspn(ver, "\n")] = 0;
            if (!fgets(temp, sizeof(temp), fin)) { user->status = 1; printf("EROARE: Data procesing failed"); break; } bul = temp[0];
            if (bul == 'I') { sprintf(user->AplicatiiInstalate[user->nr2++], "%s %s", Nume, ver); user->nr2; }
            else if(bul=='N') { sprintf(user->Aplicatii[user->nr++], "%s %s", Nume, ver); user->nr; }
            else {user->status = 1; printf("EROARE: Data procesing failed");}

        }user->nr = 0; user->nr2 = 0;
        for (i = 0; i < 100; i++) { user->nr++;  if (user->Aplicatii[i][0] == '\0') { user->nr--; break; } }
        for (i = 0; i < 100; i++) { user->nr2++;  if (user->AplicatiiInstalate[i][0] == '\0') { user->nr2--; break; } } 
        debgg(user);
}


void Meniu(User* user)
{
    if (user->status == 1) { return; }
    while (1) {
        system("cls");
        printf("-= Sistem gestionare aplicatii =-\n");
        printf("1. Aplicatii\n");
        printf("2. Profil\n");
        printf("3. Setari\n");
        printf("4. Iesire\n");
        int choice = 0; int choice2; int choice3; int i; char choicee[100];
        while (choice < 1 || choice > 4) {
            printf("Introduceti optiunea dorita ("); printf("\033[0;33mnr\033[0m"); printf("): ");
            scanf("%s", choicee); choice = atoi(choicee);
        }
        system("cls");
        while (choice == 1) {
            system("cls");
            printf("-= Aplicatii =-\n");
            printf("1. Instaleaza Aplicatii \n");
            printf("2. Dezinstaleaza Aplicatii \n");
            printf("3. Vezi Aplicatiile tale \n");
            printf("4. Iesire \n");
            choice2 = 0;
            if (choice2 != 4) {
                printf("Introduceti optiunea dorita ("); printf("\033[0;33mnr\033[0m"); printf("): ");
                scanf("%s", choicee); choice2 = atoi(choicee);
                if (choice2 == 1) {
                    while (1) {
                        system("cls");
                        printf("-= Instaleaza Aplicatii (\033[0;32m%d\033[0m) =-\n", user->nr);
                        for (i = 0; i < user->nr; i++) {
                            printf("%d. %s\n", i + 1, user->Aplicatii[i]);
                        }
                        printf("%d. Iesire\n", user->nr + 1);

                        printf("Introduceti optiunea dorita ("); printf("\033[0;33mnr\033[0m"); printf("): ");
                        scanf("%s", choicee); choice3 = atoi(choicee);

                        if (choice3 == user->nr + 1) break;
                        if (choice3 < 1 || choice3 > user->nr) {
                            printf("Optiune invalida. Incercati din nou.\n");
                            system("pause");
                            continue;
                        }
                        DeInstalare(user, 1, choice3 - 1);
                        printf("Aplicatia a fost instalata cu succes!\n");
                        //StoreData(user);
                        system("pause");
                    }
                }
                if (choice2 == 2)
                {
                    if (choice2 == 2) {
                        while (1) {
                            system("cls");
                            printf("-= Dezinstaleaza Aplicatii (\033[0;31m%d\033[0m) =-\n", user->nr2);
                            for (i = 0; i < user->nr2; i++) {
                                printf("%d. %s\n", i + 1, user->AplicatiiInstalate[i]);
                            }
                            printf("%d. Iesire\n", user->nr2 + 1);

                            printf("Introduceti optiunea dorita ("); printf("\033[0;33mnr\033[0m"); printf("): ");
                            scanf("%s", choicee); choice3 = atoi(choicee);

                            if (choice3 == user->nr2 + 1) break;
                            if (choice3 < 1 || choice3 > user->nr2) {
                                printf("Optiune invalida. Incercati din nou.\n");
                                system("pause");
                                continue;
                            }
                            DeInstalare(user, 2, choice3 - 1);
                            printf("Aplicatia a fost dezinstalata cu succes!\n");
                            //StoreData(user);
                            system("pause");
                        }
                    }
                }
                if (choice2 == 3)
                {
                    system("cls");
                    printf("-= Aplicatile Mele (\033[0;33m%d\033[0m) =-\n", user->nr2);
                    for (i = 0; i < user->nr2; i++)
                    {
                        printf("%d. %s\n", i + 1, user->AplicatiiInstalate[i]);
                    } printf("%d. Iesire\n", i + 1);
                    choice3 = 0;
                    while (choice3 != user->nr2 + 1) {
                        printf("Introduceti optiunea dorita ("); printf("\033[0;33mnr\033[0m"); printf("): ");
                        scanf("%s", choicee); choice3 = atoi(choicee);
                    }
                }
            }
            if (choice2 == 4) choice = 0;
        }
        if (choice == 2) {
            printf("-= Profil (\033[0;36m%s\033[0m) =-\n", user->numeutilizator);
            printf("1. Modifica nume utilzator \n");
            printf("2. Optiuni de plata \n");
            printf("3. Mesaje de la sistem \n");
            printf("4. Pentru Tine\n");
            printf("5. Iesire\n");
            choice2 = 0;
            while (choice2 != 5) {
                printf("Introduceti optiunea dorita ("); printf("\033[0;33mnr\033[0m"); printf("): ");
                scanf("%s", choicee); choice2 = atoi(choicee);
                if(choice2==2) printf("Serviciul de setarii este momentant \033[0;31mindisponibil\033[0m\n");
                if (choice2 == 1) {
                    printf("Introduceti un nou Nume de Utilizator (\033[0;36mnume\033[0m): "); scanf("%s", choicee); strcpy(user->numeutilizator,choicee); printf("\n");
                    choice2 = 5;
                }
                if (choice2 == 3) {
                    printf(" # Datele au fost accesate in '\033[0;32mzzzFisier.txt\033[0m' cu success\n");
                    printf(" # Programul a intampinat (\033[0;32m0\033[0m) erori pe percursul derularii\n");
                }
                if (choice2 == 4) {
                    time_t timp_cur = time(NULL); int secunde = timp_cur % 60;
                    printf("O zi \033[0;32mbuna\033[0m! Aplicatia recomandata este: ");
                    while (secunde >= user->nr2) {
                        secunde = secunde - (secunde / 2 + 1);
                        if (secunde < 0) secunde = -secunde;
                    }
                    printf("\033[0;33m%s\033[0m\n", user->AplicatiiInstalate[secunde]);
                }
            }
        }
        if (choice == 3) {
            printf("-= Setari (\033[0;36m%s\033[0m) =-\n", user->numeutilizator);
            printf("1. Salveaza\n");
            printf("2. Setari instalare\n");
            printf("3. Securitate\n");
            printf("4. Iesire\n");
            choice2 = 0;
            while (choice2 != 4) {
                printf("Introduceti optiunea dorita ("); printf("\033[0;33mnr\033[0m"); printf("): ");
                scanf("%s", choicee); choice2 = atoi(choicee);
                if (choice2 == 1) { printf("Datele au fost salvate cu \033[0;32msuccess\033[0m!\n"); StoreData(user); }
                if (choice2 > 1 && choice2 < 4)
                    printf("Serviciul de setarii este momentant \033[0;31mindisponibil\033[0m\n");
            }
        }
        if (choice == 4) { return 0; }
    }
}


int main() {
    User user; user.status = 0; user.nr = 0; memset(user.Aplicatii, 0, sizeof(user.Aplicatii)); user.nr2 = 0; memset(user.AplicatiiInstalate, 0, sizeof(user.Aplicatii)); //Totul initializat ca gol
    procesaredate(&user);
    Meniu(&user);
    StoreData(&user);
}