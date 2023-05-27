#include "sauvegarde.h"
#include "alignement.h"
#include "grille.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

int emptyFile(const char *nameFile) {
  //verifis si le fichier passez en paramètre est vide
  
  FILE *file = fopen(nameFile, "r");

  if (file == NULL) {
    return 1;
  }
  return 0;
}
void saveGrid(char **grille, int M, int N, const char *nameFile) {
  //enregistre la grille dans un fichier txt
  
  FILE *file = fopen(nameFile, "w");

  for (int i = 0; i < M; i++) {
    for (int j = 0; j < N; j++) {
      fprintf(file, "%c ", grille[i][j]);
    }
    fprintf(file, "\n");
  }

  fclose(file);
}

void saveData(const char *nameFile, int M, int N, unsigned long tms, int score,
              int nbSymb) {
  //La fonction enregistre toutes les données utile lorsque l'on veut             //reprendre une grille sauvegarde dans un autre fichier txt
  FILE *file = fopen(nameFile, "w");

  fprintf(file, "%d %d\n", M, N);
  fprintf(file, "%ld\n", tms);
  fprintf(file, "%d\n", score);
  fprintf(file, "%d\n", nbSymb);

  fclose(file);
}

void saveHighscores(const char *nameFile, char *name, int score,
                    unsigned long tms) {
  //enregistre dans un fichier score.txt le score a la fin d'une partie
  FILE *file = fopen(nameFile, "a+");
  fprintf(file, "\n");
  fputs(name, file);
  fprintf(file, "-");
  fprintf(file, "%ld-", tms);
  fprintf(file, "%d", score);

  fclose(file);
}

void printHighscores(char const *nameFile) {
  //permet d'afficher en fin de partie tout les meilleurs scores enregistrés
  FILE *file = fopen(nameFile, "r");
  char line[256];
  if (file == NULL) {
    printf("Aucun highscore enregistré");

  } else {
    printf("Tout les meilleurs scores de la forme (Nom-temps-score): \n");
    while (fgets(line, sizeof(line), file) != NULL) {
      printf("%s", line);
    }
  }
  fclose(file);
}
void loadData(const char *nameFile, unsigned long *tms, int *M, int *N,
              int *score, int *nbSymb) {
  //permet de recuperer dans un fichier txt tout les données qui vont servir   //un recuperer de manière simple la grille enregistrée dans un autre fichier txt
  
  FILE *file = fopen(nameFile, "r+");
  if (file == NULL) {
    printf("Aucune sauvegarde disponible");
    return;
  }

  fscanf(file, "%d %d", M, N);
  fscanf(file, "%ld", tms);
  fscanf(file, "%d", score);
  fscanf(file, "%d", nbSymb);

  fclose(file);
}