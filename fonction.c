#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_NAME 25

// Definition des types "post" et "Personne"
// Personne
typedef struct {
  char id[30]; // D'après le fichier, chaine de 20 caractères maximum.
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


// fonction de recherche dichotomique pour la recherche et l'ajout
// Retourne la position soit de la personne recherché, soit de l'endroit ou insérer une personne.
int dicho(char* id_rech, Personne P[], int b)
{
  int a=0;
  int m=(a+b)/2;
  while (a<b)
    {
      if (strcmp(id_rech,P[m].id)==0) {return m;}
      if (strcmp(id_rech,P[m].id)<0) {b=m-1;}
      if (strcmp(id_rech,P[m].id)>0) {a=m+1;}
      m=(a+b)/2;
    }
  return m;
}

// Fonction de décalage pour trier les listes de personnes.
void decalage(Personne aime[], int pos, int dernier)
{
  int i;
  for (i=dernier;i>=pos;i--)
    {
      aime[i+1]=aime[i];
    }
}

//Fonction ajout en tete pour les listes chainées
void ajout_tete (ListeBDE* l,Post post)
{
  CellPost* p;
  p=malloc(sizeof(CellPost));
  p->postl=post;
  p->suivant=(*l);
  (*l)=p;
}

//Fonction pour créer un nouveau post en mémoire utile pour la fonction charg_print
Post* newpost()
{
  Post* pt_newpost;
  pt_newpost=malloc(sizeof(CellPost));
  pt_newpost->dernier=-1;
  return pt_newpost;
}

// fonction de chargement d'un fichier yaml en une listeBDE.
// Elle prend en paramètre, un pointeur de fichier et le pointeur de liste à modifier.
// d'apres les test, l'id des post est toujours supérieur à 30 caractères
// L'id des personnes toujours inférieur ou egal à 19 caractères
// Ici nous n'avons pas retiré les guillemets aux chaines de caractères.
void charg_print(FILE * fp, ListeBDE* l)
{
  char s[130];
  s[0]='\0';
  char* sprec=malloc(sizeof (*sprec) * 130);
  *sprec='\0';
  int longch=0,cpt;
  int bo=1; // Booléan a 0 si un post n'a pas été encore été ajouté. (Le cas ou un post n'a été aimé par personne.)
  int bod=1; // Booléan a 1 si on est au tout debut de la procedure
  Post* pt_newpost = NULL;
  

  while (!feof(fp))
    { 
      if (bo==0||bod==1) // si on a un nouvel id en memmoire ou si on est au debut de la procedure.
	{
	  fscanf(fp,"%s",s);
	  longch=strlen(s);
	}
      
      // Ajout d'un nouveau post et d'un nouvel id
      if ((longch>25) && strcmp(sprec,"id:")==0) 
        { 
	  if (bo==0) {ajout_tete(l,*pt_newpost);free(pt_newpost);}
	  pt_newpost=newpost();
          strcpy(pt_newpost->id,s);
	  bo=0;
	  bod=0;
        } 
      
      // Ajout de la date de creation du post
      if (strcmp(sprec,"created_time:")==0) {strcpy(pt_newpost->creation,s);}
      
      // Ajout du message
      if (strcmp(sprec,"messsage:")==0||strcmp(sprec,"description:")==0) 
	{strcpy(pt_newpost->message,s);
	  strcat(pt_newpost->message," ");    
	  while ((s[longch-1]!='"')&&!feof(fp)) //tant qu'on est pas à la fin du message en espèrant qu'aucun poste ne comporte un mot suivis d'un '"'.
	    {
	      fscanf(fp,"%s",s);
	      longch=strlen(s);
	      strcat(pt_newpost->message,s); // Concaténation du nouveau mot au message.
	      strcat(pt_newpost->message," ");        
	    }     
	}
      
      // La c'est ajout dans la liste contigue en triant.      
      if (longch<20 && strcmp(sprec,"likes:")==0) 
	{
	  cpt=0;
	  int pos=0;
	  while (!feof(fp)&&longch<25)
	    {
	      strcpy(sprec,s);
	      fscanf(fp,"%s",s);
	      longch=strlen(s);
	      if ((strcmp(sprec,"id:")==0)&&(longch<25)) 
		{
		  pt_newpost->dernier=cpt;
		  pos=dicho(s, pt_newpost->aime, pt_newpost->dernier);
		  decalage(pt_newpost->aime, pos, pt_newpost->dernier);
		  strcpy(pt_newpost->aime[pos].id, s); 
		}
	      if (strcmp(sprec,"name:")==0) 
		{
		  strcpy(pt_newpost->aime[pos].name,s);
		  cpt=cpt+1;
		}
	    }
	  ajout_tete(l,*pt_newpost);
	  free(pt_newpost);
	  bo=1;
	}
      // Attention au cas ou sprec et s contiennent les infos du prochain id.
      if (bo==0||bod==1) {sprec=strcpy(sprec,s);} 
    }
  free(sprec);
}

void compte(ListeBDE* l, int * nbpost, int * nblike)
{
  CellPost* pt;
  pt=*l;
  *nbpost=0;
  *nblike=0;
  while (pt!=NULL)
    {
      *nbpost+=1;
      *nblike+=pt->postl.dernier + 1;
      pt=pt->suivant;
    }
}


//Fonction print_post
// Imprime un post.
void print_post(Post post)
{
  int i;
  printf("Id Post :\t\t %s \n",post.id);
  printf("Date du Post :\t\t %s \n",post.creation);
  printf("Message du Post :\n\n %s \n\n",post.message);
  printf("\t Liste des personnes ayant like le post.\n\n");
  for (i=0;i<=post.dernier;i++)
    {
      printf("Personne numero %d : %s\t\t id : %s \n",i,post.aime[i].name,post.aime[i].id);
    }
  printf("\n\n");
}


//Fonction print_liste
// Imprime une liste
void print_liste(ListeBDE l)
{
  int cpt=0;
  CellPost* pt_cell;
  pt_cell=l;
  while (pt_cell!=NULL)
    {
      cpt=cpt+1;
      printf("\t\t Post numero %d\n\n",cpt);
      print_post(pt_cell->postl);
      pt_cell=pt_cell->suivant;
    }

}

void post_like(ListeBDE* l, char* user, int tabpost[],int * fin)
{
  int pos;
  int cpt=1,ind=0;
  CellPost* pt;
  pt=*l;
  while (pt!=NULL)
    {
      pos=dicho(user,pt->postl.aime,pt->postl.dernier);
      if (strcmp(user,pt->postl.aime[pos].id)==0) // Si l'utilisateur a like le post
	{
	  tabpost[ind]=cpt; // Alors note le numero du post like
    print_post(pt->postl);
	  ind=ind+1;
	}
      pt=pt->suivant;
      cpt=cpt+1;
    }
  *fin=ind-1;
}

// Fonctions pour supprimer une Liste et libérer la mémoire.
void suppr_tete(ListeBDE* l)
{
  if ((*l)!=NULL)
    {
      CellPost * pt=(*l);
      (*l)=(*l)->suivant;
      free(pt);
    }
}

ListeBDE suppr_liste(ListeBDE l)
{
  CellPost * pt=l;
  while (pt!=NULL)
    {
      suppr_tete(&pt);
    }
  return pt;
}


// Fonction 3 qui liste les personnes ayant aimé au moins 1 post dans la liste l.
// Prend une liste de personne vide et la remplie des personnes ayant aimé au moins une fois 
// la liste passé en paramètre. Elle renvoie aussi la longueur du tableau nouvellement rempli.
int like_1post(ListeBDE l, Personne stock[])
{
  int i,j,dern=-1,bo;         
  while (l != NULL)                             
    {                                           
      for (i=0;i<=(l->postl.dernier);i++)
	{
	  j=0;
	  bo=0;
	  while (j<=dern && bo==0)          //recherche si l'utilisateur a déjà été stocké.
	    {
	      if (strcmp(l->postl.aime[i].id,stock[j].id)==0)
		      {
		        bo=1;
		      }
	      j++;
	    }
	  if(bo==0)              //On stock et on affiche les personnes qui n'ont pas encore été stocké.
	    {
	      dern++;
	      strcpy(stock[dern].id,l->postl.aime[i].id);
	      strcpy(stock[dern].name,l->postl.aime[i].name);
	      printf("Personne numero %d : %s\t\t id : %s \n",dern,stock[dern].name,stock[dern].id);
	    }
	}
      l=l->suivant;
    }
  printf("\n\t Il y a %d personnes qui ont aimé au moins 1 post dans cette liste BDE. \n\n",dern+1);
  return(dern);  
}

// Fonction 4 qui liste les personnes ayant aimé dans les 2 listes.
// Cette fonction prend en argument les tableaux des personnes ayant aimé au moins un post dans 2 listes 
// et imprime directement les personnes ayant liké dans les 2 listes.
void liste_truant(Personne stock1[], int dern1, Personne stock2[], int dern2)
{
  int i,j,bo=0,cpt=0;
  for (i=0;i<=dern1;i++)
    {
      j=0;
      bo=0;
      while (j<=dern2&&bo==0) 
	{
	  if (strcmp(stock1[i].id,stock2[j].id)==0) 
	    {
	      bo=1;
	      cpt=cpt+1;
	      printf("Personne numero %d : %s\t\t id : %s \n",cpt,stock1[i].name,stock1[i].id);
	    }
	  j=j+1;
	}      
    }

  printf("\n Il y a donc %d personnes qui ont aimé dans les 2 listes. \n\n",cpt);
}
