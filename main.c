#include "alignement.h"
#include "grille.h"
#include "sauvegarde.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#define color(param) printf("\033[%sm", param)

int main() {
  time_t beg;
  time_t end;
  unsigned long tms = 0;
  int score = 0;
  int M, N, num_symbols = 0;
  char **grid;
  char name[100];
  int ans1, ans2;
  
  //on commence par savoir si le joueur veut charger la derniere partie sauvegarder ou en commencer une autre 
  
  printf("Entrez votre pseudo pour commencer à jouer :");
  scanf("%s", name);
  printf("Bonjour %s, si vous voulez charger la dernière partie enregistrée "
         "tapez 0, si vous voulez en commencer une autre tapez 1 :",
         name);
  scanf("%d", &ans1);
  if (ans1 == 0) {
    if (emptyFile("grille.txt") == 0) {

      loadData("data.txt", &tms, &M, &N, &score, &num_symbols);
      FILE *file = fopen("grille.txt", "r+");
      grid = malloc(M * sizeof(char *));
      for (int i = 0; i < M; i++) {
        grid[i] = malloc(N * sizeof(char));
        for (int j = 0; j < N; j++) {

          fscanf(file, "%c ", &grid[i][j]);
        }
      }

      printf("\n");
      fclose(file);

      for (int i = 0; i < M; i++) {
        for (int j = 0; j < N; j++) {
          if (grid[i][j] == '-') {
            grid[i][j] = ' ';
          }
        }
      }
    } else {
      printf("Il n'y a aucune sauvegarde disponible ");
      return 0;
    }

  } else {
    printf("Entrez les dimensions de la grille (M x N) : ");
    scanf("%d %d", &M, &N);
    do {
      printf("Entrez le nombre de symbols différents (entre 4 et 6 ) : ");
      scanf("%d", &num_symbols);
    } while (num_symbols < 4 || num_symbols > 6 || sizeof(num_symbols) == 1);

    grid = create_grid(M, N, num_symbols);

    do {
      del_alignment(grid, M, N);
      remplis(grid, M, N, num_symbols);

    } while (alignment(grid, M, N) == 1);
  }

  printgrid(grid, M, N, score, num_symbols);
  int x1 = 0, y1 = 0, x2 = 0, y2 = 0;

  do {
    printf(
        "Voulez-vous enregistrer votre partie ?(taper 1 si oui,sinon taper 0)");
    scanf("%d", &ans2);
    if (ans2 == 1) {
      end = time(NULL);
      for (int i = 0; i < M; i++) {
        for (int j = 0; j < N; j++) {
          if (grid[i][j] == ' ') {
            grid[i][j] = '-';
          }
        }
      }

      tms = (unsigned long)difftime(end, beg);
      saveGrid(grid, M, N, "grid.txt");
      saveData("data.txt", M, N, tms, score, num_symbols);
      printf("La grille a bien été enregistrée");
      return 0;
    }
    beg = time(NULL);
    do {
      printf("Choisir les coordonnées du points a changer x:");
      scanf("%d", &x1);
    } while (x1 < 0 || x1 > N - 1);
    do {
      printf("Choisir les coordonnées du points a changer y:");
      scanf("%d", &y1);
    } while (y1 < 0 || y1 > M - 1);
    do {
      printf("Choisir les coordonnées du points échanger x:");
      scanf("%d", &x2);
    } while (x2 < 0 || x2 > N - 1);
    do {
      printf("Choisir les coordonnées du points échanger y:");
      scanf("%d", &y2);
    } while (y2 < 0 || y2 > M - 1);

    grid = swap_symbols(grid, x1, y1, x2, y2);

    if (alignment(grid, M, N) == 0) {
      while (alignment(grid, M, N) == 0) {

        grid = swap_symbols(grid, x1, y1, x2, y2);
        printf("Le déplacement n'est pas possible !\n");
        do {
          printf("Choisir les nouvelles coordonnées du points a changer x:");
          scanf("%d", &x1);
        } while (x1 < 0 || x1 > N - 1);
        do {
          printf("Choisir les nouvelles coordonnées du points a changer y:");
          scanf("%d", &y1);
        } while (y1 < 0 || y1 > M - 1);
        do {
          printf("Choisir les nouvelles coordonnées du points échanger x:");
          scanf("%d", &x2);
        } while (x2 < 0 || x2 > N - 1);
        do {
          printf("Choisir les nouvelles coordonnées du points échanger y:");
          scanf("%d", &y2);
        } while (y2 < 0 || y2 > M - 1);

        grid = swap_symbols(grid, x1, y1, x2, y2);
      }
    }

    do {

      del_alignment(grid, M, N);

      gravity(grid, M, N);
    } while (alignment(grid, M, N) == 1);
    score += 1;
    printgrid(grid, M, N, score, num_symbols);

  } while (alignment_possible(grid, M, N) == 1);
  end = time(NULL);
  if (checkwin(grid, M, N) <= 2) {
    printf(" Félicitations ! Vous avez gagné ! \n");
    unsigned long seconde = (unsigned long)difftime(end, beg) + tms;
    saveHighscores("scores.txt", name, score, seconde);
    printHighscores("scores.txt");
  } else {
    printf(" Dommage... vous avez perdu.\n");
    printHighscores("scores.txt");
  }

  for (int i = 0; i < M; i++) {
    free(grid[i]);
  }
  free(grid);

  return 0;
}
