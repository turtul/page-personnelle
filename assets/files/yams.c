/**
* \page Général 
* 
* \author Chardès
* \version 1.0
* \date 10 novembre 2021
* Ce programme permet à deux joueurs de jouer au jeu du yams.
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <time.h>

/**
* \typedef chaine20
* \brief chaine de 20 caractères.
*/
typedef char chaine20[21];

//Constantes conservant les dés en semi-graphique.
const char DE1[54] = "┌------┐\n|      |\n|  o   |\n|      |\n└------┘\n";
const char DE2[54] = "┌------┐\n|    o |\n|      |\n| o    |\n└------┘\n";
const char DE3[54] = "┌------┐\n|    o |\n|  o   |\n| o    |\n└------┘\n";
const char DE4[54] = "┌------┐\n| o  o |\n|      |\n| o  o |\n└------┘\n";
const char DE5[54] = "┌------┐\n| o  o |\n|  o   |\n| o  o |\n└------┘\n";
const char DE6[54] = "┌------┐\n| o  o |\n| o  o |\n| o  o |\n└------┘\n";

//Constante conservant le titre et le remerciment en semi-graphique.
const char TITRE[175] = "\t__   _____  ___  ___ _____ \n\t\\ \\ / / _ \\ |  \\/  |/  ___|\n\t \\ V / /_\\ \\| .  . |\\ `--. \n\t  \\ /|  _  || |\\/| | `--. \\\n\t  | || | | || |  | |/\\__/ /\n\t  \\_/\\_| |_/\\_|  |_/\\____/\n\n";
const char MERCI[623] = "\t___  ___ ___________  _____ _____  ______ _  ___  _   _  _____ ___________     ___  _____ _   _ _____\n\t|  \\/  ||  ___| ___ \\/  __ \\_   _| |  _  ( )/ _ \\| | | ||  _  |_   _| ___ \\   |_  ||  _  | | | |  ___|\n\t| .  . || |__ | |_/ /| /  \\/ | |   | | | |// /_\\ \\ | | || | | | | | | |_/ /     | || | | | | | | |__  \n\t| |\\/| ||  __||    / | |     | |   | | | | |  _  | | | || | | | | | |    /      | || | | | | | |  __| \n\t| |  | || |___| |\\ \\ | \\__/\\_| |_  | |/ /  | | | \\ \\_/ /\\ \\_/ /_| |_| |\\ \\  /\\__/ /\\ \\_/ / |_| | |___ \n\t\\_|  |_/\\____/\\_| \\_| \\____/\\___/  |___/   \\_| |_/\\___/  \\___/ \\___/\\_| \\_| \\____/  \\___/ \\___/\\____/\n";

//Constantes qui servent à choisir une réponse (o/n) quand une question est posée.
const char OUI[2] = "o";
const char NON[2] = "n";

//Constantes déffinisant le nombre tour de jeu.
const int NBTOUR = 1;
const int NBJEU = 13;

//Constantes utiles pour le bon déroulement du jeu.
const int BONUS = 35;
const int ACCBONUS = 62;
const int NBLANCERMAX = 3;
const int NBDES = 5;
const int CARMAX = 21;
const int NUMDES = 6;
const int INITVAR = -1;
const int FULL = 25;
const int PETITE = 30;
const int GRANDE = 40;
const int YAMS = 50;

/***************************************
 * ENTETES DES FONCTIONS ET PROCEDURES *
 ***************************************/
void nom(chaine20 *nom1, chaine20 *nom2);
void afficherFeuille(chaine20 joueur, int tot1, int tot2, int tot3, int tot4, int tot5, int tot6, int brelan, int carre, int full, int petite, int grande, int yams, int chance, int tour);
void lancerDe(int *nbDe);
void afficherDe(int nbDe1, int nbDe2, int nbDe3, int nbDe4, int nbDe5);
void choixDe(int *nbDe1, int *nbDe2, int *nbDe3, int *nbDe4, int *nbDe5);
void affecterDes(int nbDe1, int nbDe2, int nbDe3, int nbDe4, int nbDe5, int *tot1, int *tot2, int *tot3, int *tot4, int *tot5, int *tot6, int *brelan, int *carre, int *full, int *petite, int *grande, int *yams, int *chance);
int f_tot1(int nbDe1, int nbDe2, int nbDe3, int nbDe4, int nbDe5);
int f_tot2(int nbDe1, int nbDe2, int nbDe3, int nbDe4, int nbDe5);
int f_tot3(int nbDe1, int nbDe2, int nbDe3, int nbDe4, int nbDe5);
int f_tot4(int nbDe1, int nbDe2, int nbDe3, int nbDe4, int nbDe5);
int f_tot5(int nbDe1, int nbDe2, int nbDe3, int nbDe4, int nbDe5);
int f_tot6(int nbDe1, int nbDe2, int nbDe3, int nbDe4, int nbDe5);
bool f_bonus(int tot1, int tot2, int tot3, int tot4, int tot5, int tot6);
int f_brelan(int nbDe1, int nbDe2, int nbDe3, int nbDe4, int nbDe5);
int f_carre(int nbDe1, int nbDe2, int nbDe3, int nbDe4, int nbDe5);
int f_full(int nbDe1, int nbDe2, int nbDe3, int nbDe4, int nbDe5);
int f_petite(int nbDe1, int nbDe2, int nbDe3, int nbDe4, int nbDe5);
int f_grande(int nbDe1, int nbDe2, int nbDe3, int nbDe4, int nbDe5);
int f_yams(int nbDe1, int nbDe2, int nbDe3, int nbDe4, int nbDe5);
int f_chance(int nbDe1, int nbDe2, int nbDe3, int nbDe4, int nbDe5);
void trisDes(int tableau[5]);

/***************************************
 *         PROGRAMME PRINCIPAL         *
 ***************************************/
