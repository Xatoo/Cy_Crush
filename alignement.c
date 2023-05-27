#include "alignement.h"
#include "grille.h"
#include "sauvegarde.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
int alignment(char **grid, int M, int N) {
  // La fonction permet de savoir si il y a un alignement de minimum 3 mêmes
  // symboles dans la grille passer en paramètre

  int i, j;
  char symbole;

  // horizontal
  for (i = 0; i < M; i++) {
    for (j = 0; j < N - 2; j++) {
      if (grid[i][j] != ' ') {
        symbole = grid[i][j];
        if (grid[i][j + 1] == symbole && grid[i][j + 2] == symbole) {
          return 1;
        }
      }
    }
  }

  // vertical
  for (j = 0; j < N; j++) {
    for (i = 0; i < M - 2; i++) {
      if (grid[i][j] != ' ') {
        symbole =grid[i][j];
        if (grid[i + 1][j] == symbole && grid[i + 2][j] == symbole) {
          return 1;
        }
      }
    }
  }

  // diagonale 1 (de haut a gauche jusqu'en bas à droit)
  for (i = 0; i < M - 2; i++) {
    for (j = 0; j < N - 2; j++) {
      if (grid[i][j] != ' ') {
        symbole = grid[i][j];
        if (grid[i + 1][j + 1] == symbole &&
            grid[i + 2][j + 2] == symbole) {
          return 1;
        }
      }
    }
  }
  // diagonale 2 (de bas a gauche jusqu'en haut à droit) 
  for (i = 0; i < M - 2; i++) {
    for (j = 2; j < N; j++) {
      if (grid[i][j] != ' ') {
        symbole = grid[i][j];
        if (grid[i + 1][j - 1] == symbole &&
            grid[i + 2][j - 2] == symbole) {
          return 1;
        }
      }
    }
  }

  return 0;
}

void horizontal(char **grille, int M, int N) {
  // La fonction remplace tout les alignements horizontaux par des cases vides

  for (int i = 0; i < M; i++) {
    for (int j = 0; j < N; j++) {
      char symbole = grille[i][j];
      int compteur = 1;

      for (int k = j + 1; k < N; k++) {
        if (grille[i][k] == symbole) {
          compteur++;
        } else {
          break;
        }
      }
      if (compteur >= 3) {
        for (int k = 0; k < compteur; k++) {
          grille[i][j + k] = ' ';
        }
      }
    }
  }
}

void vertical(char **grille, int M, int N) {
  // La fonction remplace tout les alignements verticaux par des cases vides
  for (int i = 0; i < M; i++) {
    for (int j = 0; j < N; j++) {
      char symbole = grille[i][j];
      int compteur = 1;

      for (int k = i + 1; k < M; k++) {
        if (grille[k][j] == symbole) {
          compteur++;

        } else {
          break;
        }
      }

      if (compteur >= 3) {
        for (int k = 0; k < compteur; k++) {
          grille[i + k][j] = ' ';
        }
      }
    }
  }
}

void diagonal1(char **grille, int M, int N) {
  // La fonction remplace tout les alignements diagonaux (de haut a gauche
  // jusqu'en bas à droit) par des cases vides
  for (int i = 0; i < M - 2; i++) {
    for (int j = 0; j < N - 2; j++) {
      char symbole = grille[i][j];
      int compteur = 1;

      for (int k = i + 1, l = j + 1; k < M && l < N; k++, l++) {
        if (grille[k][l] == symbole) {
          compteur++;
        } else {
          break;
        }
      }

      if (compteur >= 3) {
        for (int k = 0; k < compteur; k++) {
          grille[i + k][j + k] = ' ';
        }
      }
    }
  }
}

void diagonal2(char **grille, int M, int N) {
  // La fonction remplace tout les alignements diagonaux (de bas a gauche
  // jusqu'en haut à droit) par des cases vides
  for (int i = 2; i < M; i++) {
    for (int j = 0; j < N - 2; j++) {
      char symbole = grille[i][j];
      int compteur = 1;

      for (int k = i - 1, l = j + 1; k >= 0 && l < N; k--, l++) {
        if (grille[k][l] == symbole) {
          compteur++;

        } else {
          break;
        }
      }

      if (compteur >= 3) {
        for (int k = 0; k < compteur; k++) {
          grille[i - k][j + k] = ' ';
        }
      }
    }
  }
}

int alignment_possible(char **grille, int M, int N) {
  // fonction qui cherche à savoir si il est possible de faire un alignement de
  // 3 symboles ou plus en testant tout les mouvement possible
  char **grille_test;
  for (int i = 0; i < M; i++) {
    for (int j = 0; j < N; j++) {
      // grille[i][j] est la case source
      for (int u = 0; u < M; u++) {
        for (int v = 0; v < N; v++) {
          // grille[u][v] est la case déstination
          
          grille_test = swap_symbols(grille, j, i, v, u);
         
          if (alignment(grille_test, M, N) == 1) {
           
            grille_test = swap_symbols(grille, j, i, v, u);
            
            return 1;
          }
          //reswap pour continuer les tests en revenant a la grille i
          grille_test = swap_symbols(grille, j, i, v, u);
        }
      }
    }
  }
  printf("Fin de partie \n");
  fflush(stdout);
  return 0;
}

void del_alignment(char **grille, int M, int N) {
  horizontal(grille, M, N);
  vertical(grille, M, N);
  diagonal1(grille, M, N);
  diagonal2(grille, M, N);
}
