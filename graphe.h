


#include <stdio.h>
#define Max 9999999



#ifndef GRAPHE_H_
#define GRAPHE_H_


typedef struct sommet Sommet;
typedef struct arc Arc;


/* structure de graphe*/

struct sommet {

	int id ;
	char libelle;
	int couleur;
	Arc *arcs;
	struct sommet  *suivant;


};

struct arc {

	struct sommet  *noeud;
	struct arc *suivant;

          } ;

typedef struct graphe{

	Sommet *noeuds;
	int ** cout;
	int nS;

}Graphe;



/* structure de pile*/
struct pile
{
    Sommet * sommet;
    struct pile * suivant;
};
typedef struct pile Pile;

Pile *empiler(Pile* p, Sommet * s);
Pile *depiler(Pile * pile);
void afficherPile(Pile *pile);

/* structure de file*/
typedef struct ElementFile
{
   Sommet * sommet;
	struct ElementFile * suivant;
}ElementFile;

typedef struct file
{

	ElementFile * tete;
	ElementFile * queue;
}File;


File * creerFile();
void enfiler(File * f, Sommet *  s);
Sommet * defiler(File * f);
int fileVide(File * f);
void afficherFile(File * f);


/* structure de graphes */
Graphe* creerGraphe();
void ajoutSommet(Graphe * g, char libelle);
void ajoutArc(Graphe * g,char libelle1,char libelle2,int cout);
void ajoutArete(Graphe * g,char libelle1,char libelle2,int cout);
void parcoursProfondeur(Graphe *g, char libelle);
void parcoursLargeur(Graphe * g , char libelle);
Sommet * sommetMin(Graphe * g ,int d[]);
void dijkstra(Graphe * g , char libelle , int d[] , int pi[]);
void bellman(Graphe * g , char libelle , int d[] , int pi[]);
void afficherGraphe (Graphe* g);
void afficherDistance(int tab[], int n);
void afficher_Pere(int tab[], int n);



// fonctions de test main
void testParcoursLargeur();
void testParcoursProfondeur();
void testDjikstra();
//dijkstra fonctions
Sommet* verif_Pile(Pile *pile);
int pileVide(Pile *p);
void condition_dijks(Graphe *g,Sommet *summit1,Sommet *summit2,int d[],int pi[]);
int Verifier_sommet_gris(Graphe *g);







#endif /* GRAPHE_H_ */

