

/*
 * graphe.c
 *
 *  Created on: 15 nov. 2017
 *      Author: guibadj
 */


#include "graphe.h"

/* initailiser un graphe qui va contenir nS sommets */
Graphe* creerGraphe(int nS)
{

    Graphe* graphe=malloc(sizeof(Graphe));
    graphe->noeuds=NULL;
    graphe->nS=nS;
    graphe->cout = malloc(sizeof(int*)*nS);
    int i;
    for(i=0; i<nS; i++)
        graphe->cout[i] = malloc(sizeof(int)*nS);;
    return graphe;

}

/* ajouter un sommet au graphe (insertion en fin de liste)*/
void ajoutSommet(Graphe * g,char libelle)
{

    /*************** allocattion mémoire *********************/
    Sommet * sommet = malloc(sizeof( Sommet));
    sommet->id=libelle-'a';
    sommet->libelle=libelle;
    sommet->couleur=0;
    sommet->arcs=NULL;
    sommet->suivant=NULL;

    /************ placement de sommet dans la bonne position************/

    Sommet * liste = g->noeuds;

    if(liste==NULL)
        g->noeuds  = sommet;
    else
    {
        while(liste->suivant)
            liste=liste->suivant;
        liste->suivant = sommet;
    }
}


/* cherche et retourne le pointeur vers le sommet libelle (libelle dans l'ensemble {'a', 'b','c','d','e' ....}*/
Sommet * chercheSommet(Graphe * g,char libelle)
{

    Sommet * liste = g->noeuds;
    while(liste!=NULL)
    {
        if(liste->libelle == libelle)
            return liste;
        liste = liste->suivant;
    }
    return liste;
}

/* ajoute l'arc (libelle1, libelle2) au graphe . Le cout de l'arc est passé en paramètre. Le sommet libelle2 est inséré en fin de la liste successeur de libelle1*/
void ajoutArc(Graphe * g,char libelle1,char libelle2,int cout)
{

    Sommet * s1= chercheSommet(g,libelle1);
    Sommet * s2= chercheSommet(g,libelle2);

    if(s1==NULL || s2==NULL)
    {
        return;
    }

    Arc * arc= malloc(sizeof(Arc));
    arc->noeud=s2;
    arc->suivant=NULL;

    Arc * liste = s1->arcs;

    if(liste==NULL)
        s1->arcs = arc;
    else
    {
        while(liste->suivant)
            liste=liste->suivant;
        liste->suivant=arc;
    }

    g->cout[s1->id][s2->id]= cout;
}

/* ajouter une arete au graphe . L'arete (a,b) correspond à deux arc a-> b et b->a*/
void ajoutArete(Graphe * g,char libelle1,char  libelle2,int cout)
{

    ajoutArc(g,libelle1,libelle2,cout);
    ajoutArc(g,libelle1,libelle2,cout);
}

/******************************************************************************************************/

/* afficher la structure de graphe*/
void afficherGraphe (Graphe* g)
{
    if(g->noeuds)
    {

        printf("\n les sommets du graphe :\n\n");
        Sommet *MyGraph =g->noeuds;
        while(MyGraph!=NULL)
        {
            printf("%c__",MyGraph->libelle);
            MyGraph=MyGraph->suivant;
        }
        printf("\n \n ");
        printf("\n liste d'adjacences :\n");

        Sommet * summit =g->noeuds;
        while(summit!=NULL)
        {
            printf("\n\n\t sommet _%c_ :",summit->libelle);
            Arc * arc = summit->arcs;

            while (arc!=NULL)
            {
                printf("==> %c ", arc->noeud->libelle);
                arc=arc->suivant;
                              //  arc=arc->suivant;


            }

            summit=summit->suivant;
        }
                printf("\n \n ");


    }
    else
        printf("Graphe vide");


}
/****************************************************************************************************/
/* parcourir le graphe en largeur avec une file  à partir du sommet libelle*/
void parcoursLargeur(Graphe * g, char libelle)
{
   /* initialisation*/
      Arc *arc_Largeur;
     Sommet *sommet_Largeur;
     File *liste;


    if (g == NULL)
    {
        printf("le graphe est vide????");
        return;
    }

    liste = creerFile();//liste où on va mettre les sommets non colorré afin d'acceder à ses successeurs facilement
    sommet_Largeur = chercheSommet(g, libelle);
    enfiler(liste, sommet_Largeur);
    sommet_Largeur->couleur = 1;

    while (fileVide(liste) != 1)
    {
        sommet_Largeur = defiler(liste);
        arc_Largeur = sommet_Largeur->arcs;

    /**** enfiler les successeurs ****/

        while (arc_Largeur != NULL)
        {
            if (arc_Largeur->noeud->couleur == 0)//sommet pas encore selectionner
            {
                enfiler(liste, arc_Largeur->noeud);
                arc_Largeur->noeud->couleur = 1; //sommet selectionner mais pas encore traité
            }
            arc_Largeur = arc_Largeur->suivant;
        }
        sommet_Largeur->couleur = 2; // sommet traité
        printf(" Sommet %c - ", sommet_Largeur->libelle);
        sommet_Largeur = sommet_Largeur->suivant;
    }
   printf("\n");
    // libération des espaces occupées  par le file
    free(liste->tete);
    free(liste->queue);


}

