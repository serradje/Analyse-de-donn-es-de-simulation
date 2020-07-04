#ifndef AFFICHAGE_H
#define AFFICHAGE_H

/**
 * file Affichage.h
 * contient les fonction d'affichage et traitement des données
 */

#include <string.h>
#include "Noeud.h"
#include "Flux.h"
#include "Event.h"

void Affichage_Event(Event e);
void Affichage_Noeud(Noeud n,Event e);
void Affichage_Event_Noeud(Noeud n,Event e,char nom[]);
void Affichage_Flux(Flux f,int nbr);
void Affichage_Paquet(Paquet p,int nbr);
void Freetrace(ListFlux lf,Event e, ListPaquet lp, ListNoeud ln, Option opt);
int Readtrace(FILE *fd,ListNoeud ln,ListFlux lf,ListPaquet lp,Event e, int *lu, Option opt);


#endif
