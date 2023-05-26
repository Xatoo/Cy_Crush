#include "alignement.h"
#include "grille.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#define couleur(param) printf("\033[%sm", param)

void enregistrerGrille(char **grille, int M, int N, int tps,
                       const char *nomFichier) {
  FILE *fichier = fopen(nomFichier, "w");

  fprintf(fichier, "%d %d\n", M, N);
  fprintf(fichier, "%d\n", tps);
  for (int i = 0; i < M; i++) {
    for (int j = 0; j < N; j++) {
      fprintf(fichier, "%c ", grille[i][j]);
    }
    fprintf(fichier, "\n");
  }

  fclose(fichier);
}

void saveScore(int tps, const char *nomFichier, int score, char *name) {
  FILE *fichier = fopen(nomFichier, "w");

  fprintf(fichier, "%s\n", name);
  fprintf(fichier, "%d\n", score);
  fprintf(fichier, "%d\n", tps);

  fclose(fichier);
}

void printHighScore(int tps, const char *nomFichier, int score, char *name) {
  FILE *fichier = fopen(nomFichier, "r");

  // faire une boucle aller jusqu'au dernier highscore

  fscanf(fichier, "%c", name);
  fscanf(fichier, "%d", &score);
  fscanf(fichier, "%d", &tps);
}

int checkwin(char **grille, int M, int N) {
  int symbol_count = 0;
  for (int i = 0; i < M; i++) {
    for (int j = 0; j < N; j++) {
      if (grille[i][j] != ' ') {
        symbol_count++;
      }
    }
  }
  return symbol_count;
}
bool alignements(char **grille, int M, int N) {
  int i, j, k;
  char symbole;

  // horizontal
  for (i = 0; i < M; i++) {
    for (j = 0; j < N - 2; j++) {
      symbole = grille[i][j];
      if (grille[i][j + 1] == symbole && grille[i][j + 2] == symbole) {
        return true;
      }
    }
  }

  // vertical
  for (j = 0; j < N; j++) {
    for (i = 0; i < M - 2; i++) {
      symbole = grille[i][j];
      if (grille[i + 1][j] == symbole && grille[i + 2][j] == symbole) {
        return true;
      }
    }
  }

  // diagonale 1
  for (i = 0; i < M - 2; i++) {
    for (j = 0; j < N - 2; j++) {
      symbole = grille[i][j];
      if (grille[i + 1][j + 1] == symbole && grille[i + 2][j + 2] == symbole) {
        return true;
      }
    }
  }
  // diagonale 2
  for (i = 0; i < M - 2; i++) {
    for (j = 2; j < N; j++) {
      symbole = grille[i][j];
      if (grille[i + 1][j - 1] == symbole && grille[i + 2][j - 2] == symbole) {
        return true;
      }
    }
  }

  return false;
}
bool alignement_possible(char **grille, int M, int N) {
  char **grille_test;
  for (int i = 0; i < M; i++) {
    for (int j = 0; j < N; j++) {
      // grille[i][j] est la case source
      for (int u = 0; u < M; u++) {
        for (int v = 0; v < N; v++) {
          // grille[u][v] est la case déstination
          // printf("Swap before test...i=%d j=%d u=%d v=%d M=%d
          // N=%d\n",i,j,u,v, M,N); fflush(stdout);
          grille_test = swap_symboles(grille, j, i, v, u);
          // printf("    done...\n");
          // fflush(stdout);
          if (alignements(grille_test, M, N) == true) {
            // printf("Swap after test OK...\n");
            // fflush(stdout);
            grille_test = swap_symboles(grille, j, i, v, u);
            // printf("    done...\n");
            // fflush(stdout);
            return true;
          }
          // printf("Swap after test NOK...\n");
          // fflush(stdout);
          grille_test = swap_symboles(grille, j, i, v, u);
          // printf("    done...\n");
          // fflush(stdout);
        }
      }
    }
  }
  printf("Fin de partie \n");
  fflush(stdout);
  return false;
}

void sup_alignements(char **grille, int M, int N) {
  horizontale(grille, M, N);
  verticale(grille, M, N);
  diagonale1(grille, M, N);
  diagonale2(grille, M, N);
}

