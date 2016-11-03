#include "nettoyer.h"

void nettoyer(int cachette, int tailleSujet)
{
    int taille = lseek(cachette, SEEK_SET, SEEK_END) - tailleSujet - sizeof(int);
    ftruncate(cachette, taille);
}
