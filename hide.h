#include <fcntl.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>

#define BUFFERSIZE 25

int lireParam(char *arg);
//fonction a simplifier, redodance ce code
void executer(int option, char *cachette, char *sujet);
void cacher(int cachette, int sujet);
void montrer(int cachette, int sujet);
void fermer(int cachette, int sujet);
void ecrireTaille(int cachette, int sujet);
int lireTaille(int cachette);
void executerOption(int cachette, int sujet, int option);
int initialiserFichier(int option, int *cachette, int *sujet, char *nomC, char *nomS);
