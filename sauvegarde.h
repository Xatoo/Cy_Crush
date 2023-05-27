int emptyFile(const char *nameFile);
void saveGrid(char **grid, int M, int N, const char *nameFile);
void saveData(const char *nameFile, int M, int N, unsigned long tms, int score,
              int nbSymb);
void saveHighscores(const char *nameFile, char *name, int score,
                    unsigned long tms);
void printHighscores(char const *nameFile);
void loadData(const char *nameFile, unsigned long *tms, int *M, int *N,
              int *score, int *nbSymb);
