#ifndef FLUX_H
#define FLUX_H

/**
 * file Flux.h
 * contient les structure consernant le traitement des flux
 */


#include <Event.h>

typedef struct str_flux
{
        int fid;
        char* s; 
        char* d; 

        int nbr_paquet;
        int nbr_paquet_emis;
        int nbr_paquet_perdus;
        int nbr_paquet_recus;
        int EtatFlux; 
        float t_debut; 
        float t_fin; 

        float delai_moyen; 

        struct s_flux *next;

} _Flux,*Flux;

typedef struct str_listeflux
{
        Flux First;

} _listeFlux, *ListFlux;

Flux New_Flux(void);
void Free_Flux(ListFlux l);
Flux FluxEstDans(Flux f,int fid);
void Add_Flux(ListFlux f,Event data,Trace t, Option option);



#endif