/**
* \fn int main()
* \brief Programme principal.
* \return Code de sortie du programme (0 : sortie normale).
* 
* Le programme principal, il appelle toutes les procédures et les fonctions permettant de jouer au yams.
*/
int main() {
    //Initialisation des variables de noms des 2 joueurs.
    chaine20 joueur1, joueur2, joueurActif;

    //Initialisation des variables des scores de chaque personne pour chaque combinaison et mise à 0.
    int total1_1, total2_1, total3_1, total4_1, total5_1, total6_1, bre_1, car_1, ful_1, pet_1, gra_1, yam_1, cha_1, total_1, total1_2, total2_2, total3_2, total4_2, total5_2, total6_2, bre_2, car_2, ful_2, pet_2, gra_2, yam_2, cha_2, total_2;
    total1_1 = -1;
    total2_1 = -1;
    total3_1 = -1;
    total4_1 = -1;
    total5_1 = -1;
    total6_1 = -1;
    bre_1 = -1;
    car_1 = -1;
    ful_1 = -1;
    pet_1 = -1;
    gra_1 = -1;
    yam_1 = -1;
    cha_1 = -1;
    total1_2 = -1;
    total2_2 = -1;
    total3_2 = -1;
    total4_2 = -1;
    total5_2 = -1;
    total6_2 = -1;
    bre_2 = -1;
    car_2 = -1;
    ful_2 = -1;
    pet_2 = -1;
    gra_2 = -1;
    yam_2 = -1;
    cha_2 = -1;

    //Initialisation des variables des dés.
    int de1, de2, de3, de4, de5;

    //Initialisation des variables relatives aux lancés de dés.
    char lancer[2];
    int nbLancer;

    //Initialisation des variables des boucles pour.
    int jeu, tour;
    //tirage pseudo aleatoire d'un nombre
    srand(time(NULL));
    //affichage de l'écran titre
    printf("%s",TITRE);
    //demande des noms des joueurs
    nom(&joueur1, &joueur2);
    //netpyage de l'écran
    system("clear");
    //boucle de jeu principal tourne 13 fois
    for (jeu = 0; jeu < NBJEU; jeu++){
        //le nombre de lancer corespond au nombre de fois ou les dés on été tiré (variable incrementer à chaque tirage)
        nbLancer = 0;
        //boucle de jeu secondaire : représente l'alternance des tours des joueurs
        for (tour = 0; tour < NBTOUR; tour++){
            //tour du joueur 1
            strcpy(joueurActif, joueur1);
            //alternative servant à savoir quel joueur doit jouer
            if (strcmp(joueurActif,joueur1) == 0){
                //affichage de la feuille du joueur actif au début de son tour
                afficherFeuille(joueurActif, total1_1, total2_1, total3_1, total4_1, total5_1, total6_1, bre_1, car_1, ful_1, pet_1, gra_1, yam_1, cha_1, jeu);
                //demande de lancer les dés sans quoi le jeu ne commence pas
                do {
                    printf("Entrée o pour lancer les dés.\n");
                    scanf("%s",lancer);
                } while (strcmp(lancer, OUI) != 0);
                //premier lancer des 5 dés
                lancerDe(&de1);
                lancerDe(&de2);
                lancerDe(&de3);
                lancerDe(&de4);
                lancerDe(&de5);
                //simple affichege semi-graphique des dés
                afficherDe(de1, de2, de3, de4, de5);
                nbLancer = 1;
                do {
                    printf("Voulez vous relancer certains dés, vous avez fait %d lancés ? (o/n)\n",nbLancer);
                    scanf("%s",lancer);
                } while((strcmp(lancer, OUI) != 0) && (strcmp(lancer, NON) != 0));
                //relance des dés en fonction du choix du joueur
                if (strcmp(lancer, OUI) == 0){
                    //boucle tournant tant que le joueur souhaite continuer à relancer les dés et tant que le nombre de lancer n'a pas été dépassé
                    while ((nbLancer < NBLANCERMAX) && (strcmp(lancer, OUI) == 0)){
                        //choix des dés à relancer
                        choixDe(&de1, &de2, &de3, &de4, &de5);
                        nbLancer = nbLancer + 1;
                        //verification que le nombre de lancer max n'a pas été dépassé
                        if (nbLancer < NBLANCERMAX){
                            do {
                                printf("Voulez vous relancer certains dés, vous avez fait %d lancés ? (o/n)\n",nbLancer);
                                scanf("%s",lancer);
                            } while((strcmp(lancer, OUI) != 0) && (strcmp(lancer, NON) != 0));
                        }
                    }
                }
                //affectation des dés tirés par le joueur actif
                affecterDes(de1, de2, de3, de4, de5, &total1_1, &total2_1, &total3_1, &total4_1, &total5_1, &total6_1, &bre_1, &car_1, &ful_1, &pet_1, &gra_1, &yam_1, &cha_1);
                //affichage de la feuille de marque du ojeur actif à la fin de son tour
                afficherFeuille(joueurActif, total1_1, total2_1, total3_1, total4_1, total5_1, total6_1, bre_1, car_1, ful_1, pet_1, gra_1, yam_1, cha_1, jeu);
            }
            //tour du joueur 2
            //mise en pause du programme et netoyage de l'écran
            system("read -p 'Pressez entrée pour continuer...' c");
            system("clear");
            strcpy(joueurActif, joueur2);
            //alternative servant à savoir quel joueur doit jouer
            if (strcmp(joueurActif,joueur2) == 0){
                //affichage de la feuille du joueur actif au début de son tour
                afficherFeuille(joueurActif, total1_2, total2_2, total3_2, total4_2, total5_2, total6_2, bre_2, car_2, ful_2, pet_2, gra_2, yam_2, cha_2, jeu);
                //demande de lancer les dés sans quoi le jeu ne commence pas
                do {
                    printf("Entrée o pour lancer les dés.\n");
                    scanf("%s",lancer);
                } while (strcmp(lancer, OUI) != 0);
                //premier lancer des 5 dés
                lancerDe(&de1);
                lancerDe(&de2);
                lancerDe(&de3);
                lancerDe(&de4);
                lancerDe(&de5);
                //simple affichege semi-graphique des dés
                afficherDe(de1, de2, de3, de4, de5);
                nbLancer = 1;
                do {
                    printf("Voulez vous relancer certains dés, vous avez fait %d lancés ? (o/n)\n",nbLancer);
                    scanf("%s",lancer);
                } while((strcmp(lancer, OUI) != 0) && (strcmp(lancer, NON) != 0));
                //relance des dés en fonction du choix du joueur
                if (strcmp(lancer, OUI) == 0){
                    //boucle tournant tant que le joueur souhaite continuer à relancer les dés et tant que le nombre de lancer n'a pas été dépassé
                    while ((nbLancer < NBLANCERMAX) && (strcmp(lancer, OUI) == 0)){
                        //choix des dés à relancer
                        choixDe(&de1, &de2, &de3, &de4, &de5);
                        nbLancer = nbLancer + 1;
                        //verification que le nombre de lancer max n'a pas été dépassé
                        if (nbLancer < NBLANCERMAX){
                            do {
                                printf("Voulez vous relancer certains dés, vous avez fait %d lancés ? (o/n)\n",nbLancer);
                                scanf("%s",lancer);
                            } while((strcmp(lancer, OUI) != 0) && (strcmp(lancer, NON) != 0));
                        }
                    }
                }
                //affectation des dés tirés par le joueur actif
                affecterDes(de1, de2, de3, de4, de5, &total1_2, &total2_2, &total3_2, &total4_2, &total5_2, &total6_2, &bre_2, &car_2, &ful_2, &pet_2, &gra_2, &yam_2, &cha_2);
                //affichage de la feuille de marque du ojeur actif à la fin de son tour
                afficherFeuille(joueurActif, total1_2, total2_2, total3_2, total4_2, total5_2, total6_2, bre_2, car_2, ful_2, pet_2, gra_2, yam_2, cha_2, jeu);
            }
            system("read -p 'Pressez entrée pour continuer...' c");
            system("clear");
        }
    }
    //affichage des feuilles de scores avec les totaux puisque c'est la fin des tours
    printf("Résumé des scores :\n");
    afficherFeuille(joueur1, total1_1, total2_1, total3_1, total4_1, total5_1, total6_1, bre_1, car_1, ful_1, pet_1, gra_1, yam_1, cha_1, jeu);
    afficherFeuille(joueur2, total1_2, total2_2, total3_2, total4_2, total5_2, total6_2, bre_2, car_2, ful_2, pet_2, gra_2, yam_2, cha_2, jeu);
    //calcul du score total du joueur 1
    total_1 = total1_1 + total2_1 + total3_1 + total4_1 + total5_1 + total6_1 + bre_1 + car_1 + ful_1 + pet_1 + gra_1 + yam_1 + cha_1;
    //calcul du score total du joueur 2
    total_2 = total1_2 + total2_2 + total3_2 + total4_2 + total5_2 + total6_2 + bre_2 + car_2 + ful_2 + pet_2 + gra_2 + yam_2 + cha_2;
    //determination du vainceur avec une alternative qui regarde le score le plus grand
    if (total_1 > total_2){
        printf("\n%s gagne avec un score total de : %d\n",joueur1,total_1);
        printf("Le score de %s est de : %d\n",joueur2,total_2);
    } else if (total_1 < total_2){
        printf("\n%s gagne avec un score total de : %d\n",joueur2,total_2);
        printf("Le score de %s est de : %d\n",joueur1,total_1);
    } else {
        //prise en compte du cas ou les score sont ex aequo
        printf("\n%s et %s sont ex aequo avec un score total de : %d\n",joueur1, joueur2, total_1);
    }
    system("read -p 'Pressez entrée pour continuer...' c");
    system("clear");
    printf("%s",MERCI);
    return EXIT_SUCCESS;
}

