#include "grille.h"
#include "alignement.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#define couleur(param) printf("\033[%sm", param)

char **cree_grille(int M, int N, int num_symboles) {
  char **grille = malloc(M * sizeof(char *));
  char symboles[num_symboles];
  int i, j, k;
  for (i = 0; i < num_symboles; i++) {
    symboles[i] = 'A' + i;
  }
  for (i = 0; i < M; i++) {
    grille[i] = malloc(N * sizeof(char));
  }
  srand(time(NULL));
  for (i = 0; i < M; i++) {
    for (j = 0; j < N; j++) {
      grille[i][j] = symboles[rand() % num_symboles];
    }
  }

  return grille;
}

char **swap_symboles(char **grille, int x1, int y1, int x2, int y2) {

  char temp = grille[y1][x1];
  grille[y1][x1] = grille[y2][x2];
  grille[y2][x2] = temp;
  return grille;
}

void remplis(char **grille, int M, int N, int num_symboles) {
  char symboles[num_symboles];
  int i, j, k;
  for (i = 0; i < num_symboles; i++) {
    symboles[i] = 'A' + i;
  }
  srand(time(NULL));
  for (i = 0; i < M; i++) {
    for (j = 0; j < N; j++) {
      if (grille[i][j] == ' ') {
        grille[i][j] = symboles[rand() % num_symboles];
      }
    }
  }
}

void affiche_grille(char **grille, int M, int N, int score, int num_symbole) {
  printf("Grille : \n");
  printf("  ");
  for (int x = 0; x < N; x++) {
    printf(" %d", x);
  }
  printf("\n");

  printf("   ");
  for (int z = 0; z < N; z++) {

    printf("_ ");
  }
  printf("\n");
  for (int i = 0; i < M; i++) {
    printf("%d |", i);

    for (int j = 0; j < N; j++) {
      if (num_symbole == 4) {
        if (grille[i][j] == 'A') {
          couleur("34");
        }
        if (grille[i][j] == 'B') {
          couleur("31");
        }
        if (grille[i][j] == 'C') {
          couleur("35");
        }
        if (grille[i][j] == 'D') {
          couleur("33");
        }
      }

      if (num_symbole == 5) {
        if (grille[i][j] == 'A') {
          couleur("34");
        }
        if (grille[i][j] == 'B') {
          couleur("31");
        }
        if (grille[i][j] == 'C') {
          couleur("35");
        }
        if (grille[i][j] == 'D') {
          couleur("33");
        }
        if (grille[i][j] == 'E') {
          couleur("32");
        }
      }
      if (num_symbole == 6) {
        if (grille[i][j] == 'A') {
          couleur("34");
        }
        if (grille[i][j] == 'B') {
          couleur("31");
        }
        if (grille[i][j] == 'C') {
          couleur("35");
        }
        if (grille[i][j] == 'D') {
          couleur("33");
        }
        if (grille[i][j] == 'E') {
          couleur("32");
        }
        if (grille[i][j] == 'F') {
          couleur("37");
        }
      }

      printf("%c ", grille[i][j]);
      couleur("0");
    }
    printf("\n");
  }

  printf("Nombre de coup : %d \n", score);
}
void gravite(char **grille, int M, int N) {
  char temp;
  int compteur = 0;
  for (int i = 0; i < M; i++) {
    for (int j = N - 1; j > 0; j--) {
      if (grille[i][j] == ' ') {
        for (int x = j - 1; x >= 0; x--) {
          if (grille[i][x] != ' ') {
            temp = grille[i][x];
            grille[i][x] = ' ';
            grille[i][j] = temp;
            break;
          }
        }
      }
    }
  }
}