int main() {
  int tps = 0;
  int score = 0;
  int M, N, num_symboles;
  char **grille;
  char name[100];
  bool align;
  int ans;
  num_symboles = 0;
  printf("Entrez votre pseudo pour commencer à jouer :");
  scanf("%s", name);
  printf("Bonjour %s, si vous voulez charger la dernière partie enregistrée "
         "tapé 0, si vous voulez en commencer une autre tapé 1 ",
         name);
  scanf("%d", &ans);
  if (ans == 0) {
    // recupererGrille(grille, M, N, tps, "sauvegarde.txt");

  } else {

    printf("Entrez les dimensions de la grille (M x N) : ");
    scanf("%d %d", &M, &N);
    do {
      printf("Entrez le nombre de symboles différents (entre 4 et 6 ) : ");
      scanf("%d", &num_symboles);
    } while (num_symboles < 4 || num_symboles > 6 || sizeof(num_symboles) == 1);

    grille = cree_grille(M, N, num_symboles);

    do {
      sup_alignements(grille, M, N);
      remplis(grille, M, N, num_symboles);

    } while (alignements(grille, M, N) == true);
  }
  affiche_grille(grille, M, N, score, num_symboles);
  int x1 = 0, y1 = 0, x2 = 0, y2 = 0;

  do {
    printf(
        "Voulez-vous enregistrer votre partie ?(taper 1 si oui,sinon taper 0)");
    scanf("%d", &ans);
    if (ans == 1) {
      enregistrerGrille(grille, M, N, tps, "sauvegarde.txt");
      exit(1);
    }

    do {
      printf("Choisir les coordonnées du points a changer x:");
      scanf("%d", &x1);
    } while (x1 < 0 || x1 > N - 1 || x1 == ' ');
    do {
      printf("Choisir les coordonnées du points a changer y:");
      scanf("%d", &y1);
    } while (y1 < 0 || y1 > M - 1 || y1 == ' ');
    do {
      printf("Choisir les coordonnées du points échanger x:");
      scanf("%d", &x2);
    } while (x2 < 0 || x2 > N - 1 || x2 == ' ');
    do {
      printf("Choisir les coordonnées du points échanger y:");
      scanf("%d", &y2);
    } while (y2 < 0 || y2 > M - 1 || y2 == ' ');

    grille = swap_symboles(grille, x1, y1, x2, y2);

    if (alignements(grille, M, N) == false) {
      while (alignements(grille, M, N) == false) {

        grille = swap_symboles(grille, x1, y1, x2, y2);
        printf("Le déplacement n'est pas possible !\n");
        do {
          printf("Choisir les nouvelles coordonnées du points a changer x:");
          scanf("%d", &x1);
        } while (x1 < 0 || x1 > N - 1 || x1 == ' ');
        do {
          printf("Choisir les nouvelles coordonnées du points a changer y:");
          scanf("%d", &y1);
        } while (y1 < 0 || y1 > M - 1 || y1 == ' ');
        do {
          printf("Choisir les nouvelles coordonnées du points échanger x:");
          scanf("%d", &x2);
        } while (x2 < 0 || x2 > N - 1 || x2 == ' ');
        do {
          printf("Choisir les nouvelles coordonnées du points échanger y:");
          scanf("%d", &y2);
        } while (y2 < 0 || y2 > M - 1 || y2 == ' ');

        grille = swap_symboles(grille, x1, y1, x2, y2);
      }
    }

    do {
      sup_alignements(grille, M, N);
      gravite(grille, M, N);
    } while (alignements(grille, M, N) == true);
    score += 1;
    affiche_grille(grille, M, N, score, num_symboles);

  } while (alignement_possible(grille, M, N) == true);

  if (checkwin(grille, M, N) <= 2) {
    printf(" Félicitations ! Vous avez gagné ! \n");
    saveScore(tps, "sauvegarde.txt", score, name);
    // fonction qui affiche tout les meilleurs score
  } else {
    printf(" Dommage... vous avez perdu.\n");
    // fonction qui affiche tout les meilleurs score
  }
  for (int i = 0; i < M; i++) {
    free(grille[i]);
  }
  free(grille);

  return 0;
}