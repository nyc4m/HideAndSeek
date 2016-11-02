#include "cacher.h"

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

void ecrireTaille(int cachette, int sujet)
{
  int taille = lseek(sujet, SEEK_SET, SEEK_END);
  write(cachette, &taille, sizeof(int));
}