/***************************************
 *        PROCEDURE ET FONCTION        *
 ***************************************/
/**
* \fn void nom(char[20] *nom1, char[20] *nom2)
* \brief Procédure qui demande les noms des deux joueurs.
* \param nom1 : paramètre d'entrée sortie qui permet à l'utilisateur de choisir son nom.
* \param nom2 : paramètre d'entrée sortie qui permet à l'utilisateur de choisir son nom.
*/
void nom(chaine20 *nom1, chaine20 *nom2){
    //boucles permetant de s'assurer que le nom de joueur ne dépasse pas le nb max de caractères
    do
    {
        printf("Donnez le nom du joueur 1 : ");
        scanf("%s",*nom1);
    } while (strlen(*nom1) >= CARMAX);
    do
    {
        printf("Donnez le nom du joueur 2 : ");
        scanf("%s",*nom2);
    } while (strlen(*nom2) >= CARMAX);
}

/**
* \fn void afficherFeuille(chaine20 joueur, int tot1, int tot2, int tot3, int tot4, int tot5, int tot6, int brelan, int carre, int full, int petite, int grande, int yams, int chance, int tour)
* \brief Procédure qui affiche la feuille de marque avec une variable pour chaque ligne ainsi que les totaux calculé par cette procédure en grâce aux paramètres d'entrés.
* \param joueur : variable stockant le nom du joueur actif.
* \param tot1 : variable stockant le score de joueur actif pour la combianson : tot1.
* \param tot2 : variable stockant le score de joueur actif pour la combianson : tot2.
* \param tot3 : variable stockant le score de joueur actif pour la combianson : tot3.
* \param tot4 : variable stockant le score de joueur actif pour la combianson : tot4.
* \param tot5 : variable stockant le score de joueur actif pour la combianson : tot5.
* \param tot6 : variable stockant le score de joueur actif pour la combianson : tot6.
* \param brelan : variable stockant le score de joueur actif pour la combianson : brelan.
* \param carre : variable stockant le score de joueur actif pour la combianson : carre.
* \param full : variable stockant le score de joueur actif pour la combianson : full.
* \param petite : variable stockant le score de joueur actif pour la combianson : petite.
* \param grande : variable stockant le score de joueur actif pour la combianson : grande.
* \param yams : variable stockant le score de joueur actif pour la combianson : yams.
* \param chance : variable stockant le score de joueur actif pour la combianson : chance.
* \param jeu : variable stockant nombre de tour (tot 13) depuis le debut du jeu.
*/
void afficherFeuille(chaine20 joueur, int tot1, int tot2, int tot3, int tot4, int tot5, int tot6, int brelan, int carre, int full, int petite, int grande, int yams, int chance, int tour){
    //affichage du nom de joueur dont c'est le tour de jouer
    printf("Feuille de marque de %s :\n",joueur);
    printf("┌-----------------------------┐\n");
    //chaque emplacement de chaque varible de chaque ligne de la feuille de marque est affiché vide si la varible de la ligne est non-attribuée
    if (tot1 >= 0) {
        printf("|1 [total de 1]           |%3d|\n",tot1);
    } else {
        printf("|1 [total de 1]           |   |\n");
    }
    if (tot2 >= 0) {
        printf("|2 [total de 2]           |%3d|\n",tot2);
    } else {
        printf("|2 [total de 2]           |   |\n");
    }
    if (tot3 >= 0) {
        printf("|3 [total de 3]           |%3d|\n",tot3);
    } else {
        printf("|3 [total de 3]           |   |\n");
    }
    if (tot4 >= 0) {
        printf("|4 [total de 5]           |%3d|\n",tot4);
    } else {
        printf("|4 [total de 5]           |   |\n");
    }
    if (tot5 >= 0) {
        printf("|5 [total de 5]           |%3d|\n",tot5);
    } else {
        printf("|5 [total de 5]           |   |\n");
    }
    if (tot6 >= 0) {
        printf("|6 [total de 6]           |%3d|\n",tot6);
    } else {
        printf("|6 [total de 6]           |   |\n");
    }
    //alternative qui s'assure que c'est bien le dernier tour pour pouvoir afficher le total inférieur
    if (tour == NBJEU){
        //alternative qui determine si le bonnus est vrai
        if (f_bonus(tot1, tot2, tot3, tot4, tot5, tot6) == true){
            printf("|Bonus                    |%3d|",BONUS);
            printf("|Total inférieur          |%3d|\n",tot1 + tot2 + tot3 + tot4 + tot5 + tot6 + BONUS);
        } else {
            printf("|Bonus                    |   |\n");
            printf("|Total inférieur          |%3d|\n",tot1 + tot2 + tot3 + tot4 + tot5 + tot6);
        }
    } else {
        printf("|Bonus                    |   |\n");
        printf("|Total inférieur          |   |\n");
    }
    printf("|-----------------------------|\n");
    if (brelan >= 0) {
        printf("|Brelan       [total]     |%3d|\n",brelan);
    } else {
        printf("|Brelan       [total]     |   |\n");
    }
    if (carre >= 0) {
        printf("|Carré        [total]     |%3d|\n",carre);
    } else {
        printf("|Carré        [total]     |   |\n");
    }
    if (full >= 0) {
        printf("|Full House   [25]        |%3d|\n",full);
    } else {
        printf("|Full House   [25]        |   |\n");
    }
    if (petite >= 0) {
        printf("|Petite suite [30]        |%3d|\n",petite);
    } else {
        printf("|Petite suite [30]        |   |\n");
    }
    if (grande >= 0) {
        printf("|Grande suite [40]        |%3d|\n",grande);
    } else {
        printf("|Grande suite [40]        |   |\n");
    }
    if (yams >= 0) {
        printf("|Yams         [50]        |%3d|\n",yams);
    } else {
        printf("|Yams         [50]        |   |\n");
    }
    if (chance >= 0) {
        printf("|Chance       [total]     |%3d|\n",chance);
    } else {
        printf("|Chance       [total]     |   |\n");
    }
    //alternative qui s'assure que c'est bien le dernier tour pour pouvoir afficher le total supérieur
    if (tour == NBJEU){
        printf("|Total supérieur          |%3d|\n",brelan + carre + full + petite + grande + yams + chance);
    } else {
        printf("|Total supérieur          |   |\n");
    }
    printf("|-----------------------------|\n");
    //alternative qui s'assure que c'est bien le dernier tour pour pouvoir afficher le total
    if (tour == NBJEU){
        printf("|Total                    |%3d|\n",tot1 + tot2 + tot3 + tot4 + tot5 + tot6 + brelan + carre + full + petite + grande + yams + chance);
    } else {
        printf("|Total                    |   |\n");
    }
    printf("└-----------------------------┘\n");
}

