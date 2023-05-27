void printgrid(char **grille, int M, int N, int score, int num_symbole);
void remplis(char **grille, int M, int N, int num_symboles);
char **create_grid(int M, int N, int num_symboles);
char **swap_symbols(char **grille, int x1, int y1, int x2, int y2);
void gravity(char **grille, int M, int N);
int checkwin(char **grille, int M, int N);