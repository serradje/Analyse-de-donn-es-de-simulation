#include <stdlib.h>
#include <stdio.h>

#include "Affichage.h"
#include "color.h"
#include <math.h>

/**
 * fonction affichant  les données d'un evenement
 */

void Affichage_Event(Event e)
{
		printf(FG_YELLOW"======================================================= \n"NOCOLOR);
        printf("Nombre Evenements : ");
        printf(FG_BLUE": %d \n" NOCOLOR,e->nbr_event);
        printf("Nombre Paquets Traités : ");
        printf( FG_BLUE" %d \n"NOCOLOR,e->nbr_paquet_traites);
        printf("Nombre Paquets Emis : ");
        printf( FG_BLUE" %d \n"NOCOLOR,e->nbr_paquet_emis);
        printf("Nombre Paquets Reçus : ");
        printf( FG_BLUE" %d \n"NOCOLOR,e->nbr_paquet_recus);
        printf("Nombre de Paquets Perdus : ");
        printf( FG_BLUE" %d \n"NOCOLOR,e->nbr_paquet_perdus);
        e->taux_perte = (float)e->nbr_paquet_perdus/(float)e->nbr_paquet_emis*100;
        printf("Taux de Perte : ");
        printf( FG_BLUE" %f %% \n",e->taux_perte);
        printf(FG_YELLOW"======================================================= \n"NOCOLOR);
        printf("Nombre de Flux : ");
        printf(FG_BLUE" %d \n"NOCOLOR,e->nbr_flux);
        printf("Nombre de Noeud : ");
        printf(FG_BLUE" %d \n"NOCOLOR,e->nbr_noeud);
         printf(FG_YELLOW"=======================================================\n"NOCOLOR);



        e->temps_attente_file = (float)e->temps_attente_file/(float)e->nbr_paquet_recus;
        e->temps_transmission_liens = (float)e->temps_transmission_liens/(float)e->nbr_paquet_recus;
        printf("Temps moyen transmission sur les liens : ");
        printf(FG_BLUE" %f \n"NOCOLOR,e->temps_transmission_liens);
        printf("Temps moyen d'attente dans les files : ");
        printf(FG_BLUE" %f \n"NOCOLOR,e->temps_attente_file );
        e->delai_moyen =(float)e->delai_moyen/(float)e->nbr_paquet_recus;
        printf("Délai moyen de bout en bout  : ");
        printf(FG_BLUE" %f \n",e->delai_moyen );
        printf(FG_YELLOW"======================================================= \n"NOCOLOR);



}

/**
 * fonction affichant  les données d'un noeud
 */

void Affichage_Noeud(Noeud n,Event e)
{
        Noeud tmp = NULL;
        tmp = n;
        printf(FG_YELLOW"=============================================================================================================================== \n"NOCOLOR);
        printf("Informations Noeuds \n");

        printf("%-10s %-10s %-10s %-10s %-10s %-15s %-15s %-15s %-15s\n", "Noeud", "Emis", "Recus","Perdus", "Taille file","Taux de perte", "Proportion perte", "Proportion emis", "Proportion reçus");
        while(tmp != NULL)
        {

                float proportion = (float)tmp->nbr_paquet_perdus/(float)e->nbr_paquet_perdus*100;
                float proportion_emis = (float)tmp->nbr_paquet_emis/(float)e->nbr_paquet_emis*100;
                float proportion_recus = (float)tmp->nbr_paquet_recus/(float)e->nbr_paquet_recus*100;
                float taux = (float)tmp->nbr_paquet_perdus/((float)tmp->nbr_paquet_emis+(float)tmp->nbr_paquet_in)*100;
                printf(FG_BLUE"%-10s"NOCOLOR,tmp->nom);
                printf(" %-10d %-10d %-10d %-15d %f%-10s %f%-9s %f%-8s %-f%-7s  \n",
                       tmp->nbr_paquet_emis,tmp->nbr_paquet_recus,tmp->nbr_paquet_perdus,tmp->size_file,taux,"%",proportion,"%",proportion_emis,"%",proportion_recus,"%");

                tmp=tmp->next;
        }
        printf(FG_YELLOW"=============================================================================================================================== \n\n"NOCOLOR);
}

/**
 * fonction affichant  les evenement d'un noeud
 */