/**
* \fn void lancerDe(int *nbDe, int numDe)
* \brief Procédure qui attribue un nombre aléatoire au dé en entrée sortie.
* \param nbDe : paramètre d'entrée sortie qui permet de tirer un nombre alétoire et de l'affecter à un dé.
*/
void lancerDe(int *nbDe) {
    //attribue un nombre pseudo-aléatoire entre 1 et 6 à un dé
    *nbDe = (rand() % NUMDES) + 1;
}

/**
* \fn void afficherDe(int nbDe1, int nbDe2, int nbDe3, int nbDe4, int nbDe5)
* \brief Procédure qui affiche le nombre de chaque dé.
* \param nbDe1 : paramètre qui indique à la procédure quel est la valeur du dé n°1.
* \param nbDe2 : paramètre qui indique à la procédure quel est la valeur du dé n°2.
* \param nbDe3 : paramètre qui indique à la procédure quel est la valeur du dé n°3.
* \param nbDe4 : paramètre qui indique à la procédure quel est la valeur du dé n°4.
* \param nbDe5 : paramètre qui indique à la procédure quel est la valeur du dé n°5.
*/
void afficherDe(int nbDe1, int nbDe2, int nbDe3, int nbDe4, int nbDe5){
    //5 switch permettent de couvrir tous les cas pour afficher les dés dans toutes les situations
    printf("Dés n°1 :\n");
    switch (nbDe1) {
    case 1:
        printf("%s",DE1);
        break;
    case 2:
        printf("%s",DE2);
        break;
    case 3:
        printf("%s",DE3);
        break;
    case 4:
        printf("%s",DE4);
        break;
    case 5:
        printf("%s",DE5);
        break;
    case 6:
        printf("%s",DE6);
        break;
    default:
        break;
    }
    printf("Dés n°2 :\n");
    switch (nbDe2) {
    case 1:
        printf("%s",DE1);
        break;
    case 2:
        printf("%s",DE2);
        break;
    case 3:
        printf("%s",DE3);
        break;
    case 4:
        printf("%s",DE4);
        break;
    case 5:
        printf("%s",DE5);
        break;
    case 6:
        printf("%s",DE6);
        break;
    default:
        break;
    }
    printf("Dés n°3 :\n");
    switch (nbDe3) {
    case 1:
        printf("%s",DE1);
        break;
    case 2:
        printf("%s",DE2);
        break;
    case 3:
        printf("%s",DE3);
        break;
    case 4:
        printf("%s",DE4);
        break;
    case 5:
        printf("%s",DE5);
        break;
    case 6:
        printf("%s",DE6);
        break;
    default:
        break;
    }
    printf("Dés n°4 :\n");
    switch (nbDe4) {
    case 1:
        printf("%s",DE1);
        break;
    case 2:
        printf("%s",DE2);
        break;
    case 3:
        printf("%s",DE3);
        break;
    case 4:
        printf("%s",DE4);
        break;
    case 5:
        printf("%s",DE5);
        break;
    case 6:
        printf("%s",DE6);
        break;
    default:
        break;
    }
    printf("Dés n°5 :\n");
    switch (nbDe5) {
    case 1:
        printf("%s",DE1);
        break;
    case 2:
        printf("%s",DE2);
        break;
    case 3:
        printf("%s",DE3);
        break;
    case 4:
        printf("%s",DE4);
        break;
    case 5:
        printf("%s",DE5);
        break;
    case 6:
        printf("%s",DE6);
        break;
    default:
        break;
    }
}

/**
* \fn void choixDe(int *nbDe1, int *nbDe2, int *nbDe3, int *nbDe4, int *nbDe5)
* \brief Procédure qui demande quels dés relancer et appelle lancerDe pour chaque dé à relancer à l'aide d'un switch.
* \param nbDe1 : paramètre qui permet indique à la procédure quel est la valeur du dé n°1.
* \param nbDe2 : paramètre qui permet indique à la procédure quel est la valeur du dé n°2.
* \param nbDe3 : paramètre qui permet indique à la procédure quel est la valeur du dé n°3.
* \param nbDe4 : paramètre qui permet indique à la procédure quel est la valeur du dé n°4.
* \param nbDe5 : paramètre qui permet indique à la procédure quel est la valeur du dé n°5.
*/
void choixDe(int *nbDe1, int *nbDe2, int *nbDe3, int *nbDe4, int *nbDe5){
    int numDe;
    printf("Donnez les numéros des dés à relancer séparer par des espaces et mettez 0 pour les dés que vous ne voulez pas relancer (ex : 2 5 3 0 0)\n");
    //initialisation des varibles servant à savoir si un dé a déjà été relancer et donc d'interdir ce relancement
    bool dejaLancerDe1, dejaLancerDe2, dejaLancerDe3, dejaLancerDe4, dejaLancerDe5;
    dejaLancerDe1 = false;
    dejaLancerDe2 = false;
    dejaLancerDe3 = false;
    dejaLancerDe4 = false;
    dejaLancerDe5 = false;
    //boucle qui permet de faire 5 scanf pour chaque dé a relancer ou non en suivant la consigne donnée dans le précédent printf
    for (int i = 0; i < NBDES; i++)
    {
        scanf("%d",&numDe);
        //switch gérant les arrivé des numéro des dés lus au clavier et relancer le dé corespondant
        switch (numDe)
        {
        case 1:
            if (dejaLancerDe1 == false){
                lancerDe(&*nbDe1);
                dejaLancerDe1 = true;
                printf("Le dé n°1 a été relancé.\n");
            }
            break;
        case 2:
            if (dejaLancerDe2 == false){
                lancerDe(&*nbDe2);
                dejaLancerDe2 = true;
                printf("Le dé n°2 a été relancé.\n");
            }
            break;
        case 3:
            if (dejaLancerDe3 == false){
                lancerDe(&*nbDe3);
                dejaLancerDe3 = true;
                printf("Le dé n°3 a été relancé.\n");
            }
            break;
        case 4:
            if (dejaLancerDe4 == false){
                lancerDe(&*nbDe4);
                dejaLancerDe4 = true;
                printf("Le dé n°4 a été relancé.\n");
            }
            break;
        case 5:
            if (dejaLancerDe5 == false){
                lancerDe(&*nbDe5);
                dejaLancerDe5 = true;
                printf("Le dé n°5 a été relancé.\n");
            }
            break;
        case 0:
            break;
        default:
            break;
        }
    }
    //affichage de tout les dés
    afficherDe(*nbDe1, *nbDe2, *nbDe3, *nbDe4, *nbDe5);
}

