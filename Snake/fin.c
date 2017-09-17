#include <stdlib.h>
#include <graph.h>
#include <stdio.h>
#include <unistd.h>
#include <time.h>
#include "menu.h"
#include "snake.h"
#include "fin.h"

void affichageNiveauFin(struct Jeu* Jeu) {
  int niveau = Jeu->niveau + 1;
  if (niveau >= 10) {
    int dizaine = niveau / 10;
    int unite = niveau % 10;
    char entierTab[3] = {'0', '0', '\0'};
    entierTab[0] = '0' + dizaine;
    entierTab[1] = '0' + unite;
    EcrireTexte(255, 130, entierTab, 2);
  }
  else if (niveau < 10) {
    char entierTab[2] = {'0', '\0'};
    entierTab[0] = '0' + niveau;
    EcrireTexte(255, 130, entierTab, 2);
  }
}


void fin(char* score, struct Jeu* Jeu, struct Config* Config) {
  InitialiserGraphique();
  CreerFenetre(100, 100, 300, 350);

  ChoisirCouleurDessin(CouleurParNom("green"));
  EcrireTexte(80, 50, "Fin de partie", 2);
  
  ChoisirCouleurDessin(CouleurParNom("grey"));
  EcrireTexte(35, 130, "Vous avez perdu au niveau", 1);
  affichageNiveauFin(Jeu);

  EcrireTexte(85, 180, "Avec un score de", 1);
  EcrireTexte(105, 205, score, 2);

  EcrireTexte(40, 270, "Retourner au menu principal", 1);
  EcrireTexte(125, 300, "Quitter", 1);
 
  int fin = 0;

  while (!fin) {
    SourisCliquee();
    if ((_X) >= 40 && (_Y) >= 254 && (_X) < 245 && (_Y) < 274) {
      fin = 1;
      ChoisirCouleurDessin(CouleurParNom("white"));
      RemplirRectangle(0, 0, 300, 350);
      menu(Config);
    }
    if ((_X) >= 125 && (_Y) >= 284 && (_X) < 182 && (_Y) < 320) {
      return;
    }
  }

}
