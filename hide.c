#include "hide.h"

int main(int argc, char **argv)
{
  int exec = 0;
  if(argc == 4)
  {
    executer(lireParam(argv[1]), argv[2], argv[3]);
  }else{
    fprintf(stderr, "Pas assez d'arguments\n");
    exec = 1;
  }
  return exec;
}


void cacher(int cachette, int sujet)
{
  char buffer[BUFFERSIZE];
  int lu=0;
  lseek(cachette, SEEK_SET, SEEK_END);
  while((lu = read(sujet, buffer, BUFFERSIZE))>0)
  {
    write(cachette, buffer, lu);
  }
  ecrireTaille(cachette, sujet);
}

void montrer(int cachette, int sujet)
{
  char *buffer[1]; //le buffer ne stocke qu'un seul caractere
  int compteur = 0;
  int tailleCachette = lseek(cachette, 0, SEEK_END);
  int tailleSujet = lireTaille(cachette);
  lseek(cachette, 0, SEEK_SET); //le curseur est remis au debut du fichier
  lseek(cachette, tailleCachette - tailleSujet - sizeof(int), SEEK_SET);
  int lu = 0;
  //On lit char par char jusqu'a la taille du message puis on arrete. La taille ne doit pas etre lue.
  while((lu = read(cachette, buffer, 1))>0 && compteur < tailleSujet)
  {
    write(sujet, buffer, lu);
    compteur++;
  }
}

void fermer(int cachette, int sujet)
{
  close(cachette);
  close(sujet);
}

void ecrireTaille(int cachette, int sujet)
{
  int taille = lseek(sujet, SEEK_SET, SEEK_END);
  write(cachette, &taille, sizeof(int));
}

int lireTaille(int cachette)
{
  int res = 0;
  int t = lseek(cachette, SEEK_SET, SEEK_END)-4;
  lseek(cachette, t,SEEK_SET);
  read(cachette, &res, sizeof(int));
  return res;
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

void executer(int option, char *cachette, char *sujet)
{
  int c = 0;
  int s = 0;
  if(option == 1 || option == 2)
  {
      if(option == 1)
      {
        if((c = open(cachette, O_WRONLY)) != 0 && (s = open(sujet, O_RDONLY)) != 0)
        {
          cacher(c, s);
        }else{
          fprintf(stderr, "Probleme de fichier : %s\n", strerror(errno));
        }
      }else{
        if((c = open(cachette, O_RDONLY)) != 0 && (s = open(sujet, O_TRUNC | O_CREAT | O_WRONLY, 0664)))
        {
          montrer(c, s);
        }else{
          fprintf(stderr, "Probleme de fichier : %s\n", strerror(errno));
        }
      }
      fermer(c,s);
  }else{
    fprintf(stderr, "Commande inconnue\n");
  }
}