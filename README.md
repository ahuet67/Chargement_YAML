Etude et comparaison de 2 groupes facebook (Liste BDE Poly'eagles et Razmotech)
===============================================================================

>contributeurs:<br>
>Alexandre Huet<br>


>IMA3 Polytech Lille<br>

Sommaire:
---------

0) Introduction


1) Compilation<br>


2) Execution<br>


3) Utilisation<br>


0) Introduction
---------------

  L'objectif de ce projet est de charger 2 fichiers en format YAML dans une structure de donnée choisi par nos soins
et de les utiliser pour traiter des requêtes que pourra exiger l'utilisateur.
Nous pouvons ainsi compter le nombre de post Facebook de chaque liste, le nombre total de likes obtenus. Nous renvoyons les posts likés par une personne choisi par l'utilisateur. Nous avons aussi la possibilitée de lister et de compter les personnes qui ont liké au moins 1 post dans une liste ou ceux qui ont liké des posts dans les 2 listes.
  Pour finir, nous avons la possibilité d'effectuer un bilan des stats de chaque liste et en déduire laquelle des 2 listes a été le mieux apprécié sur les réseaux sociaux.



1) Compilation
---------------

Pour compiler le programme, veuillez taper "make DEBUG=no" dans le répertoire projet.

Pour tester les fuites mémoires avec valgrind, détailler l’exécution avec gdb ou ddd, veuillez taper "make DEBUG=yes".

2) Exécution
----------------

Pour exécuter le programme, tapez "./exec" dans le terminal.

3) Utilisation
----------------

Une fois le fichier exécuter, laissez vous guider par le menu en fonction de ce que vous désirez faire.