void Affichage_Event_Noeud(Noeud n,Event e,char nom[])
{
        Noeud tmp = n;
        printf(FG_YELLOW"===============================================================================================================================\n"NOCOLOR);
        printf("Informations Noeud \n");
		
        printf("%-10s %-10s %-10s %-10s %-10s %-15s %-15s %-15s %-15s\n", " Noeud ", " Emis ", " Recus "," Perdus ", " Taille file "," Taux de perte ", " Proportion perte ", " Proportion emis ", " Proportion reçus ");
        while(tmp != NULL && strcmp(tmp->nom,nom) != 0)
        {
                tmp=tmp->next;
        }

        if ( tmp !=NULL)
        {

                float proportion = (float)tmp->nbr_paquet_perdus/(float)e->nbr_paquet_perdus*100;
                float proportion_emis = (float)tmp->nbr_paquet_emis/(float)e->nbr_paquet_emis*100;
                float proportion_recus = (float)tmp->nbr_paquet_recus/(float)e->nbr_paquet_recus*100;
                float taux = (float)tmp->nbr_paquet_perdus/((float)tmp->nbr_paquet_emis+(float)tmp->nbr_paquet_in)*100;
                printf(FG_BLUE"%-10s"NOCOLOR,tmp->nom);
                printf(" %-10d %-10d %-10d %-15d %f%-10s %f%-9s %f%-8s %-f%-7s \n",
                       tmp->nbr_paquet_emis,tmp->nbr_paquet_recus,tmp->nbr_paquet_perdus,tmp->size_file,taux,"%",proportion,"%",proportion_emis,"%",proportion_recus,"%");
        }
        else
        {
                printf("Node not Found \n");
        }
        printf(FG_YELLOW"=============================================================================================================================== \n\n"NOCOLOR);
}


/**
 * fonction affichant  les données d'un flux
 */


double Ecart_Type(Flux * f, double m, int nbr) {
	double s = 0;
	double k=  0;
	double kk;

	Flux tmp = f;
	
	 while(tmp != NULL)
	 {
		k += pow(((double)(tmp->t_debut) - m),2);
		tmp = tmp->next;
	 }

		kk = (1/(double)nbr)*k;
		s = sqrt(kk);
		return s;
}

void Intervalle_De_Confiance(Flux *f, double m, int nbr) {

	float s = Ecart_Type(f, m, nbr);
	printf("\n");
	printf("\t\t\t\tIntervalle De Confiance\n");
	printf(FG_YELLOW"\t\t==============================================================\n"NOCOLOR);

	printf("\t\tEnviron 68%% des valeurs se situent dans [%f ; %f]\n", m-s, m+s);
	printf("\t\tEnviron 95%% des valeurs se situent dans [%f : %f]\n", m-(2*s), m+(2*s));
	printf("\t\tEnviron 99%% des valeurs se situent dans [%f ; %f]\n", m-(3*s), m+(3*s));

	printf(FG_YELLOW"\t\t==============================================================\n"NOCOLOR);
}
 
void Affichage_Flux(Flux f,int nbr)
{
        Flux tmp = f;
	double T_moyen;
        printf(FG_YELLOW"=============================================================================================================================== \n"NOCOLOR);
        printf("Informations Flux \n");

        printf("%-10s %-10s %-10s %-10s %-10s %-10s %-10s %-10s %-10s %-10s %-10s\n", "Flux", "Source", "Dest", "Emis", "Recus","Perdus", "Delai moyen","Debut","Fin", "Duree de vie","Taux de perte");
       
        while(tmp != NULL && tmp->fid != nbr )
        {
                tmp = tmp->next;
        }

        if ( tmp != NULL)
        {

                tmp->delai_moyen = (float)tmp->delai_moyen/(float)tmp->nbr_paquet_emis;
		T_moyen = (float)tmp->delai_moyen/(float)tmp->nbr_paquet_recus;
                float taux = (float)tmp->nbr_paquet_perdus/((float)tmp->nbr_paquet_emis)*100;          
                printf(" %-10d %-10s %-10s %-10d %-10d %-10d %-10f %-10f %-10f %-15f %-10f%s \n",
                     tmp->fid,tmp->s,tmp->d,tmp->nbr_paquet_emis,tmp->nbr_paquet_recus,tmp->nbr_paquet_perdus,tmp->delai_moyen,
                       tmp->t_debut,tmp->t_fin,tmp->t_fin-tmp->t_debut,taux,"%");
		Intervalle_De_Confiance(tmp,tmp->delai_moyen,tmp->nbr_paquet_emis);
			
        }
		
        else
        {
                printf("Flow not Found \n");
        }
	
        printf(FG_YELLOW"===============================================================================================================================\n\n"NOCOLOR);

}

