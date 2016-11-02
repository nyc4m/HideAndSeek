#include <stdio.h>
#include <stdlib.h>


int lireParam(char *arg);
int executer(int option, char *cachette, char *sujet);
void fermer(int cachette, int sujet);
void executerOption(int cachette, int sujet, int option);
int initialiserFichier(int option, int *cachette, int *sujet, char *nomC, char *nomS);
