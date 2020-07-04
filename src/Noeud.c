#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "Noeud.h"

/**
 * file Noeud.c
 * contietn les fonction qui traite les noeuds
 */

Noeud New_Noeud(void){
        return (Noeud) NULL;
}


void Free_Noeud(ListNoeud N){
        Noeud NN = NULL;
        NN = N->First;
        Noeud tmp= NULL;

        while (NN != NULL) {
                tmp = NN;
                NN = NN->next;
                free(tmp->nom);
                free (tmp);
        }

        free(N);

}



/**
 * fonction qui cherche si un noeud est dans la liste
 */
 
Noeud NoeudEstDans(Noeud N,char nom[SIZE])
{
      
        Noeud tmp = NULL;
        tmp = N;

        while(tmp != NULL)
        {
                if (strcmp(tmp->nom, nom) == 0)
                        return tmp;  

                tmp=tmp->next;
        }

        return NULL;
}

/**
 * fonction qui ajoute un noeud a la liste
 */
 
void Add_Noeud(ListNoeud N,Event e,Trace t,Option option){

        Noeud tmp=New_Noeud();
        tmp = NoeudEstDans(N->First,t->pos);

        if ( tmp == NULL ) // Je dois creer le noeud
        {
                e->nbr_noeud++;
                tmp =  (Noeud) malloc(sizeof(_Noeud));
                if ( tmp != NULL)
                {

                        tmp->nom = (char*)malloc(strlen(t->pos)+1);
                        strcpy(tmp->nom,t->pos);

                        tmp->nbr_paquet_in=0;
                        tmp->nbr_paquet_out=0;
                        tmp->nbr_paquet_perdus=0;
                        tmp->nbr_paquet_emis=0;
                        tmp->nbr_paquet_recus=0;
                        tmp->nbr_paquet_file=0;
                        tmp->size_file=0;

                        if ( N->First == NULL )
                        {
                                N->First = tmp;
                        }
                        else
                        {
                                tmp->next = N->First;
                                N->First = tmp;
                        }
                }
        }

        if (strcmp(tmp->nom, t->pos) == 0)
        {

                switch (t->code)
                {
                case 0:
                        tmp->nbr_paquet_emis++;
                        tmp->nbr_paquet_file++;
                        break;
                case 1:
                        tmp->nbr_paquet_in++;
                        tmp->nbr_paquet_file++;
                        break;
                case 2:
                        break;
                case 3:
                        tmp->nbr_paquet_recus++;

                        tmp->nbr_paquet_file--;
                        break;
                case 4:
                        tmp->nbr_paquet_perdus++;
                        tmp->nbr_paquet_file--;
                        if ( tmp->nbr_paquet_perdus == 1  )
                        {
                                tmp->size_file=tmp->nbr_paquet_file;

                        }

                        break;
                default:

                        break;
                }

                if ( strcmp(option->noeud, tmp->nom) == 0 )
                {
                        if ( (t->code != 2) && (ajustement == 0) )
                        {
                                fprintf(option->file_attente, "%f %d \n", t->t, tmp->nbr_paquet_file);
                        }
                       ajustement=(ajustement+1)%250;
                }


        }


}

/**
 * fonction qui renvoi un paquet
 */
 
Paquet New_Paquet(void){
        return (Paquet) NULL;
}

/**
 * focntion qui libere la memoire alloué pour le chemin d'un paquet
 */
 
void Free_Trajet(ListTrajet l){
        Trajet tmp = l->First;
        Trajet ll= NULL;

        while (tmp != NULL) { 
                ll = tmp;
                tmp = tmp->next;
                free(ll->pos);
                free (ll);
        }

        free(l);

}

/**
 * fonction qui free la memoire occupe par un paquet
 */
 
void Free_Paquet(ListPaquet l){
        Paquet tmp = l->First;
        Paquet ll= NULL;

        while (tmp != NULL) {
                ll = tmp;
                tmp = tmp->next; 
                Free_Trajet(ll->l);
                free(ll->s);
                free(ll->d);
                free(ll->prec);
                free (ll);  
        }

        free(l);
}


/**
 * fonction qui retourne un paquet en fonction de son pid
 */
 
Paquet getPaquet(Paquet p,int pid)
{
        Paquet tmp = p;

        while(tmp != NULL)
        {
                if (tmp->pid == pid )
                        return tmp;  

                tmp=tmp->next;
        }

        return NULL;
}

/**
 * fonction qui ajoute un paquet a la liste des paquet
 */

