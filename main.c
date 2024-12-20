/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/cFiles/main.c to edit this template
 */

/* 
 * File:   main.c
 * Author: lguerriau
 *
 * Created on 20 décembre 2024, 09:54
 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <locale.h>

#define TAILLE 3

void afficherGrille(wchar_t grille[TAILLE][TAILLE]) {
    system("clear");
    for (int i = 0; i < TAILLE; i++) {
        for (int j = 0; j < TAILLE; j++) {
            printf(" %lc ", grille[i][j]);
            if (j < TAILLE - 1) {
                printf("￨");                  //Affichage de la grille
            }
        }
        printf("\n");
        if (i < TAILLE - 1) {
            printf("―――✛―――✛―――\n");
        }
    }
}

int verifierGagnant(wchar_t grille[TAILLE][TAILLE], wchar_t symbole) {    
    for (int i = 0; i < TAILLE; i++) {
        if (grille[i][0] == symbole && grille[i][1] == symbole && grille[i][2] == symbole) return 1; // Vérification des lignes et colonnes
        if (grille[0][i] == symbole && grille[1][i] == symbole && grille[2][i] == symbole) return 1;
    }     
    if (grille[0][0] == symbole && grille[1][1] == symbole && grille[2][2] == symbole) return 1; // Vérification des diagonales
    if (grille[0][2] == symbole && grille[1][1] == symbole && grille[2][0] == symbole) return 1;
    return 0;
}

int grillePleine(wchar_t grille[TAILLE][TAILLE]) {
    for (int i = 0; i < TAILLE; i++) {
        for (int j = 0; j < TAILLE; j++) { //Test pour l'égalité
            if (grille[i][j] == ' ') return 0;
        }
    }
    return 1;
}

void tourIA(wchar_t grille[TAILLE][TAILLE], wchar_t skinO) {
    int x, y;
    do {
        x = rand() % TAILLE;
        y = rand() % TAILLE; //Tour de L'IA
    } while (grille[x][y] != ' ');
    grille[x][y] = skinO;
}

void tourJoueur(wchar_t grille[TAILLE][TAILLE], wchar_t joueur, const char* pseudo) {
    int x, y;
    while (1) {
        printf("%s %lc , entrez votre choix (ligne colonne) : ", pseudo, joueur); //Tour du joueur
        scanf("%d %d", &x, &y);
        if (x >= 1 && x <= TAILLE && y >= 1 && y <= TAILLE && grille[x - 1][y - 1] == ' ') {
            grille[x - 1][y - 1] = joueur;
            break;
        } else {
            printf("Position invalide, essayez à nouveau.\n");
        }
    }
}

void afficherMenu() {
    printf("Bienvenue dans le jeu du Morpion !\n\n");
    printf("1. Jouer\n");
    printf("2. Règles du jeu\n"); //affichage du menu principal
    printf("3. Quitter\n\n");
    printf("Entrez votre choix : ");
}

void afficherMenuSkin() {
    printf("\nSélection des Skins :\n");
    printf(" 1. \U00002573    2. \U000026CC    3. \U0001FBBD    4. \U0001D465    5. \U0001F187    6. \U0001D6BE    7. \U0001F1FD    8. \U0001F7AE    9. \U00002717  \n10. \U000003B8   11. \U000024C2   12. \U0001F17E   13. \U0000FFFD   14. \U0001D7D8   15. \U00000C66   16. \U0001F1F4   17. \U0000A9F0   18. \U0001D2E0  \n");
    printf("Votre choix : "); //affichage du menu des skins
}

wchar_t selectionnerSkin() {
    int choix;
    wchar_t skins[] = {0x2573, 0x26CC, 0x1FBBD, 0x1D465, 0x1F187, 0x1D6BE, 0x1F1FD, 0x1F7AE, 0x2717, 0x03B8, 0x24C2, 0x1F17E, 0xFFFD, 0x1D7D8, 0x0C66, 0x1F1F4, 0xA9F0, 0x1D2E0};
    while (1) { //liste des skins possibles
        scanf("%d", &choix);
        if (choix >= 1 && choix <= 18) { //18 étant le numéro du dernier skin , d'autres valeurs ne marchent pas
            return skins[choix - 1];
        } else {
            printf("Choix invalide. Veuillez réessayer.\n");
        }
    }
}

void afficherRegles() {
    printf("\nRègles du jeu du Morpion :\n\n");
    printf("1. Le jeu se joue sur une grille de 3x3 cases.\n");
    printf("2. Deux joueurs s'affrontent : un joue avec les X et l'autre avec les O.\n");
    printf("3. Les joueurs placent leurs symboles à tour de rôle sur une case vide.\n"); //affichage des règles
    printf("4. Le premier joueur à aligner 3 symboles horizontalement, verticalement ou en diagonale gagne.\n");
    printf("5. Si toutes les cases sont remplies sans alignement, la partie est déclarée nulle.\n\n");
}

int main() {
    setlocale(LC_ALL, "");

    wchar_t grille[TAILLE][TAILLE];
    srand(time(NULL));

    int choix;
    while (1) {
        afficherMenu();
        scanf("%d", &choix);

        if (choix == 1) {
            break;
        } else if (choix == 2) {
            afficherRegles();
            printf("Appuyez sur Entrée pour revenir au menu principal...\n");
            getchar(); // Consommer le saut de ligne précédent
            getchar(); // Attendre que l'utilisateur appuie sur Entrée
        } else if (choix == 3) {
            printf("Merci d'avoir joué ! À bientôt !\n\n");
            return 0;
        } else {
            printf("Choix invalide, veuillez réessayer.\n\n");
        }
    }

    int mode;
    char pseudo1[50], pseudo2[50]; //la taille max des pseudos est mise a 50
    wchar_t skinX, skinO;

    printf("Entrez le pseudo du Joueur 1 : ");
    scanf("%s", pseudo1);
    afficherMenuSkin(); //affiche le menu des skins pour le joueur 1
    printf("%s, choisissez votre skin pour X : \n", pseudo1);
    skinX = selectionnerSkin();

    printf("Choisissez le mode de jeu : \n1. Contre l'IA  \n2. 2 Joueurs\n");
    scanf("%d", &mode);

    if (mode == 2) {
        printf("Entrez le pseudo du Joueur 2 : ");
        scanf("%s", pseudo2);
        afficherMenuSkin(); //affiche le menu des skins pour le joueur 2 si il n'est pas IA
        printf("%s, choisissez votre skin pour O : \n", pseudo2);
        skinO = selectionnerSkin();
    } else {
        strcpy(pseudo2, "IA");
        skinO = 'O'; // Par défaut pour l'IA joue le skin de base
    }

    int scoreJoueur1 = 0, scoreJoueur2 = 0;

    while (1) {
        int joueurActuel = 1; // 1 pour joueur 1, 2 pour joueur 2 ou IA
        for (int i = 0; i < TAILLE; i++) {
            for (int j = 0; j < TAILLE; j++) {
                grille[i][j] = ' ';
            }
        }

        while (1) {
            afficherGrille(grille);

            if (mode == 1 && joueurActuel == 2) {
                tourIA(grille, skinO); //c'est le tour de l'IA/Joueur 2
            } else {
                tourJoueur(grille, (joueurActuel == 1) ? skinX : skinO, (joueurActuel == 1) ? pseudo1 : pseudo2); //c'est le tour du joueur 1
            }

            if (verifierGagnant(grille, (joueurActuel == 1) ? skinX : skinO)) {
                afficherGrille(grille);
                printf("\n%s %lc a gagné !\n", (joueurActuel == 1) ? pseudo1 : pseudo2, (joueurActuel == 1) ? skinX : skinO); //Message de victoire

                if (joueurActuel == 1) {
                    scoreJoueur1++; //Si le joueur 1 gagne , augmenter son score
                } else {
                    scoreJoueur2++;//Si le joueur 2 gagne , augmenter son score
                }

                break;
            }
            if (grillePleine(grille)) {
                afficherGrille(grille);
                printf("\nMatch nul !\n"); //Message Match nul
                break;
            }

            joueurActuel = (joueurActuel == 1) ? 2 : 1; //Changement du tour de quel joueur
        }

        printf("Scores : %s %lc = %d, %s %lc = %d\n", pseudo1, skinX, scoreJoueur1, pseudo2, skinO, scoreJoueur2);
        printf("Voulez-vous rejouer ? (1 pour Oui, 0 pour Non) : "); //Rejouer ?
        int rejouer;
        scanf("%d", &rejouer);
        if (!rejouer) {
            break;
        }
    }

    printf("Merci d'avoir joué ! Scores finaux : %s %lc = %d, %s %lc = %d\n", pseudo1, skinX, scoreJoueur1, pseudo2, skinO, scoreJoueur2); //Message de fermeture
    return 0;
}