/********************************************************************************************************/

/* parcourir le graphe en largeur avec une file à partir du sommet libelle */
void parcoursProfondeur(Graphe * g, char libelle)
{


    //  initialisation

    int i;
    int * P = malloc(sizeof(Sommet *) *g->nS );
    Sommet * s = g->noeuds;

    for(i=0; i<g->nS ; i++)
    {
        //initialisation
        P[i] = -1;
        s->couleur=0;
        s = s->suivant;
    }
    Sommet * s0 = chercheSommet(g,libelle);

    Pile * pile = NULL;
    pile = empiler(pile,s0);
    s0->couleur=1;

    Sommet * sk =NULL;
    while(pile!=NULL)
    {
        sk = pile->sommet;

        Arc *sucesseurs= sk->arcs;
        while(sucesseurs && sucesseurs->noeud->couleur!=0 )
            sucesseurs=sucesseurs->suivant;

        if(sucesseurs)
        {

            Sommet * si = sucesseurs->noeud;
            pile = empiler(pile, si);
            si->couleur=1;
            P[si->id] = sk->id;

        }
        else
        {
            pile =depiler(pile);
            sk->couleur = 2;
            printf(" Sommet %c -", sk->libelle);
        }

    }

}

/********************************************************************************************************/

// retourner le sommet gris S  el que d[S] soit minimal
Sommet * sommetMin(Graphe * g,int d[])
{
    Sommet * s = NULL;
    Sommet * liste = g->noeuds;
    int min = Max;

    while(liste)
    {
        if(d[liste->id]<min && liste->couleur==1)
        {
            min = d[liste->id];
            s = liste;
        }
        liste= liste->suivant;
    }

    return s;


}
/********************************************************************************************************/


/* algorithme de dijkstra*/
void dijkstra(Graphe * g, char libelle, int d[], int pi[])
{
 int i;
    Sommet *S=g->noeuds;
    for(i=0;i<g->nS;i++)
    {
        d[S->id]=Max;
        pi[S->id]=0;
        S->couleur=0;
        S=S->suivant;
    }
    Sommet *SOM=chercheSommet(g,libelle);
    d[SOM->id]=0;
    SOM->couleur=1;
    while(Verifier_sommet_gris(g))
    {
        Sommet *min=sommetMin(g,d);
        Arc *A=min->arcs;
        while(A)
        {
            if(A->noeud->couleur!=2)
            {
                condition_dijks(g,min,A->noeud,d,pi);
                if(A->noeud->couleur==0)
                    A->noeud->couleur=1;
            }
            A=A->suivant;
        }
        min->couleur=2;
    }



}

/********************************************************************************************************/


/* algorithme de Bellman*/
void bellman(Graphe * g, char libelle, int d[], int pi[])
{



}






/*
 * fonctions de manipulation de file
 */


File * creerFile()
{
    File * f = malloc(sizeof(File));
    f->tete = NULL;
    f->queue = NULL;
    return f;
}

int fileVide(File * f)
{
    if(f->tete==NULL  && f->queue ==NULL)
        return 1;
    else
        return 0;
}
void enfiler(File * f, Sommet *s)
{

    ElementFile * e = malloc(sizeof(ElementFile));
    e->sommet = s;
    e->suivant = NULL;
    if (fileVide(f))
    {
        f->tete = e;
        f->queue = e;

    }
    else
    {
        f->queue->suivant = e;
        f->queue = e;
    }



}
Sommet * defiler(File * f)
{


    if (fileVide(f))
    {

        return NULL;
    }


    Sommet * s = f->tete->sommet;

    f->tete=f->tete->suivant;
    if(f->tete == NULL)
        f->queue =NULL;



    return s;


}