/**
 * fonction affichant  les données d'un paquet
 */
 
void Affichage_Paquet(Paquet p,int nbr)
{
        Paquet tmp = p;

        printf(FG_YELLOW"===============================================================================================================================\n"NOCOLOR);
        printf("Informations Paquets \n");
        while(tmp != NULL && tmp->pid != nbr )
        {
                tmp=tmp->next;
        }

        if ( tmp != NULL)
        {
                printf(FG_BLUE"=== Paquet %d === \n"NOCOLOR,tmp->pid);
                printf("Parcours: \n ");
                Trajet tmp2 = tmp->l->First;
                printf("- Emission par %s ", tmp->s);

                Trajet precedent = NULL;
                Trajet precedent2 =NULL;
                while(tmp2 != NULL)
                {
                        precedent = tmp2;
                        tmp2 = tmp2->next;

                        if ( precedent != NULL && tmp2 != NULL)
                        {

                                if ( precedent->code == 0 )
                                        printf("[ t = %f  ] \n ",precedent->date);
                                switch (tmp2->code)
                                {

                                case 1:
                                        printf("- Arrivée sur %s [ temps transmission %s -> %s = %f ] \n ",tmp2->pos,precedent2->pos,tmp2->pos,tmp2->date-precedent->date );
                                        break;
                                case 2:
                                        printf("- Depart depuis la file de %s [ temps attente = %f ] \n ",precedent->pos,tmp2->date-precedent->date );
                                        precedent2=precedent;
                                        break;
                                case 3:
                                        printf("- Arrivée à destination %s [ t = %f [ temps attente = %f] ] \n ",tmp2->pos,tmp2->date,tmp2->date-precedent->date );
                                        break;
                                case 4:
                                        printf("Perte du paquet sur %s \n",tmp2->pos);
                                        break;
                                default:

                                        break;
                                }
                        }
                }

                printf("%-10s %-10s %-15s %-15s %-20s \n", "Source", "Dest°", "Attente_file", "Temps transmission", "Délai acheminement");
                printf(" %-10s %-10s %-15f %-20f %-20f \n",tmp->s,tmp->d,tmp->temps_attente_file,tmp->temps_transmission_liens,tmp->temps_attente_file+tmp->temps_transmission_liens);
           

        }
        else
        {
                printf("Paquet not Found ! \n");
        }
        printf(FG_YELLOW"===============================================================================================================================\n\n"NOCOLOR);
}

/**
 * fonction qui libere le contenu alloué 
 */
 
void Freetrace(ListFlux lf,Event e, ListPaquet lp, ListNoeud ln, Option opt)
{
        Free_Flux(lf);
        Free_Event(e);
        Free_Paquet(lp);
        Free_Noeud(ln);
        free(opt);
}

/**
 * Fonction qui lit un fichier et renvoi des données en fonction de besoin
 */

int Readtrace(FILE *fd,ListNoeud ln,ListFlux lf,ListPaquet lp,Event e, int *lu, Option opt)
{
        int dev;

        Trace t1 = NULL;
        t1 = (Trace) malloc(sizeof(_trace));
        t1->code = -1;

        *lu = fscanf(fd, "%f %d",&t1->t,&t1->code);
        if ( t1->code != 4)
                *lu = fscanf(fd, "%d %d %d %d %s %s %s\n",&t1->pid,&t1->fid,&dev,&dev,t1->s,t1->d,t1->pos );
        else
                *lu = fscanf(fd, "%d %d %d %s %s %s\n",&t1->pid,&t1->fid,&dev,t1->s,t1->d,t1->pos );
                
        if ( *lu != EOF)
        {
               Add_Noeud(ln,e,t1,opt);
               Add_Flux(lf,e,t1,opt);
               Add_Event(e,t1,opt);
               Add_Paquet(lp,ln,lf,e,t1,opt);
        }

        free(t1);

        return 0;
}
