#include "cacher.h"
#include "montrer.h"
#include "nettoyer.h"
#include "hide.h"

int main(int argc, char **argv)
{
  int exec = 0;
  if(argc == 4)
  {
    exec = executer(lireParam(argv[1]), argv[2], argv[3]);
  }else{
    fprintf(stderr, "[ERREUR] Pas assez d'arguments\n");
    exec = 1;
  }
  return exec;
}

void fermer(int cachette, int sujet)
{
  close(cachette);
  close(sujet);
}

int lireParam(char *arg)
{
  int res = 0; //renvoie 1 pour cacher, 2 pour montrerm 0 en cas d'erreur
  if(arg[0] == '-')
  {
    if(arg[1] == 'h')
    {
      res = 1;
    }else if(arg[1] == 's')
    {
      res = 2;
    }
  }

  return res;
}

int executer(int option, char *cachette, char *sujet)
{
  int res = 0;
  int c = 0;
  int s = 0;
  if(option == 1 || option == 2)
  {
    if(initialiserFichier(option, &c, &s, cachette, sujet) == 0)
    {
      executerOption(c,s,option);
      printf("Commande executee correctement !\n");
    }else{
      res = 1;
      fprintf(stderr, "[ERREUR] Probleme de fichier : %s\n", strerror(errno));
    }
    fermer(c,s);
  }
  else{
    res = 1;
    fprintf(stderr, "[ERREUR] Commande inconnue\n");
  }
  return res;
}

void executerOption(int cachette, int sujet, int option)
{
  void (*operation[2])(int, int)={cacher, montrer};
  operation[option-1](cachette, sujet);
}

int initialiserFichier(int option, int *cachette, int *sujet, char *nomC, char *nomS) {
  int res = 0;
  if(option == 1)
  {
    *cachette = open(nomC, O_WRONLY);
    *sujet = open(nomS, O_RDONLY);
  }else{
    *cachette = open(nomC, O_RDONLY);
    *sujet = open(nomS, O_TRUNC|O_CREAT|O_WRONLY, 0664);
  }
  if(*cachette< 0 | *sujet<0)
  {
    res = 1;
  }
  return res;
}