void afficherFile(File * f)
{


    ElementFile * p = f->tete;
    printf("\n");
    while (p!=NULL)
    {
        printf("(%c) --> ", p->sommet->id);
        fflush(stdout);
        p=p->suivant;
    }



}

/*
 * fonctions de manipulation de pile
 */


Pile *empiler(Pile* pile, Sommet * s)
{

    Pile * e = malloc(sizeof(Pile));
    e->sommet = s;
    e->suivant = NULL;

    if(pile==NULL)
    {
        pile = e;
        return pile;
    }

    e->suivant = pile;
    pile= e;
    return pile;

}

Pile *depiler(Pile * pile)
{

    if(pile != NULL)
    {

        pile = pile->suivant;


    }


    return pile;

}

void afficherPile(Pile *pile)
{
    Pile * p = pile;

    printf("\n");
    while(p!=NULL)
    {

        printf(" %c - ", p->sommet->id);
        p = p->suivant;
    }


}


void afficherDistance(int tab[], int n)
{

    int i=0;
char lettre='a';
    printf("\n");
    for(i=0; i<n; i++){
       printf(" \n\t le plus court chemin entre la source a et le sommet ");
        printf(" %c est : %d ",lettre, tab[i]);
        lettre+=1;
        printf("\n");

}
}
void afficher_Pere(int tab[], int n)
{

    int i=0;
char lettre='a';
    printf("\n");
    for(i=0; i<n; i++){

       printf("\n\t le pere de la sommet %c ett le sommet %d ",lettre,tab[i]);
        lettre+=1;
        printf("\n");
    }
    lettre='a';
    printf("\n intepretation : \n ");
    for(i=0; i<n; i++){
       printf("\n\t le sommet %d <=> sommet %c",i,lettre);
       lettre+=1;
                      }




}


//implimentations des fonctions tests
void testDjikstra()

{
	Graphe* graphe3 = creerGraphe(5);

	ajoutSommet(graphe3,'a');
	ajoutSommet(graphe3,'b');
	ajoutSommet(graphe3,'c');
	ajoutSommet(graphe3,'d');
	ajoutSommet(graphe3,'e');

	ajoutArc(graphe3,'a','b',3);
	ajoutArc(graphe3,'a','e',5);
	ajoutArc(graphe3,'b','e',1);
	ajoutArc(graphe3,'e','b',1);
	ajoutArc(graphe3,'b','c',6);
	ajoutArc(graphe3,'e','d',6);
	ajoutArc(graphe3,'e','c',3);
	ajoutArc(graphe3,'c','d',2);
	ajoutArc(graphe3,'d','c',7);
	ajoutArc(graphe3,'d','a',3);
	afficherGraphe(graphe3);

	int d[5];
	int pi [5] ;
    printf("\n test d'algorithme de dijkstra sur le graphe de figure 3 \n ");
	dijkstra(graphe3,'a',d,pi);
    printf("\n  affichage  de plus court chemin entre le sommet a et les autres sommets du graphe figure 3 \n ");
	afficherDistance(d,5);
    printf("\n  affichage  des peres de plus court chemin \n ");
	afficher_Pere(pi,5);
	printf("\n\ncliquer sur entrer pour revenir au menu principal");
	 getch();
	 system("cls");
	 menu();
}