/**
* \fn void affecterDes(int nbDe1, int nbDe2, int nbDe3, int nbDe4, int nbDe5, int *tot1, int *tot2, int *tot3, int *tot4, int *tot5, int *tot6, int *brelan, int *carre, int *full, int *petite, int *grande, int *yams, int *chance)
* \brief Procédure qui demande quel combinaison remplir avec les dés, si la ligne est déjà remplie alors un message d'erreur est affiché si non la fonction de la combinaison choisie est appelée puis cette procédure attribue la valeur retournée par la fonction à la variable représentant cette combinaison
* \param nbDe1 : paramètre qui permet indique à la procédure quel est la valeur du dé n°1.
* \param nbDe2 : paramètre qui permet indique à la procédure quel est la valeur du dé n°2.
* \param nbDe3 : paramètre qui permet indique à la procédure quel est la valeur du dé n°3.
* \param nbDe4 : paramètre qui permet indique à la procédure quel est la valeur du dé n°4.
* \param nbDe5 : paramètre qui permet indique à la procédure quel est la valeur du dé n°5.
* \param tot1 : variable stockant le score de joueur actif pour la combianson : tot1.
* \param tot2 : variable stockant le score de joueur actif pour la combianson : tot2.
* \param tot3 : variable stockant le score de joueur actif pour la combianson : tot3.
* \param tot4 : variable stockant le score de joueur actif pour la combianson : tot4.
* \param tot5 : variable stockant le score de joueur actif pour la combianson : tot5.
* \param tot6 : variable stockant le score de joueur actif pour la combianson : tot6.
* \param brelan : variable stockant le score de joueur actif pour la combianson : brelan.
* \param carre : variable stockant le score de joueur actif pour la combianson : carre.
* \param full : variable stockant le score de joueur actif pour la combianson : full.
* \param petite : variable stockant le score de joueur actif pour la combianson : petite.
* \param grande : variable stockant le score de joueur actif pour la combianson : grande.
* \param yams : variable stockant le score de joueur actif pour la combianson : yams.
* \param chance : variable stockant le score de joueur actif pour la combianson : chance.
*/
void affecterDes(int nbDe1, int nbDe2, int nbDe3, int nbDe4, int nbDe5, int *tot1, int *tot2, int *tot3, int *tot4, int *tot5, int *tot6, int *brelan, int *carre, int *full, int *petite, int *grande, int *yams, int *chance){
    //initialisation des variables (carAbsorb sert juste à éviter que le scanf prenne le caractère de fin de chaîne et le mettent dans ligne)
    char ligne;
    char carAbsorb;
    bool affectation;
    affectation = false;
    //boucle permettant de mettre une valeur dans une ligne à condition qu'elle ne soit pas déjà remplie
    do{
        printf("Donnez le caractère (entre prenthèses) corspondant à la ligne à affecter avec la combinaison des dés :\n\n");
        printf("Total de 1   (1)\nTotal de 2   (2)\nTotal de 3   (3)\nTotal de 4   (4)\nTotal de 5   (5)\ntotal de 6   (6)\nBrelan       (b)\nCarré        (c)\nFull House   (f)\nPetite Suite (p)\nGrande Suite (g)\nYams         (y)\nChance       (C)\n");
        scanf("%c%c",&carAbsorb,&ligne);
        //chque ligne à affecter est gérée par ce switch
        switch (ligne)
        {
        case '1':
            //alternative qui regarde si la ligne est vide ou pleine et si elle est vide la variable de score est affecter avec l'appelle de la fonction corespondante
            if (*tot1 == INITVAR){
                *tot1 = f_tot1(nbDe1, nbDe2, nbDe3, nbDe4, nbDe5);
                affectation = true;
            } else {
                printf("Vous avez déjà affecté une valeur pour cette ligne !\n");
            }
            break;
        case '2':
            if (*tot2 == INITVAR){
                *tot2 = f_tot2(nbDe1, nbDe2, nbDe3, nbDe4, nbDe5);
                affectation = true;
            } else {
                printf("Vous avez déjà affecté une valeur pour cette ligne !\n");
            }
            break;
        case '3':
            if (*tot3 == INITVAR){
                *tot3 = f_tot3(nbDe1, nbDe2, nbDe3, nbDe4, nbDe5);
                affectation = true;
            } else {
                printf("Vous avez déjà affecté une valeur pour cette ligne !\n");
            }
            break;
        case '4':
            if (*tot4 == INITVAR){
                *tot4 = f_tot4(nbDe1, nbDe2, nbDe3, nbDe4, nbDe5);
                affectation = true;
            } else {
                printf("Vous avez déjà affecté une valeur pour cette ligne !\n");
            }
            break;
        case '5':
            if (*tot5 == INITVAR){
                *tot5 = f_tot5(nbDe1, nbDe2, nbDe3, nbDe4, nbDe5);
                affectation = true;
            } else {
                printf("Vous avez déjà affecté une valeur pour cette ligne !\n");
            }
            break;
        case '6':
            if (*tot6 == INITVAR){
                *tot6 = f_tot6(nbDe1, nbDe2, nbDe3, nbDe4, nbDe5);
                affectation = true;
            } else {
                printf("Vous avez déjà affecté une valeur pour cette ligne !\n");
            }
            break;
        case 'b':
            if (*brelan == INITVAR){
                *brelan = f_brelan(nbDe1, nbDe2, nbDe3, nbDe4, nbDe5);
                affectation = true;
            } else {
                printf("Vous avez déjà affecté une valeur pour cette ligne !\n");
            }
            break;
        case 'c':
            if (*carre == INITVAR){
                *carre = f_carre(nbDe1, nbDe2, nbDe3, nbDe4, nbDe5);
                affectation = true;
            } else {
                printf("Vous avez déjà affecté une valeur pour cette ligne !\n");
            }
            break;
        case 'f':
            if (*full == INITVAR){
                *full = f_full(nbDe1, nbDe2, nbDe3, nbDe4, nbDe5);
                affectation = true;
            } else {
                printf("Vous avez déjà affecté une valeur pour cette ligne !\n");
            }
            break;
        case 'p':
            if (*petite == INITVAR){
                *petite = f_petite(nbDe1, nbDe2, nbDe3, nbDe4, nbDe5);
                affectation = true;
            } else {
                printf("Vous avez déjà affecté une valeur pour cette ligne !\n");
            }
            break;
        case 'g':
            if (*grande == INITVAR){
                *grande = f_grande(nbDe1, nbDe2, nbDe3, nbDe4, nbDe5);
                affectation = true;
            } else {
                printf("Vous avez déjà affecté une valeur pour cette ligne !\n");
            }
            break;
        case 'y':
            if (*yams == INITVAR){
                *yams = f_yams(nbDe1, nbDe2, nbDe3, nbDe4, nbDe5);
                affectation = true;
            } else {
                printf("Vous avez déjà affecté une valeur pour cette ligne !\n");
            }
            break;
        case 'C':
            if (*chance == INITVAR){
                *chance = f_chance(nbDe1, nbDe2, nbDe3, nbDe4, nbDe5);
                affectation = true;
            } else {
                printf("Vous avez déjà affecté une valeur pour cette ligne !\n");
            }
            break;
        }
    } while (affectation == false);
}

