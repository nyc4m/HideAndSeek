#include "montrer.h"
#include "nettoyer.h"

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
  nettoyer(cachette, tailleSujet);
}

int lireTaille(int cachette)
{
  int res = 0;
  int t = lseek(cachette, SEEK_SET, SEEK_END)-4;
  lseek(cachette, t,SEEK_SET);
  read(cachette, &res, sizeof(int));
  return res;
}
