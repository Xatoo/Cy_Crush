#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#define TailleMax 100

#define couleur(param) printf("\033[%sm", param)
typedef struct {
  int score, longueur, larg, nbSymb;
  char **grille;
  char nomJoueur[TailleMax];
  time_t gametime;
  
} infospartie;

bool asksave() {
  char *commande;
  printf("Voulez-vous sauvegarder votre partie ? (oui/non) : ");
  scanf(" %s\n", commande); 
  // pour savoir si l'utilisateur répond "oui" ou autre chose
  if (strcmp(commande, "oui\n") == 0) {
    return true;
  } 
  else {
    return false;
  }
}



bool askload() {
  char commande[TailleMax];
  printf("Voulez-vous charger une ancienne partie ? (oui/non) : ");
  fgets(commande, TailleMax, stdin);
  if (strcmp(commande, "oui") == 0) {
    return true;
  } 
  else {
    return false;
  }
}

void savegame(infospartie *jeu, const char *nomFichier) {
  FILE *fichier = fopen(nomFichier, "wb");
  if (fichier != NULL) {
    fwrite(jeu, sizeof(infospartie), 1, fichier);
    fclose(fichier);
    printf("Jeu sauvegardé avec succès dans le fichier : %s\n", nomFichier);
  } 
  else {
    printf("Erreur lors de l'ouverture du fichier de sauvegarde.\n");
  }
}

void afficherSauvegardes(){
  FILE* fichier = fopen("sauvegardes.txt", "r");
  if (fichier == NULL) {
    printf("Aucune sauvegarde disponible.\n");
    return;
  }
  infospartie sauvegarde;
  int numsave=1;
  printf("Sauvegardes disponibles :\n");
  while (fread(&sauvegarde, sizeof(infospartie), 1, fichier)) {
    printf("%d. Nom : %s Score: %d\n", numsave, sauvegarde.nomJoueur, sauvegarde.score);
    numsave+=1;
  }
  fclose(fichier);
}

void loadgame(infospartie jeu, const char *nomFichier, int numeroChoisi) {
  FILE *fichier = fopen(nomFichier, "rb");
  infospartie sauvegarde;
  int numeroSauvegarde = 1;
  while (fread(&sauvegarde, sizeof(infospartie), 1, fichier)) {
    if (numeroSauvegarde == numeroChoisi) {
      printf("Sauvegarde %d chargée : Nom : %s Score: %d Temps de jeu: %ld secondes\n", numeroChoisi, sauvegarde.nomJoueur, sauvegarde.score, sauvegarde.gametime);
      time_t debut, fin;
      time(&debut);
      affiche_grille (jeu.grille, jeu.larg, jeu.longueur);
      time(&fin); 
      time_t tempsJeu = fin - debut;
      jeu.gametime +=tempsJeu;
      fclose(fichier);
      return;
    }
    numeroSauvegarde+=1;
  }

  fclose(fichier);
  // Si on arrive ici, cela signifie que le numéro de sauvegarde choisi est invalide
  printf("Numéro de sauvegarde invalide.\n");
}

bool checkwin(char **grille, int M, int N){
  int symbol_count = 0;
  for (int i = 0; i < M; i++) {
      for (int j = 0; j < N; j++) {
          if (grille[i][j] != ' ') {
            symbol_count++;
          }
      }
  }
  if (symbol_count <= 2) {
    printf( " Félicitations ! Vous avez gagné ! \n");
    return 1; 
  } 
  else {
    printf( " Dommage... vous avez perdu.\n");
    return 0;
  }
}
//à modifier pour trier les 
void afficherHighscores(){
  FILE* fichier = fopen("sauvegardes.txt", "r");
  if (fichier == NULL) {
    printf("Aucune sauvegarde disponible.\n");
    return;
  }
  infospartie sauvegarde;
  int numsave=1;
  printf("Meilleurs scores :\n");
  while (fread(&sauvegarde, sizeof(infospartie), 1, fichier)) {
    printf("%d. Nom : %s Score: %d\n", numsave, sauvegarde.nomJoueur, sauvegarde.score);
    numsave+=1;
  }
  fclose(fichier);
}





















