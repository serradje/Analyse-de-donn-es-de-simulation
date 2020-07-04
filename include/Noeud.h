#ifndef NOEUD_H
#define NOEUD_H

/**
 * file Noeud.h
 * contient les structures pour le traitement des noeuds et les paquets
 */



#include "Event.h"
#include "Noeud.h"
#include "Flux.h"

#define SIZE 1024

typedef struct str_Noeud
{
        char* nom;
        int nbr_paquet_emis;
        int nbr_paquet_recus;
        int nbr_paquet_perdus;
        int nbr_paquet_in;
        int nbr_paquet_out;
        int nbr_paquet_file;
        int size_file;

        struct str_Noeud *next;

}_Noeud,*Noeud;


typedef struct str_ListNoeud
{
        Noeud First;

}_listNoeud,*ListNoeud;

typedef struct str_trajet
{
        char* pos;
        float date;
        int code;

        struct str_trajet *next;

}_trajet,*Trajet;

typedef struct Str_ListTrajet
{
        Trajet First;

}_listTrajet,*ListTrajet;

typedef struct Str_paquet
{
        int pid;

        char* s;
        char* d; 
        ListTrajet l;

        char* prec;

        float temps_attente_file;
        float temps_transmission_liens;

        struct Str_paquet *next;

}_paquet,*Paquet;

typedef struct Str_ListPaquet
{
        Paquet First;

}_listPaquet,*ListPaquet;


Noeud New_Noeud(void);
void Free_Noeud(ListNoeud N);
Noeud NoeudEstDans(Noeud N,char* nom);
void Add_Noeud(ListNoeud N,Event e,Trace t,Option option);

Paquet New_Paquet(void);
void Free_Trajet(ListTrajet l);
void Free_Paquet(ListPaquet l);
Paquet getPaquet(Paquet p,int pid);
void Add_Paquet(ListPaquet p,ListNoeud n,ListFlux f,Event e,Trace t, Option option);



#endif