/**
* \fn int f_tot1(int nbDe1, int nbDe2, int nbDe3, int nbDe4, int nbDe5)
* \brief Fonction qui demande calcul le total de dés sur 1 et retourne ce nombre.
* \param nbDe1 : paramètre qui indique à la procédure quel est la valeur du dé n°1.
* \param nbDe2 : paramètre qui indique à la procédure quel est la valeur du dé n°2.
* \param nbDe3 : paramètre qui indique à la procédure quel est la valeur du dé n°3.
* \param nbDe4 : paramètre qui indique à la procédure quel est la valeur du dé n°4.
* \param nbDe5 : paramètre qui indique à la procédure quel est la valeur du dé n°5.
* \return res : varible de retour qui contient la somme des dés sur 1.
*/
int f_tot1(int nbDe1, int nbDe2, int nbDe3, int nbDe4, int nbDe5){
    //regarde si chaque dé est positioné sur 1 et fait la somme de ces dés
    int res;
    res = 0;
    if (nbDe1 == 1){
        res = res + nbDe1;
    }
    if (nbDe2 == 1){
        res = res + nbDe2;
    }
    if (nbDe3 == 1){
        res = res + nbDe3;
    }
    if (nbDe4 == 1){
        res = res + nbDe4;
    }
    if (nbDe5 == 1){
        res = res + nbDe5;
    }
    return res;
}

/**
* \fn int f_tot2(int nbDe1, int nbDe2, int nbDe3, int nbDe4, int nbDe5)
* \brief Fonction qui demande calcul le total de dés sur 2 et retourne ce nombre.
* \param nbDe1 : paramètre qui indique à la procédure quel est la valeur du dé n°1.
* \param nbDe2 : paramètre qui indique à la procédure quel est la valeur du dé n°2.
* \param nbDe3 : paramètre qui indique à la procédure quel est la valeur du dé n°3.
* \param nbDe4 : paramètre qui indique à la procédure quel est la valeur du dé n°4.
* \param nbDe5 : paramètre qui indique à la procédure quel est la valeur du dé n°5.
* \return res : varible de retour qui contient la somme des dés sur 2.
*/
int f_tot2(int nbDe1, int nbDe2, int nbDe3, int nbDe4, int nbDe5){
    //regarde si chaque dé est positioné sur 2 et fait la somme de ces dés
    int res;
    res = 0;
    if (nbDe1 == 2){
        res = res + nbDe1;
    }
    if (nbDe2 == 2){
        res = res + nbDe2;
    }
    if (nbDe3 == 2){
        res = res + nbDe3;
    }
    if (nbDe4 == 2){
        res = res + nbDe4;
    }
    if (nbDe5 == 2){
        res = res + nbDe5;
    }
    return res;
}

/**
* \fn int f_tot3(int nbDe1, int nbDe2, int nbDe3, int nbDe4, int nbDe5)
* \brief Fonction qui demande calcul le total de dés sur 3 et retourne ce nombre.
* \param nbDe1 : paramètre qui indique à la procédure quel est la valeur du dé n°1.
* \param nbDe2 : paramètre qui indique à la procédure quel est la valeur du dé n°2.
* \param nbDe3 : paramètre qui indique à la procédure quel est la valeur du dé n°3.
* \param nbDe4 : paramètre qui indique à la procédure quel est la valeur du dé n°4.
* \param nbDe5 : paramètre qui indique à la procédure quel est la valeur du dé n°5.
* \return res : varible de retour qui contient la somme des dés sur 3.
*/
int f_tot3(int nbDe1, int nbDe2, int nbDe3, int nbDe4, int nbDe5){
    //regarde si chaque dé est positioné sur 3 et fait la somme de ces dés
    int res;
    res = 0;
    if (nbDe1 == 3){
        res = res + nbDe1;
    }
    if (nbDe2 == 3){
        res = res + nbDe2;
    }
    if (nbDe3 == 3){
        res = res + nbDe3;
    }
    if (nbDe4 == 3){
        res = res + nbDe4;
    }
    if (nbDe5 == 3){
        res = res + nbDe5;
    }
    return res;
}

/**
* \fn int f_tot4(int nbDe1, int nbDe2, int nbDe3, int nbDe4, int nbDe5)
* \brief Fonction qui demande calcul le total de dés sur 4 et retourne ce nombre.
* \param nbDe1 : paramètre qui indique à la procédure quel est la valeur du dé n°1.
* \param nbDe2 : paramètre qui indique à la procédure quel est la valeur du dé n°2.
* \param nbDe3 : paramètre qui indique à la procédure quel est la valeur du dé n°3.
* \param nbDe4 : paramètre qui indique à la procédure quel est la valeur du dé n°4.
* \param nbDe5 : paramètre qui indique à la procédure quel est la valeur du dé n°5.
* \return res : varible de retour qui contient la somme des dés sur 4.
*/
int f_tot4(int nbDe1, int nbDe2, int nbDe3, int nbDe4, int nbDe5){
    //regarde si chaque dé est positioné sur 4 et fait la somme de ces dés
    int res;
    res = 0;
    if (nbDe1 == 4){
        res = res + nbDe1;
    }
    if (nbDe2 == 4){
        res = res + nbDe2;
    }
    if (nbDe3 == 4){
        res = res + nbDe3;
    }
    if (nbDe4 == 4){
        res = res + nbDe4;
    }
    if (nbDe5 == 4){
        res = res + nbDe5;
    }
    return res;
}

/**
* \fn int f_tot5(int nbDe1, int nbDe2, int nbDe3, int nbDe4, int nbDe5)
* \brief Fonction qui demande calcul le total de dés sur 5 et retourne ce nombre.
* \param nbDe1 : paramètre qui indique à la procédure quel est la valeur du dé n°1.
* \param nbDe2 : paramètre qui indique à la procédure quel est la valeur du dé n°2.
* \param nbDe3 : paramètre qui indique à la procédure quel est la valeur du dé n°3.
* \param nbDe4 : paramètre qui indique à la procédure quel est la valeur du dé n°4.
* \param nbDe5 : paramètre qui indique à la procédure quel est la valeur du dé n°5.
* \return res : varible de retour qui contient la somme des dés sur 5.
*/
int f_tot5(int nbDe1, int nbDe2, int nbDe3, int nbDe4, int nbDe5){
    //regarde si chaque dé est positioné sur 5 et fait la somme de ces dés
    int res;
    res = 0;
    if (nbDe1 == 5){
        res = res + nbDe1;
    }
    if (nbDe2 == 5){
        res = res + nbDe2;
    }
    if (nbDe3 == 5){
        res = res + nbDe3;
    }
    if (nbDe4 == 5){
        res = res + nbDe4;
    }
    if (nbDe5 == 5){
        res = res + nbDe5;
    }
    return res;
}

/**
* \fn int f_tot6(int nbDe1, int nbDe2, int nbDe3, int nbDe4, int nbDe5)
* \brief Fonction qui demande calcul le total de dés sur 6 et retourne ce nombre.
* \param nbDe1 : paramètre qui indique à la procédure quel est la valeur du dé n°1.
* \param nbDe2 : paramètre qui indique à la procédure quel est la valeur du dé n°2.
* \param nbDe3 : paramètre qui indique à la procédure quel est la valeur du dé n°3.
* \param nbDe4 : paramètre qui indique à la procédure quel est la valeur du dé n°4.
* \param nbDe5 : paramètre qui indique à la procédure quel est la valeur du dé n°5.
* \return res : varible de retour qui contient la somme des dés sur 6.
*/
int f_tot6(int nbDe1, int nbDe2, int nbDe3, int nbDe4, int nbDe5){
    //regarde si chaque dé est positioné sur 6 et fait la somme de ces dés
    int res;
    res = 0;
    if (nbDe1 == 6){
        res = res + nbDe1;
    }
    if (nbDe2 == 6){
        res = res + nbDe2;
    }
    if (nbDe3 == 6){
        res = res + nbDe3;
    }
    if (nbDe4 == 6){
        res = res + nbDe4;
    }
    if (nbDe5 == 6){
        res = res + nbDe5;
    }
    return res;
}

