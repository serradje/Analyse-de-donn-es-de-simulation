#ifndef EVENT_H
#define EVENT_H

/**
 * file Event.h
 * contient les structures nécissaire pour le bon fonctionnement de la simulation
 */

#include <stdio.h>

#define SIZE 1024

int ajustement;
int ajustement1;
int ajustement2;
int ajustement3;
int ajustement4;

typedef struct str_event
{

        int nbr_paquet_traites;
        int nbr_paquet_emis;
        int nbr_paquet_recus;
        int nbr_flux;
        int nbr_paquet_perdus;
        int nbr_event;
        int nbr_noeud;
        int intervalle;
        int nbr_paquet_File;
        int nbr_paquet_transit; 
        int nbr_flux_actif;
        int nbr_paquet_perdusT;
        float taux_perte;
        float delai_moyen;
        float ecart_type;
        float temps_attente_file;
        float temps_transmission_liens;


}_event,*Event;

typedef struct str_trace {
        float t;
        int code; 
        int pid; 
        int fid; 
        char s[SIZE];
        char d[SIZE]; 
        char pos[SIZE]; 

}_trace,*Trace;

typedef struct str_option {
        char noeud[SIZE];
        int flux_delai;
        int transit;
        int flux_actif;
        int perdus;

        FILE *file_attente;
        FILE *file_flux_actif;
        FILE *file_flux_delai;
        FILE *file_transit;
        FILE *file_perdus;


}_option,*Option;

Trace New_Trace(void);
Event New_Event(void);
void Free_Event(Event e);
void Add_Event(Event e,Trace t, Option option);


#endif
