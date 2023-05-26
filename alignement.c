
#include "alignement.h"
#include "grille.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

void horizontale(char **grille, int M, int N) {

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
void verticale(char **grille, int M, int N) {

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
void diagonale1(char **grille, int M, int N) {

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
void diagonale2(char **grille, int M, int N) {

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
