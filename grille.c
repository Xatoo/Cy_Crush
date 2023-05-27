#include "grille.h"
#include "alignement.h"
#include "sauvegarde.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#define color(param) printf("\033[%sm", param)
void printgrid(char **grid, int M, int N, int score, int num_symbol){
  //affiche la grille en couleurs pour mieux distingué les différents symboles
  //l'affichage est fait avec des chiffres pour rappeler un plan avec des       //coordonnées x et y
  
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
      if (num_symbol == 4) {
        if (grid[i][j] == 'A') {
          color("34");
        }
        if (grid[i][j] == 'B') {
          color("31");
        }
        if (grid[i][j] == 'C') {
          color("35");
        }
        if (grid[i][j] == 'D') {
          color("33");
        }
      }

      if (num_symbol == 5) {
        if (grid[i][j] == 'A') {
          color("34");
        }
        if (grid[i][j] == 'B') {
          color("31");
        }
        if (grid[i][j] == 'C') {
          color("35");
        }
        if (grid[i][j] == 'D') {
          color("33");
        }
        if (grid[i][j] == 'E') {
          color("32");
        }
      }
      if (num_symbol == 6) {
        if (grid[i][j] == 'A') {
          color("34");
        }
        if (grid[i][j] == 'B') {
          color("31");
        }
        if (grid[i][j] == 'C') {
          color("35");
        }
        if (grid[i][j] == 'D') {
          color("33");
        }
        if (grid[i][j] == 'E') {
          color("32");
        }
        if (grid[i][j] == 'F') {
          color("37");
        }
      }

      printf("%c ", grid[i][j]);
      color("0");
    }
    printf("\n");
  }

  printf("Nombre de coup : %d \n", score);
}

void remplis(char **grid, int M, int N, int num_symbols) {
  //remplis la grille avant le debut de partie pour qu'il n'y est aucun alignement de 3 même symboles ou plus
  
  char symbols[num_symbols];
  int i, j;
  for (i = 0; i < num_symbols; i++) {
    symbols[i] = 'A' + i;
  }
  srand(time(NULL));
  for (i = 0; i < M; i++) {
    for (j = 0; j < N; j++) {
      if (grid[i][j] == ' ') {
        grid[i][j] = symbols[rand() % num_symbols];
      }
    }
  }
}
char **create_grid(int M, int N, int num_symbols) {
  //crée un tableau 2D de type char et place des lettres servant de symboles 
  //en fonction du nombre de 
  
  
  char **grid = malloc(M * sizeof(char *));
  char symbols[num_symbols];
  int i, j, k;
  for (i = 0; i < num_symbols; i++) {
    symbols[i] = 'A' + i;
  }
  for (i = 0; i < M; i++) {
    grid[i] = malloc(N * sizeof(char));
  }
  srand(time(NULL));
  for (i = 0; i < M; i++) {
    for (j = 0; j < N; j++) {
      grid[i][j] = symbols[rand() % num_symbols];
    }
  }

  return grid;
}
char **swap_symbols(char **grid, int x1, int y1, int x2, int y2) {
  //echange deux cases de la grille en fonction de leurs coordonnées (x;y) 

  
  char temp = grid[y1][x1];
  grid[y1][x1] = grid[y2][x2];
  grid[y2][x2] = temp;
  return grid;
}

void gravity(char **grid, int M, int N) {
  //applique un mouvement des symboles vers la droite si la cases à leurs       //droite est un espace vide (permet la gravite vers la droie)
  
  char temp;
  for (int i = 0; i < M; i++) {
    for (int j = N - 1; j > 0; j--) {
      if (grid[i][j] == ' ') {
        for (int x = j - 1; x >= 0; x--)
          if (grid[i][x] != ' ') {
            temp = grid[i][x];
            grid[i][x] = ' ';
            grid[i][j] = temp;
            break;
          }
      }
    }
  }
}

int checkwin(char **grid, int M, int N) {
  //retourne le nombre de symbole restant dans la grille pour determiner en     //suite si la partie est gagné ou non 
  int symbol_count = 0;
  for (int i = 0; i < M; i++) {
    for (int j = 0; j < N; j++) {
      if (grid[i][j] != ' ') {
        symbol_count++;
      }
    }
  }
  return symbol_count;
}