/**
* \fn bool f_bonus(int tot1, int tot2, int tot3, int tot4, int tot5, int tot6)
* \brief Fonction qui additionne tous les paramètres d'entrée et determine l'accès au bonus.
* \param nbDe1 : paramètre qui indique à la procédure quel est la valeur du dé n°1.
* \param nbDe2 : paramètre qui indique à la procédure quel est la valeur du dé n°2.
* \param nbDe3 : paramètre qui indique à la procédure quel est la valeur du dé n°3.
* \param nbDe4 : paramètre qui indique à la procédure quel est la valeur du dé n°4.
* \param nbDe5 : paramètre qui indique à la procédure quel est la valeur du dé n°5.
* \return res : varible de retour qui contient true si le bonus est accessible et false sinon.
*/
bool f_bonus(int tot1, int tot2, int tot3, int tot4, int tot5, int tot6){
    //initialise la variable de retour à faux car on part du principe qu'il n'y a pas de bonus
    bool bon;
    bon = false;
    //alternative qui somme toutes les variables de score de la partie inférieur et détermine l'accéès au bonus
    if (tot1 + tot2 + tot3 + tot4 + tot5 + tot6 > ACCBONUS){
        bon = true;
    }
    return bon;
}

/**
* \fn int f_brelan(int nbDe1, int nbDe2, int nbDe3, int nbDe4, int nbDe5)
* \brief Fonction qui fait la somme de 3 dés sur le même nombre et la retourne si il n'y en a pas elle fait la somme avec 0 dés donc retourne 0.
* \param nbDe1 : paramètre qui indique à la procédure quel est la valeur du dé n°1.
* \param nbDe2 : paramètre qui indique à la procédure quel est la valeur du dé n°2.
* \param nbDe3 : paramètre qui indique à la procédure quel est la valeur du dé n°3.
* \param nbDe4 : paramètre qui indique à la procédure quel est la valeur du dé n°4.
* \param nbDe5 : paramètre qui indique à la procédure quel est la valeur du dé n°5.
* \return res : varible de retour qui contient la somme total des dés si il y a un brelan et 0 sinon.
*/
int f_brelan(int nbDe1, int nbDe2, int nbDe3, int nbDe4, int nbDe5){
    int res;
    //les variables des dés sont misent dans un tableau
    int tableau[5] = {nbDe1, nbDe2, nbDe3, nbDe4, nbDe5};
    int j, i;
    i = 0;
    //ce tableau est trié pour facilité les recherches de combinaison
    trisDes(tableau);
    //la boucle parcours le tableau à la recherche de 2 nombre identique et si tel est le cas alors une varible de compatege i est incrémentée de 1
    for (j = 0; j < 4; ++j) {
        if (tableau[j] == tableau[j + 1]){
            i++;
        }
    }
    //si i est supérieur à 2 alors ça veut dire que plus de deux dés sont identiques et si tel est le cas alors il ya un brelan
    if (i >= 2){
        //le brelan corespond à la somme de tout les dés et c'est exactment ce que fait la fonction chance donc elle est appelée et son retour est affecté au retour de cette fonction
        res = f_chance(nbDe1, nbDe2, nbDe3, nbDe4, nbDe5);
    } else {
        res = 0;
    }
    return res;
}

/**
* \fn int f_carre(int nbDe1, int nbDe2, int nbDe3, int nbDe4, int nbDe5)
* \brief Fonction qui fait la somme de 4 dés sur le même nombre et la retourne si il n y en pas fait la somme avec 0 dés donc retourne 0.
* \param nbDe1 : paramètre qui indique à la procédure quel est la valeur du dé n°1.
* \param nbDe2 : paramètre qui indique à la procédure quel est la valeur du dé n°2.
* \param nbDe3 : paramètre qui indique à la procédure quel est la valeur du dé n°3.
* \param nbDe4 : paramètre qui indique à la procédure quel est la valeur du dé n°4.
* \param nbDe5 : paramètre qui indique à la procédure quel est la valeur du dé n°5.
* \return res : varible de retour qui contient la somme total des dés si il y a un carré et 0 sinon.
*/
int f_carre(int nbDe1, int nbDe2, int nbDe3, int nbDe4, int nbDe5){
    int res;
    //les variables des dés sont misent dans un tableau
    int tableau[5] = {nbDe1, nbDe2, nbDe3, nbDe4, nbDe5};
    int j, i;
    i = 0;
    //ce tableau est trié pour facilité les recherches de combinaison
    trisDes(tableau);
    //la boucle parcours le tableau à la recherche de 2 nombre identique et si tel est le cas alors une varible de compatege i est incrémentée de 1
    for (j = 0; j < 4; ++j) {
        if (tableau[j] == tableau[j + 1]){
            i++;
        }
    }
    //si i est supérieur à 3 alors ça veut dire que plus de trois dés sont identiques et si tel est le cas alors il ya un carré
    if (i >= 3){
        //le carré corespond à la somme de tout les dés et c'est exactment ce que fait la fonction chance donc elle est appelée et son retour est affecté au retour de cette fonction
        res = f_chance(nbDe1, nbDe2, nbDe3, nbDe4, nbDe5);
    } else {
        res = 0;
    }
    return res;
}

/**
* \fn int f_full(int nbDe1, int nbDe2, int nbDe3, int nbDe4, int nbDe5)
* \brief Fonction qui regarde la présence d'un brelan et d'une paire et si oui retourne 25 sinon retourne 0.
* \param nbDe1 : paramètre qui indique à la procédure quel est la valeur du dé n°1.
* \param nbDe2 : paramètre qui indique à la procédure quel est la valeur du dé n°2.
* \param nbDe3 : paramètre qui indique à la procédure quel est la valeur du dé n°3.
* \param nbDe4 : paramètre qui indique à la procédure quel est la valeur du dé n°4.
* \param nbDe5 : paramètre qui indique à la procédure quel est la valeur du dé n°5.
* \return res : varible de retour qui contient 25 si il y a un full house et 0 sinon.
*/
int f_full(int nbDe1, int nbDe2, int nbDe3, int nbDe4, int nbDe5){
    int res;
    //stockage des variables dans un tableau pour simplifier les détection de combinaisons
    int tableau[5] = {nbDe1, nbDe2, nbDe3, nbDe4, nbDe5};
    //tableau qui stocke les différente occurence de chaque nombre
    int tableauComptage[6] = {0,0,0,0,0,0};   
    //variables de boucles
    int j, i;
    //variables de detection de brelan et de pair
    int nbPourBrelan;
    int nbPourPair;
    nbPourBrelan = 0;
    nbPourPair = 0;
    //variable de detection de yams
    bool yams;
    yams = (f_yams(nbDe1, nbDe2, nbDe3, nbDe4, nbDe5) == YAMS);
    i = 0;
    res = 0;
    //appel de la fonction pour trier le tableau
    trisDes(tableau);
    //boucle qui comptent les occurences de chaque nombre et les places dans le tableau tableauComptage
    for (j = 0; j < NBDES; ++j) {
        tableauComptage[tableau[j]-1] = tableauComptage[tableau[j]-1] + 1;
    }
    //boucle qui cherche dans le tableau de comptage si il ya 3 fois un nombre et si il y en a un 2 fois
    while ((nbPourPair == 0 || nbPourBrelan == 0) && i < NUMDES){
        if (tableauComptage[i] == 3){
            nbPourBrelan = 1;
        } else if (tableauComptage[i] == 2){
            nbPourPair = 1;
        }
        i = i + 1;
    }
    //alternative qui attribue 25 à res si il ya un full house
    if (((nbPourBrelan == 1) && (nbPourPair == 1)) || yams == true){
        res = FULL;
    }
    return res;
}

