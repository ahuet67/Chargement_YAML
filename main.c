#include <stdio.h>
#include "fonction.h"

int main()
{
  int choixf=-1; // Booléan du choix de la fonction à executer.
  int choixl=0; // Booléan du choix de la liste à traiter
  ListeBDE lraz = NULL;
  FILE* fpraz;
  ListeBDE lea = NULL;
  FILE* fpea;

  int nbpost,nblike;

  // Utile pour les fonctions 4 et 5.
  int dernsraz;
  Personne stockraz[600];
  int dernsea;
  Personne stockea[600];


// Importer les listes.
  fpraz=fopen("2016_razmotech.yaml","r");
  charg_print(fpraz,&lraz);
  fclose(fpraz);

  fpea=fopen("2016_poly_eagles.yaml","r");
  charg_print(fpea,&lea);
  fclose(fpea);
  
  

  while(choixf!=0)
  {
    printf("------------   BIENVENUE DANS LE MENU DE L'APPLICATION --------------\n\n\n");
    printf("Tapez 1 : Si vous voulez lister une liste entierement.\n");
    printf("Tapez 2 : Si vous voulez compter le nombre de post d'une liste et le nombre total de likes obtenus.\n");
    printf("Tapez 3 : Si vous voulez connaitre les posts like par un utilisateur.\n");
    printf("Tapez 4 : Si vous voulez compter et lister les utilisateurs qui ont like au moins un post dans la liste de votre choix.\n");
    printf("Tapez 5 : Si vous voulez lister les utilisateurs qui ont like des posts dans les deux listes.\n");
    printf("Tapez 6 : Si vous voulez avoir le bilan de succès des 2 listes.\n");
    printf("Tapez 0 : Si vous voulez sortir de l'application.\n");
    scanf("%d",&choixf);

    // guide pour le choix de la liste à traiter.
    switch (choixf)
    {
      case 1:
      case 2:
      case 4:
        printf("Veuillez choisir la liste que vous voulez traiter.\n"); 
        printf("tapez 1 pour razmotech et 2 pour poly eagles.\n\n");
        scanf("%d",&choixl);
        break;

      case 0:
        printf("Au revoir!\n");
        break;

      case 3:
      case 5:
      case 6:
        break;

      default:
        printf("Vous n'avez pas rentré un nombre correct. Veuillez réessayer.\n\n");
    }

    // Application des fonctions selon les choix de l'utilisateur.
    switch (choixf) 
    {
        case 1:
          if (choixl==1) {print_liste(lraz);}
          if (choixl==2) {print_liste(lea);}
          break;

        case 2:
          if (choixl==1) 
            {
              compte(&lraz,&nbpost,&nblike);
              printf("Dans la liste razmotech, il y a %d post et %d like. \n\n",nbpost,nblike);
            }
          if (choixl==2) 
            {
              compte(&lea,&nbpost,&nblike);
              printf("Dans la liste poly'eagles, il y a %d post et %d like. \n\n",nbpost,nblike);
            }
          break;

        case 3:
            printf("Veuillez rentrer l'id de l'utilisateur a espionner. (Veuillez mettre des guillemets)\n");
            int tabpost[60],i,fin; //60 le maximum
            char idpers[20];
            scanf("%s",idpers);                      
            
            post_like(&lraz,idpers,tabpost,&fin);
            
            printf("l'utilisateur a aime les post : ");
            for (i=0;i<=fin;i++)
              {      
                printf("%d, ",tabpost[i]);
              }
            printf("de la liste rose les razmotech.\n Et l'utilisateur a aime les post : ");
            post_like(&lea,idpers,tabpost,&fin);
            for (i=0;i<=fin;i++)
              {      
                printf("%d, ",tabpost[i]);
              }
            printf("de la liste bleu les poly eagles.\n\n");
          break;

        case 4:

              if (choixl==1)
                  {
                    printf("\n\t\t Les utilisateurs ci-dessous ont liké au moins 1 post dans la liste razmotech. \n\n");
                    dernsraz=like_1post(lraz,stockraz);
                  }

              if (choixl==2)
                  {
                    printf("\n\t\t Les utilisateurs ci-dessous ont liké au moins 1 post dans la liste poly'eagles. \n\n");
                    dernsea=like_1post(lea,stockea);
                  }
          break;


          case 5:
            printf("\n\t\t Les utilisateurs ci-dessous ont liké au moins 1 post dans la liste razmotech. \n\n");
            dernsraz=like_1post(lraz,stockraz);
            printf("\n\t\t Les utilisateurs ci-dessous ont liké au moins 1 post dans la liste poly'eagles. \n\n");
            dernsea=like_1post(lea,stockea);
            liste_truant(stockraz,dernsraz,stockea,dernsea);   
          break;

          case 6:
            compte(&lraz,&nbpost,&nblike);            
            dernsraz=like_1post(lraz,stockraz);
            dernsea=like_1post(lea,stockea);
            printf("La liste razmotech a posté %d posts et a reçu %d likes ce qui fait une moyenne de %d likes par post.\n De plus, %d personnes ont liké au moins 1 post dans la liste.\n\n",nbpost,nblike,nblike/nbpost,dernsraz+1);        
            compte(&lea,&nbpost,&nblike);
            printf("La liste Poly'eagles a posté %d posts et a reçu %d likes ce qui fait une moyenne de %d likes par post.\n De plus, %d personnes ont liké au moins 1 post dans la liste.\n\n",nbpost,nblike,nblike/nbpost,dernsea+1);        
            printf("On peut donc remarquer que la liste razmotech a eu un meilleur succès sur facebook, avec moins de post pour un meilleur résultat (en like). C'est pourtant poly'eagles qui a été choisi.\n\n\n");
          break;
        
    }

  }    

  lraz=suppr_liste(lraz);  
  lea=suppr_liste(lea);
  return 0;
}