bool alignements(char **grille, int M, int N) {
  int i, j, k;
  char symbole;

  // horizontal
  for (i = 0; i < M; i++) {
    for (j = 0; j < N - 2; j++) {
    	if (grille[i][j] != ' '){
      		symbole = grille[i][j];
      		if (grille[i][j + 1] == symbole && grille[i][j + 2] == symbole) {
        		return true;
        }
      }
    }
  }

  // vertical
  for (j = 0; j < N; j++) {
    for (i = 0; i < M - 2; i++) {
    if (grille[i][j] != ' '){		
      symbole = grille[i][j];
      if (grille[i + 1][j] == symbole && grille[i + 2][j] == symbole) {
        return true;
      }
      }
      
    }
  }

  // diagonale 1
  for (i = 0; i < M - 2; i++) {
    for (j = 0; j < N - 2; j++) {
    if (grille[i][j] != ' '){
      symbole = grille[i][j];
      if (grille[i + 1][j + 1] == symbole && grille[i + 2][j + 2] == symbole) {
        return true;
      }
      }
    }
  }
  // diagonale 2
  for (i = 0; i < M - 2; i++) {
    for (j = 2; j < N; j++) {
    if (grille[i][j] != ' '){
      symbole = grille[i][j];
      if (grille[i + 1][j - 1] == symbole && grille[i + 2][j - 2] == symbole) {
        return true;
      }
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

      if(compteur >= 3) {
        for (int k = 0; k < compteur; k++){
          grille[i - k][j + k] = ' ';
        }
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

char **swap_symboles(char **grille, int x1, int y1, int x2, int y2) {

  char temp = grille[y1][x1];
  grille[y1][x1] = grille[y2][x2];
  grille[y2][x2] = temp;
  return grille;
}

bool alignement_possible(char **grille, int M, int N) {
  char **grille_test;
  for (int i = 0; i < M; i++) {
    for (int j = 0; j < N; j++) {
      		// grille[i][j] est la case source
      for (int u = 0; u < M; u++) {
        for (int v = 0; v < N; v++) {
          // grille[u][v] est la case déstination
          //printf("Swap before test...i=%d j=%d u=%d v=%d M=%d N=%d\n",i,j,u,v, M,N);
          //fflush(stdout);
          grille_test = swap_symboles(grille, j, i, v, u);
          //printf("    done...\n");
          //fflush(stdout);
          if (alignements(grille_test, M, N) == true) {
		  //printf("Swap after test OK...\n");
		  //fflush(stdout);
             grille_test = swap_symboles(grille, j, i, v, u);
          //printf("    done...\n");
          //fflush(stdout);
             return true;
          }
	  //printf("Swap after test NOK...\n");
	  //fflush(stdout);
          grille_test = swap_symboles(grille, j, i, v, u);
        //printf("    done...\n");
          //fflush(stdout);
          }
      }
    }
  }
  printf("Fin de partie detectee \n");
  fflush(stdout);
  return false;
}

void sup_alignements(char **grille, int M, int N) {
  horizontale(grille, M, N);
  verticale(grille, M, N);
  diagonale1(grille, M, N);
  diagonale2(grille, M, N);
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

int main() {
	
  int score = 0;
  int M, N, num_symboles;
  char **grille;

  bool align;
  num_symboles = 0;

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

  affiche_grille(grille, M, N, score, num_symboles);
  int x1=0, y1=0, x2=0, y2=0;

  do {
  	affiche_grille(grille, M, N, score, num_symboles);
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

	affiche_grille(grille, M, N, score, num_symboles);

	
    grille = swap_symboles(grille, x1, y1, x2, y2);
    	
    
    if (alignements(grille, M, N) == false) {
     	while (alignements(grille, M, N) == false){

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
	score +=1;
    affiche_grille(grille, M, N, score, num_symboles);

  } while (alignement_possible(grille, M, N) == true);

  for (int i = 0; i < M; i++) {
    free(grille[i]);
  }
  free(grille);

  return 0;
}
