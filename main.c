#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

bool alignement_impossible(char **grille, int M, int N) {
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
      if (compteur >= 2) {
        return true;
      }
    }
  }
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
      if (compteur >= 2) {
        return true;
      }
    }
  }
  // diagonale de bas a en haut
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
      if (compteur >= 2) {
        return true;
      }
    }
  }
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
      if (compteur >= 2) {
        return true;
      }
    }
  }

  return false;
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

void swap_symboles(char **grille, int x1, int y1, int x2, int y2) {
  char temp;
  temp = grille[y1][x1];
  grille[y1][y1] = grille[y2][x2];
  grille[y2][x2] = temp;
}

void affiche_grille(char **grille, int M, int N) {
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

      printf("%c ", grille[i][j]);
    }
    printf("\n");
  }
}

void gravite(char **grille, int M, int N) {
  char temp;
  int compteur = 0;
  for (int i = 0; i < M; i++) {
    for (int j = N - 1; j > 0; j--) {
      if (grille[i][j] == ' ') {
        for (int x = j - 1; x >= 0; x--)
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

void sup_alignements(char **grille, int M, int N) {
  horizontale(grille, M, N);
  verticale(grille, M, N);
  diagonale1(grille, M, N);
  diagonale2(grille, M, N);
}

int main() {

  int M, N, num_symboles;
  char **grille;
  bool align;
  num_symboles = 0;

  printf("Entrez les dimensions de la grille (M x N) : ");
  scanf("%d %d", &M, &N);
  do {
    printf("Entrez le nombre de symboles différents (entre 4 et 6 ) : ");
    scanf("%d", &num_symboles);
  } while (num_symboles < 4 || num_symboles > 6 || num_symboles == ' ');

  grille = cree_grille(M, N, num_symboles);

  do {
    sup_alignements(grille, M, N);
    remplis(grille, M, N, num_symboles);

  } while (alignements(grille, M, N) == true);


///////////////////////////////////////////// A CHANGER


  
  affiche_grille(grille, M, N);
  int x1, y1, x2, y2;
  do {
    do {
      printf("Choisir les coordonnées du points a changer x:");
      scanf("%d", &x1);
    } while (x1 < 0 || x1 > M - 1 || x1 == ' ');
    do {
      printf("Choisir les coordonnées du points a changer y:");
      scanf("%d", &y1);
    } while (y1 < 0 || y1 > N - 1 || y1 == ' ');
    do {
      printf("Choisir les coordonnées du points échanger x:");
      scanf("%d", &x2);
    } while (x2 < 0 || x2 > M - 1 || x2 == ' ');
    do {
      printf("Choisir les coordonnées du points échanger y:");
      scanf("%d", &y2);
    } while (y2 < 0 || y2 > N - 1 || y2 == ' ');

    swap_symboles(grille, x1, y1, x2, y2);

    if (alignements(grille, M, N) == true) {
      sup_alignements(grille, M, N);
      gravite(grille, M, N);
      affiche_grille(grille, M, N);

    } else {
      swap_symboles(grille, x1, y1, x2, y2);

      do {
        do {
          printf("Choisir les nouvelles coordonnées du points a changer x:");
          scanf("%d", &x1);
        } while (x1 < 0 || x1 > M - 1 || x1 == ' ');
        do {
          printf("Choisir les nouvelles coordonnées du points a changer y:");
          scanf("%d", &y1);
        } while (y1 < 0 || y1 > N - 1 || y1 == ' ');
        do {
          printf("Choisir les nouvelles coordonnées du points échanger x:");
          scanf("%d", &x2);
        } while (x2 < 0 || x2 > M - 1 || x2 == ' ');
        do {
          printf("Choisir les nouvelles coordonnées du points échanger y:");
          scanf("%d", &y2);
        } while (y2 < 0 || y2 > N - 1 || y2 == ' ');
        swap_symboles(grille, x1, y1, x2, y2);

        if (alignements(grille, M, N) == true) {
          // sup_alignements(grille, M, N);
          gravite(grille, M, N);
          affiche_grille(grille, M, N);
        } else {
          swap_symboles(grille, x1, y1, x2, y2);
        }

      } while (alignements(grille, M, N) == false);
    }
  } while (alignement_impossible(grille, M, N) == true);

  for (int i = 0; i < M; i++) {
    free(grille[i]);
  }
  free(grille);

  return 0;
} 
