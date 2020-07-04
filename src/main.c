#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <math.h>
#include "Affichage.h"
#include "color.h"

/**
 * file main.c
 * contient la fonction principale du programme
 */





/** Affiche la syntaxe du programme
 * 
 * fonctions pour regrouper les messages à un seul endroit.
 * @param prog nom du programme
 * 
 */

void usage (const char *prog)
{
    fprintf (stderr, "usage: %s <file_trace> <matrice_adjacence> -p [ <pid> | all ] -f [ <fid> | all ] [ -t ] [ -l ] [ -a ]\n" 
    			"\t-p   : evolution de nombre de paquet dans la file au cours de temps et pour avoir la courbe de la file d_attente\n"
    			"\t-f   : délai de bout en bout pour l'ensemble des paquets du flux au cours du temps et pour avoir la courbe de delai bout en bout\n"
    			"\t-l   : pour l_affichage de la courbe de paquets perdus au cours du temps\n"
    			"\t-t   : pour l_affichage de la courbe de paquets en transit au cours du temps\n"
    			"\t-a   : pour l_affichage de la courbe de flux actif au cours du temps\n"
    		, prog) ; /* on affichera ceci l'orsque qu'une erreur dans les arguments surviennent */
}


int main (int argc, char *argv[])
{

        FILE *file;
        int c;
        double progression=0;
        extern char * optarg;
        int shift=0;
        char * prog = argv[0];
        int noflg = 0;
        char c1[1]="";
        char chaine[10];
        int num=0;
        int retour=0;
        int nb=0;
        int i=0;
        


        if ( argc < 3  )
        {
                usage(argv[0]);
                exit(1);
        }


        Event e = New_Event();

        ListNoeud ln = NULL;
        ln  = (ListNoeud) malloc(sizeof(_listNoeud));
        ln->First=NULL;

        ListFlux lf = NULL;
        lf = (ListFlux) malloc(sizeof(_listeFlux));
        lf->First=NULL;

        ListPaquet lp = NULL;
        lp = (ListPaquet) malloc(sizeof(_listPaquet));
        lp->First=NULL;

        Option option = NULL;
        option = (Option) malloc(sizeof(_option));
        strcpy(option->noeud,"vide");
        option->flux_actif = 0;
        option->flux_delai =-1;
        option->transit=0;
        option->perdus=0;



        // verification d'arguements

        while ((c = getopt(argc, argv, "p:f:tla")) != -1)
                switch (c) {
                case 'p':                 
                        shift+=2;
                        strcpy(option->noeud,optarg);
                        option->file_attente = fopen("plot_File/file_attente.tr", "w");
                        ajustement = 0;
                        break;
                 case 'f':
                        shift+=2;
                        option->flux_delai=atoi(optarg);
                        option->file_flux_delai = fopen("plot_File/delai_flux.tr", "w");
                        ajustement1=0;
                        break;
                case 't':
                        shift++;
                        option->transit++;
                        option->file_transit = fopen("plot_File/transit.tr", "w");
                        ajustement2=0;
                        break;
                case 'l':
                        shift++;
                        option->perdus++;
                        option->file_perdus = fopen("plot_File/perdu.tr", "w");
                        break;
                case 'a':
                        shift++;
                        option->flux_actif++;
                        option->file_flux_actif = fopen("plot_File/flux_actif.tr", "w");
                        ajustement4=0;
                        break;
              
                case '?':
                        noflg++;
                        break;
                }

        if (noflg || argc != (shift+3))
        {
                usage(prog);
                Freetrace(lf,e,lp,ln,option);
                return -1;
        }
		//ouverture de fichier
        file = fopen(argv[1+shift], "r");

        if (!file)
        {
                perror("fopen");
                Freetrace(lf,e,lp,ln,option);
                exit(1);
        }

        int nl = 0;
        char car;
			//on saute les newLine
        for (car = getc(file); car != EOF; car = getc(file))
                if (car == '\n')
                        nl++;

        fclose(file);



        file = fopen(argv[1+shift], "r");

        if (!file)
        {
                perror("fopen");
                Freetrace(lf,e,lp,ln,option);
                exit(3);
        }


        printf("\n");
        printf("Simulation en cours...\n");
        do {
                Readtrace(file,ln,lf,lp,e,&nb,option);
              i++;
              progression = (double)i/(double)nl*100;                           
              printf("\r######################### Chargement: %.2f%s ############################",progression,"%");
              fflush(stdout);
                
        } while ( nb != EOF );
      

        printf("\n");

        Affichage_Event(e);
        Affichage_Noeud(ln->First,e);

			
	// analyser la simulation par evenement	
        while ( strcmp(c1,"4") != 0 )
        {

                printf(FG_BLUE" ################### Menu de Simulation ################### : \n"NOCOLOR);
                printf(" 1. 	Analyser un paquet <tapez 1>\n");
                printf(" 2. 	Analyser un flux <tapez 2>\n");
                printf(" 3. 	Analyser un noeud <tapez 3>\n");
                printf(" 4. 	Quitter la simulation <tapez 4>\n");
                printf("Saisissez votre choix : ");
                retour = scanf ("%1s", c1);
                retour = scanf ("%*[^\n]");
                getchar ();


                if ( strcmp(c1,"1") == 0 )
                {
                        printf(" Saisissez le numéro du paquet à analyser <pid> : ");
                        retour = scanf ("%d", &num);
                        retour = scanf ("%*[^\n]");
                        getchar ();

                        Affichage_Paquet(lp->First,num);
                        num=0;

                }
                else if ( strcmp(c1,"2") == 0 )
                {
                        printf(" Saisissezle numéro du flux à analyser <fid> : ");
                        retour = scanf ("%d", &num);
                        retour = scanf ("%*[^\n]");
                        getchar ();


                        Affichage_Flux(lf->First,num);
                        num=0;

                }
                else if ( strcmp(c1,"3") == 0 )
                {
                        printf(" Saisissez le nom du noeud à analyser <nom> : ");
                        retour = scanf ("%10s", chaine);
                        retour = scanf ("%*[^\n]");
                        if ( retour != 0)
                            getchar ();
                        Affichage_Event_Noeud(ln->First,e,chaine);

                }


        }
        

          // liberer la memoire      
        Freetrace(lf,e,lp,ln,option);
        fclose(file);

        return 0;
}