/**
* \fn int f_petite(int nbDe1, int nbDe2, int nbDe3, int nbDe4, int nbDe5)
* \brief Fonction qui regarde la présence de 4 dés qui se suivent si oui retourne 30 sinon retourne 0.
* \param nbDe1 : paramètre qui indique à la procédure quel est la valeur du dé n°1.
* \param nbDe2 : paramètre qui indique à la procédure quel est la valeur du dé n°2.
* \param nbDe3 : paramètre qui indique à la procédure quel est la valeur du dé n°3.
* \param nbDe4 : paramètre qui indique à la procédure quel est la valeur du dé n°4.
* \param nbDe5 : paramètre qui indique à la procédure quel est la valeur du dé n°5.
* \return res : varible de retour qui contient 30 si il y a une petite suite et 0 sinon.
*/
int f_petite(int nbDe1, int nbDe2, int nbDe3, int nbDe4, int nbDe5){
    int res;
    res = 0;
    //stockage des variables dans un tableau pour simplifier les détection de combinaisons
    int tableau[5] = {nbDe1, nbDe2, nbDe3, nbDe4, nbDe5};
    //variable qui stocke le nombre de fois que des chiffres se suivent
    int i, nbQuiSeSuivent;
    i = 0;
    nbQuiSeSuivent = 0;
    //appel de la fonction pour trier le tableau
    trisDes(tableau);
    //boucle qui parcours le tableau à la recherche de nombre qui se suivent
    do {
        if (tableau[i] == tableau[i + 1]-1){
            nbQuiSeSuivent = nbQuiSeSuivent + 1;
        }
        i = i + 1;
    } while ((nbQuiSeSuivent < 3) && (i < 5) && ((tableau[i] == tableau[i + 1]-1) || (tableau[i] == tableau[i + 1])));
    //si le nombre de chiffres qui se suivent est supérieur ou égal à 3 alors il y a une petite suite
    if (nbQuiSeSuivent >= 3){
        res = 30;
    }
    return res;
}

/**
* \fn int f_grande(int nbDe1, int nbDe2, int nbDe3, int nbDe4, int nbDe5)
* \brief Fonction qui regarde la présence de 5 dés qui se suivent si oui retourne 40 sinon retourne 0.
* \param nbDe1 : paramètre qui indique à la procédure quel est la valeur du dé n°1.
* \param nbDe2 : paramètre qui indique à la procédure quel est la valeur du dé n°2.
* \param nbDe3 : paramètre qui indique à la procédure quel est la valeur du dé n°3.
* \param nbDe4 : paramètre qui indique à la procédure quel est la valeur du dé n°4.
* \param nbDe5 : paramètre qui indique à la procédure quel est la valeur du dé n°5.
* \return res : varible de retour qui contient 40 si il y a une grande suite et 0 sinon.
*/
int f_grande(int nbDe1, int nbDe2, int nbDe3, int nbDe4, int nbDe5){
    int res;
    res = 0;
    //stockage des variables dans un tableau pour simplifier les détection de combinaisons
    int tableau[5] = {nbDe1, nbDe2, nbDe3, nbDe4, nbDe5};
    //variable qui stocke le nombre de fois que des chiffres se suivent
    int i, nbQuiSeSuivent;
    i = 0;
    nbQuiSeSuivent = 0;
    //appel de la fonction pour trier le tableau
    trisDes(tableau);
    //boucle qui parcours le tableau à la recherche de nombre qui se suivent
    do {
        if (tableau[i] == tableau[i + 1]-1){
            nbQuiSeSuivent = nbQuiSeSuivent + 1;
        }
        i = i + 1;
    } while ((nbQuiSeSuivent < 4) && (i < NBDES));
    //si le nombre de chiffres qui se suivent est supérieur ou égal à 4 alors il y a une grande suite
    if (nbQuiSeSuivent >= 4){
        res = GRANDE;
    }
    return res;
}

/**
* \fn int f_yams(int nbDe1, int nbDe2, int nbDe3, int nbDe4, int nbDe5)
* \brief Fonction qui regarde la présence de 5 dés qui ont la même valeur si oui retourne 50 sinon retourne 0.
* \param nbDe1 : paramètre qui indique à la procédure quel est la valeur du dé n°1.
* \param nbDe2 : paramètre qui indique à la procédure quel est la valeur du dé n°2.
* \param nbDe3 : paramètre qui indique à la procédure quel est la valeur du dé n°3.
* \param nbDe4 : paramètre qui indique à la procédure quel est la valeur du dé n°4.
* \param nbDe5 : paramètre qui indique à la procédure quel est la valeur du dé n°5.
* \return res : varible de retour qui contient 50 si il y a un yams et 0 sinon.
*/
int f_yams(int nbDe1, int nbDe2, int nbDe3, int nbDe4, int nbDe5){
    int res;
    res = 0;
    if ( nbDe1 == nbDe2 && nbDe1 == nbDe3 && nbDe1 == nbDe4 && nbDe1 == nbDe5){
        res = YAMS;
    }
    return res;
}

/**
* \fn int f_chance(int nbDe1, int nbDe2, int nbDe3, int nbDe4, int nbDe5)
* \brief Fonction qui fait la somme de tous les dés et retourne cette somme (elle est aussi appelé par d'autre fonction qui ont besoins d'avoir la somme des dés).
* \param nbDe1 : paramètre qui indique à la procédure quel est la valeur du dé n°1.
* \param nbDe2 : paramètre qui indique à la procédure quel est la valeur du dé n°2.
* \param nbDe3 : paramètre qui indique à la procédure quel est la valeur du dé n°3.
* \param nbDe4 : paramètre qui indique à la procédure quel est la valeur du dé n°4.
* \param nbDe5 : paramètre qui indique à la procédure quel est la valeur du dé n°5.
* \return res : varible de retour qui contient la somme des dés.
*/
int f_chance(int nbDe1, int nbDe2, int nbDe3, int nbDe4, int nbDe5){
    int res;
    res = nbDe1 + nbDe2 + nbDe3 + nbDe4 + nbDe5;
    return res;
}

/**
* \fn void trisDes(int tableau[5])
* \brief Procédure qui trie les dés dans l'ordre croissant.
* \param tableau[5] : paramètre qui transmet à la procédure le tableau des dés non-trié et qui retourne ce tableau trié.
*/
void trisDes(int tab[5]){
    //constante déffinissant la taille du tableau
    int i, j, tmp;
    int posMin;
    //boucle parcourant le tableau
    for (i = 0; i < NBDES-1; i++){
        posMin = i;
        //boucle parcourant le tableau avec à chaque fois 1 élément de moins
        for (j = i+1; j < NBDES; j++){
            if (tab[j] < tab[posMin]) {
                posMin = j;
            }
        }
        //instructions échangeant la postion des deux éléments du tableau
        tmp = tab[i];
        tab[i] = tab[posMin];
        tab[posMin] = tmp;
    }
}