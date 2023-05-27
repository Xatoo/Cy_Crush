int emptyFile(const char *nameFile);
void saveGrid(char **grille, int M, int N, const char *nameFile);
void saveData(const char *nameFile, int M, int N, unsigned long tps, int score,
              int nbSymb);
void saveHighscores(const char *nameFile, char *name, int score,
                    unsigned long tps);
void printHighscores(char const *nameFile);
void loadData(const char *nameFile, unsigned long *tps, int *M, int *N,
              int *score, int *nbSymb);