void testParcoursLargeur()
{


	 Graphe* graphe1 = creerGraphe(9);
	 ajoutSommet(graphe1,'a');
	 ajoutSommet(graphe1,'b');
	 ajoutSommet(graphe1,'c');
	 ajoutSommet(graphe1,'d');
	 ajoutSommet(graphe1,'e');
	 ajoutSommet(graphe1,'f');
	 ajoutSommet(graphe1,'g');
	 ajoutSommet(graphe1,'h');
	 ajoutSommet(graphe1,'i');

	 ajoutArete(graphe1,'a','b',0);
	 ajoutArete(graphe1,'a','g',0);
	 ajoutArete(graphe1,'b','c',0);
	 ajoutArete(graphe1,'b','e',0);
	 ajoutArete(graphe1,'b','g',0);
	 ajoutArete(graphe1,'g','h',0);
	 ajoutArete(graphe1,'c','d',0);
	 ajoutArete(graphe1,'c','f',0);
	 ajoutArete(graphe1,'e','f',0);
	 ajoutArete(graphe1,'e','h',0);
	 ajoutArete(graphe1,'f','i',0);
	 ajoutArete(graphe1,'h','i',0);

	 afficherGraphe(graphe1);
	 printf("\n parcours  largeur du graphe figure 1 \n\n ");
	 parcoursLargeur(graphe1,'a');
	 printf("\n\ncliquer sur entrer pour revenir au menu principal");
	 getch();
	 system("cls");
	 menu();
}


void testParcoursProfondeur()
{
	 Graphe* graphe2 = creerGraphe(8);

	 ajoutSommet(graphe2,'a');
	 ajoutSommet(graphe2,'b');
	 ajoutSommet(graphe2,'c');
	 ajoutSommet(graphe2,'d');
	 ajoutSommet(graphe2,'e');
	 ajoutSommet(graphe2,'f');
	 ajoutSommet(graphe2,'g');
	 ajoutSommet(graphe2,'h');

	 ajoutArc(graphe2,'a','b',0);
	 ajoutArc(graphe2,'a','g',0);
	 ajoutArc(graphe2,'b','c',0);
	 ajoutArc(graphe2,'b','e',0);
	 ajoutArc(graphe2,'b','f',0);
	 ajoutArc(graphe2,'c','d',0);
	 ajoutArc(graphe2,'c','e',0);
	 ajoutArc(graphe2,'d','c',0);
	 ajoutArc(graphe2,'e','d',0);
	 ajoutArc(graphe2,'e','h',0);
	 ajoutArc(graphe2,'e','b',0);
	 ajoutArc(graphe2,'f','h',0);
	 ajoutArc(graphe2,'f','a',0);
	 ajoutArc(graphe2,'g','f',0);

	 afficherGraphe(graphe2);
     printf("\n parcours  profondeur du graphe figure 2 \n\n ");
	 parcoursProfondeur(graphe2,'a');
	 printf("\n\ncliquer sur entrer pour revenir au menu principal");
	 getch();
	 system("cls");
	 menu();

}

int Verifier_sommet_gris(Graphe *g)
{
    Sommet *parcour=g->noeuds;
    while(parcour)
    {
        if(parcour->couleur==1)
            return 1;
        parcour=parcour->suivant;
    }
    return 0;
}

void condition_dijks(Graphe *g,Sommet *summit1,Sommet *summit2,int d[],int pi[])
{
    if( d[summit2->id] > d[summit1->id] + g->cout[summit1->id][summit2->id] )
    {
        d[summit2->id] = d[summit1->id] + g->cout[summit1->id][summit2->id];
        pi[summit2->id]=summit1->id;
    }
}

Sommet* verif_Pile(Pile *pile)
{
    if(pile->sommet!=NULL)
        return pile->sommet;
    return NULL;
}

int pileVide(Pile *p)
{
    if(p==NULL)
        return 1;
    return 0;
}



void menu(){

     int choix;
printf("\n\n");
     printf("\t\t\t ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^\n");
     printf("\t\t\t ^   Devoir Maison d'Algorithmique avancee   ^\n");
     printf("\t\t\t ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^\n");



    printf("\n\n\n");

    printf("\n\t\t***************************************************************\n");
    printf("\n\t\t*                      1) parcours largeur.                   *\n");
    printf("\n\t\t*                      2) parcours profondeur.                *\n");
    printf("\n\t\t*                      3) algorithme de dijkstra.             *\n");
    printf("\n\t\t***************************************************************\n");


printf(" Entrez votre choix : ");
scanf("%d",&choix);
  while(choix<=0 || choix>3){
    printf("\nchoix invalide\n");
    printf(" Entrez autre choix : ");
    scanf("%d",&choix);
    }


     switch(choix)//selon le choix de l'utilisateur
    {
    case 1:
        testParcoursLargeur();

        break;

    case 2:
       testParcoursProfondeur();
        break;

    case 3:
        testDjikstra();
        break;



    default:
      printf("\n choix invalide!!!!!");
        break;
    }


}












