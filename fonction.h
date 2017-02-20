#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_NAME 25

// Definition des types "post" et "Personne"
// Personne
typedef struct {
  char id[20]; // D'après le fichier, chaine de 20 caractères maximum.
  char name[MAX_NAME]; // 25 -> saisie arbitraire.
} Personne;

// Post
typedef struct Post{
  char id[40]; // D'apres les fichiers yaml, les post sont identifiés dans une chaine comme supérieur à 30 caractères mais inférieur à 40.
  char creation[30]; // basé sur les meme criteres. 25 char
  char message[250]; // Messages/description de 200 caractères maximum. (202 avec guillemets)
  Personne aime[200]; // Jamais plus de 200 j'aime par post dans aucune des 2 listes.
  int dernier;
} Post;
// Il existe aussi d'autres critères sur le fichier Yaml mais dont nous n'avons pas l'utilité d'après notre cahier des charges.

// Liste chainee
typedef struct CellPost{
  Post postl; 
  struct CellPost* suivant;
} CellPost;

// Et donc le type ListeBDE en tant que liste chainee.
typedef CellPost* ListeBDE;

// Retourne la position soit de la personne recherché, soit de l'endroit ou insérer une personne.
// b étant le dernier indice du tableau de personne.
int dicho(char* id_rech, Personne P[], int b);

// Fonction de décalage pour trier les listes de personnes.
void decalage(Personne aime[], int pos, int dernier);

//Fonction ajout en tete pour les listes chainées
void ajout_tete (ListeBDE* l,Post post);

// fonction de chargement d'un fichier yaml en une listeBDE.
// Elle prend en paramètre, un pointeur de fichier et le pointeur de liste à modifier.
void charg_print(FILE * fp, ListeBDE* l);

// Imprime un post
void print_post(Post post);

// Imprime une liste
void print_liste(ListeBDE l);

void compte(ListeBDE* l, int * nbpost, int * nblike);

void post_like(ListeBDE* l, char* user, int tabpost[],int * fin);

// Fonctions pour supprimer une Liste et libérer la mémoire.
void suppr_tete(ListeBDE* l);

ListeBDE suppr_liste(ListeBDE l);

// Fonction 3 qui liste les personnes ayant aimé au moins 1 post dans la liste l.
// Prend une liste de personne vide et la remplie des personnes ayant aimé au moins une fois 
// la liste passé en paramètre. Elle renvoie aussi la longueur du tableau nouvellement rempli.
int like_1post(ListeBDE l, Personne stock[]);

// Fonction 4 qui liste les personnes ayant aimé dans les 2 listes.
// Cette fonction prend en argument les tableaux des personnes ayant aimé au moins un post dans 2 listes 
// et imprime directement les personnes ayant liké dans les 2 listes.
void liste_truant(Personne stock1[], int dern1, Personne stock2[], int dern2);