void Add_Paquet(ListPaquet p,ListNoeud n,ListFlux f,Event e,Trace t, Option option){

        Paquet tmp=New_Paquet();
	int nb_paquet;
        if ( t->code == 0 )
        {
                ListTrajet lt = (ListTrajet) malloc(sizeof(_listTrajet));
                tmp = (Paquet) malloc(sizeof(_paquet));
                if ( tmp != NULL)
                {
                        tmp->pid=t->pid;

                        tmp->s = (char*)malloc(strlen(t->s)+1);
                        strcpy(tmp->s,t->s);
                        tmp->d = (char*)malloc(strlen(t->d)+1);
                        strcpy(tmp->d,t->d);
                        tmp->prec = (char*)malloc(strlen(t->pos)+1);
                        strcpy(tmp->prec,t->pos);

                        tmp->temps_attente_file = 0;
                        tmp->temps_transmission_liens=0;

                        Trajet tr = (Trajet) malloc(sizeof(_listTrajet));
                        tr->pos = (char*)malloc(strlen(t->pos)+1);
                        strcpy(tr->pos,t->pos);
                        tr->date=t->t;
                        tr->code=t->code;
                        tr->next = NULL;
                        lt->First = tr;
                        tmp->l = lt;

                        if ( p->First == NULL )
                        {
                                p->First = tmp;
                        }
                        else
                        {
                                tmp->next = p->First;
                                p->First = tmp;
                        }
                }
        }
        else
        {
                tmp = getPaquet(p->First,t->pid);   
                if ( tmp != NULL )
                {
                        Trajet tr = (Trajet) malloc(sizeof(_listTrajet));
                        tr->pos = (char*)malloc(strlen(t->pos)+1);
                        strcpy(tr->pos,t->pos);
                        tr->date=t->t;
                        tr->code=t->code;
                        tr->next = NULL;

                        Trajet tmp2 = tmp->l->First;
                        while(tmp2->next != NULL) tmp2 = tmp2->next;
                        tmp2->next = tr;

                        if ( tr->code == 2 && tmp2->code == 0 )
                                tmp->temps_attente_file+=tr->date-tmp2->date;

                        if ( tr->code == 2 && tmp2->code == 1 )
                                tmp->temps_attente_file+=tr->date-tmp2->date;

                        if ( tr->code == 3 && tmp2->code == 1 )
                                tmp->temps_attente_file+=tr->date-tmp2->date;

                        if ( tr->code == 1 && tmp2->code == 2 )
                                tmp->temps_transmission_liens+=tr->date-tmp2->date;


                        if ( t->code == 1 )
                        {

                                char *tmp3 = (char*)realloc(tmp->prec,strlen(t->pos)+1);
                                tmp->prec = tmp3;
                                strcpy(tmp->prec,t->pos);
                        }

                        if ( t->code == 2 )
                        {
                                Noeud ntmp = New_Noeud();
                                ntmp = NoeudEstDans(n->First,tmp->prec);
                                if ( ntmp != NULL)
                                {
                                        ntmp->nbr_paquet_out++;
                                        ntmp->nbr_paquet_file--;

                                        if ( strcmp(option->noeud, ntmp->nom) == 0 )
                                        {
                                                if ( (ajustement == 0) )
                                                {
							nb_paquet = ntmp->nbr_paquet_file;
                                                        fprintf(option->file_attente, "%f %d \n", t->t, ntmp->nbr_paquet_file);
                                                }
                                                ajustement=(ajustement+1)%250;
                                        }
                                }
                        }

			
                        if ( t->code == 3 )
                        {

                                Flux ftmp=New_Flux();
                                e->temps_transmission_liens+= tmp->temps_transmission_liens;
                                e->temps_attente_file+=tmp->temps_attente_file;

                                e->delai_moyen+= tmp->temps_transmission_liens+tmp->temps_attente_file;

                                ftmp = FluxEstDans(f->First,t->fid);
                                ftmp->delai_moyen+=tmp->temps_transmission_liens+tmp->temps_attente_file;
                                ftmp->nbr_paquet_recus++;
                                if ( option->flux_delai == t->fid )
                                {
                                        if ( (ajustement1 == 0) )
                                        {
                                                fprintf(option->file_flux_delai, "%f %f \n", t->t,(float)ftmp->nbr_paquet_recus);
                                        }
											ajustement1=(ajustement1+1)%25;
                                }
                        }
                }
        }
}


