#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "Event.h"

/**
 * flie Event.c
 * contient les fonctions qui traitent un evenement
 */


/**
 * focntion qui cree et inialise un evenement
 */

Event New_Event(void){
	
        Event event = (Event) malloc(sizeof(_event));
        event->nbr_paquet_perdus=0;
        event->nbr_paquet_traites=0;
        event->nbr_paquet_emis=0;
        event->nbr_paquet_recus=0;
        event->nbr_flux=0;
        event->nbr_paquet_perdus=0;
        event->taux_perte=0;
        event->nbr_noeud=0;
        event->delai_moyen=0;
        event->nbr_event=0;
        event->temps_attente_file=0;
        event->temps_transmission_liens=0;
        event->nbr_paquet_perdusT=0;
        event->nbr_flux_actif=0;
        event->ecart_type=0;
        event->nbr_paquet_File=0;
        event->nbr_paquet_transit=0;
        event->intervalle=1;

        return event;
}



Trace New_Trace(void){
        return (Trace) NULL;
}


void Free_Event(Event e){
        free(e);

}

/**
 * fonction qui ajoute un event a la liste
 */

void Add_Event(Event e,Trace t,Option option){
        e->nbr_event++;
        switch (t->code)
        {
        case 0:
                e->nbr_paquet_emis++;
                e->nbr_paquet_File++;
                e->nbr_paquet_transit++;
                break;
        case 1:
                e->nbr_paquet_File++;
                break;
        case 2:
                e->nbr_paquet_traites++;
                e->nbr_paquet_File--;
                break;
        case 3:
                e->nbr_paquet_recus++;
                e->nbr_paquet_File--;
                e->nbr_paquet_transit--;
                break;
        case 4:
                e->nbr_paquet_perdus++;
                e->nbr_paquet_perdusT++;
                if ( t->t > e->intervalle )
                {
                        if ( option->perdus )
                                fprintf(option->file_perdus, "%f %d \n", t->t, e->nbr_paquet_perdusT );
                        e->nbr_paquet_perdusT = 0;
                        e->intervalle++;

                }


                e->nbr_paquet_File--;
                e->nbr_paquet_transit--;
                break;
        default:

                break;
        }

        if ( strcmp(option->noeud, "all") == 0 )
        {
                if ( (ajustement == 0) )
                {
                        fprintf(option->file_attente, "%f %d \n", t->t, e->nbr_paquet_File );
                }
                ajustement=(ajustement+1)%250;
        }

        if ( option->transit && t->code != 1 && t->code !=2 )
        {
                if ( (ajustement2 == 0) )
                {
                        fprintf(option->file_transit, "%f %d \n", t->t, e->nbr_paquet_transit );
                }
                ajustement2=(ajustement2+1)%500;
        }

}
