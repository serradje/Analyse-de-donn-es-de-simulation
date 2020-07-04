/**
 * flie Flux.c
 * contient les fonctions qui traitent les données d'un flux
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "Flux.h"

/**
 * fonction qui renvoi un new flux
 */

Flux New_Flux(void){
        return (Flux) NULL;
}

/**
 * fonction qui libere l'espace memoire occupe par flux
 */
 
void Free_Flux(ListFlux l){
        Flux tmp = NULL;
        tmp = l->First;
        Flux curr= NULL;

        while (tmp != NULL) {
                curr=tmp;
                tmp=tmp->next;
                free(curr->s);
                free(curr->d);
                free (curr);
        }

        free(l);

}

/**
 * fonction qui cherche si un flux est dans la liste
 */
 
Flux FluxEstDans(Flux f,int fid)
{
       
        Flux tmp = NULL;
        tmp = f;

        while(tmp != NULL)
        {
                if (tmp->fid == fid )
                        return tmp;  


                tmp=tmp->next;
        }

        return NULL; 

}

/**
 * fonction qui ajoute un flux a la liste des flux
 */

void Add_Flux(ListFlux f,Event data,Trace t, Option option){


        Flux tmp=New_Flux();
        tmp = FluxEstDans(f->First,t->fid);

        if ( tmp == NULL ) 
        {
                data->nbr_flux++;
                tmp = (Flux) malloc(sizeof(_Flux));
                if ( tmp != NULL)
                {
                        tmp->fid = t->fid;
                        tmp->s = (char*)malloc(strlen(t->s)+1);
                        strcpy(tmp->s,t->s);
                        tmp->d = (char*)malloc(strlen(t->d)+1);
                        strcpy(tmp->d,t->d);
                        tmp->nbr_paquet=0;
                        tmp->nbr_paquet_perdus=0;
                        tmp->nbr_paquet_emis=0;
                        tmp->nbr_paquet_recus=0;
                        tmp->delai_moyen=0;
                        tmp->EtatFlux=0;
                        tmp->t_debut=t->t;
                        tmp->t_fin=t->t;

                        if ( f->First == NULL )
                        {
                                f->First = tmp;
                        }
                        else
                        {
                                tmp->next=f->First;
                                f->First = tmp;
                        }
                }
        }

        if (tmp->fid == t->fid )
        {

                tmp->t_fin=t->t;

                switch (t->code)
                {
                case 0:
                        tmp->nbr_paquet_emis++;
                        if ( tmp->EtatFlux == 0)
                        {
                                data->nbr_flux_actif++;
                                if ( option->flux_actif )
                                {
                                        if ( (ajustement4 == 0) )
                                        {
                                                fprintf(option->file_flux_actif, "%f %d \n", t->t, data->nbr_flux_actif );
                                        }
                                        ajustement4=(ajustement4+1)%500;
                                }
                        }
                        tmp->EtatFlux++;

                        break;
                case 1:

                        break;
                case 2:

                        break;
                case 3:


                        tmp->EtatFlux--;
                        if ( tmp->EtatFlux == 0)
                        {
                                data->nbr_flux_actif--;

                                if ( option->flux_actif )
                                {
                                        if ( (ajustement4 == 0) )
                                        {
                                                fprintf(option->file_flux_actif, "%f %d \n", t->t, data->nbr_flux_actif );
                                        }
                                        ajustement4=(ajustement4+1)%500;
                                }
                        }
                        break;
                case 4:
                        tmp->nbr_paquet_perdus++;
                        tmp->EtatFlux--;
                        if ( tmp->EtatFlux == 0)
                        {
                                data->nbr_flux_actif--;
                                if ( option->flux_actif )
                                {
                                        if ( (ajustement4 == 0) )
                                        {
                                                fprintf(option->file_flux_actif, "%f %d \n", t->t, data->nbr_flux_actif );
                                        }
                                        ajustement4=(ajustement4+1)%500;
                                }
                        }
                        break;
                default:

                        break;
                }
        }

}
