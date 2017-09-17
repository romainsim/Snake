#include <stdlib.h>
#include <graph.h>
#include <stdio.h>
#include <unistd.h>
#include <time.h>
#include "menu.h"
#include "snake.h"
#include "fin.h"

void initialiserTabCases(struct Jeu* Jeu, int tailleGrille) {
  Jeu->tabCases = (enum etatCase*) malloc(sizeof(enum etatCase) * (tailleGrille+1));
  
  int i = 0;
  while (i <= tailleGrille) {
    Jeu->tabCases[i] = vide;
    i++;
  }
  /* On a des cases vides de 0 a tailleGrille - 1 */
}

int avoirColonne(int idCase, struct Config* Config) {
  if ((idCase%Config->longueurGrille) == 0)
    return Config->longueurGrille*20-20;
  return (idCase%Config->longueurGrille-1)*20;
}

int avoirLigne(int idCase, struct Config* Config) {
  if ((idCase%Config->longueurGrille) == 0)
    return (idCase/Config->longueurGrille)*20-20;
  return (idCase/Config->longueurGrille)*20;
}

void genererPommes(struct Jeu* Jeu, struct Config* Config) {
  int i = 0, tailleGrille = Config->hauteurGrille * Config->longueurGrille, nombreAleatoire;
  ChoisirCouleurDessin(CouleurParNom("red"));
  srand(time(NULL));

  while (i < Config->nombrePastille) {
    nombreAleatoire = rand()%tailleGrille+1;
    if (Jeu->tabCases[nombreAleatoire] == pomme)
      ;
    else {
      Jeu->tabCases[nombreAleatoire] = pomme;
      RemplirRectangle(avoirColonne(nombreAleatoire, Config), avoirLigne(nombreAleatoire, Config), 20, 20);
      i++;
    }
  }
}

void creerSerpent(struct Snake* Snake, int caseActuelle, int caseDebut) {
  struct Membre* premier = (struct Membre*) malloc(sizeof(struct Membre));
  struct Membre* deuxieme = (struct Membre*) malloc(sizeof(struct Membre));

  Snake->tete = deuxieme;
  Snake->queue = premier;
  
  premier->idCase = caseDebut;
  deuxieme->idCase = caseActuelle;
  premier->precedent = deuxieme;
  premier->suivant = NULL;
  deuxieme->precedent = NULL;
  deuxieme->suivant = premier;
}

void agrandirSerpent(struct Snake* Snake, int caseActuelle) {
  struct Membre* ajout = (struct Membre*) malloc(sizeof(struct Membre));

  Snake->tete->precedent = ajout;
  
  ajout->idCase = caseActuelle;
  ajout->suivant = Snake->tete;
  ajout->precedent = NULL;

  Snake->tete = ajout;
}

void reduireSerpent(struct Snake* Snake, struct Config* Config) {
  struct Membre* temporaire = Snake->queue;

  Snake->queue->precedent->suivant = NULL;
  Snake->queue = Snake->queue->precedent;
  ChoisirCouleurDessin(CouleurParNom("white"));
  int caseAVider = Snake->queue->idCase;
  RemplirRectangle(avoirColonne(caseAVider, Config), avoirLigne(caseAVider, Config),20,20);
  free(temporaire);
  ChoisirCouleurDessin(CouleurParNom("green"));
}

int toucheSerpent(struct Jeu* Jeu, struct Snake* Snake, int caseActuelle, struct Config* Config) {
  struct Membre* temporaire;
  for (temporaire = Snake->tete; temporaire->suivant != NULL; temporaire = temporaire->suivant) { 
    if (caseActuelle == temporaire->idCase || Jeu->tabCases[caseActuelle] == obstacle) {
      return 1;
    }
  }
  return 0;
}

int touchePomme(struct Jeu* Jeu, int caseActuelle) {
  if (Jeu->tabCases[caseActuelle] == pomme) {
    Jeu->tabCases[caseActuelle] = vide;
    return 1;
  }
  return 0;
}

void addition(int score[],int score1[],char score2[]){
  int i;
    
  int c;
  int retenue=0;
  for (c=0;c<7;c++){
    int tmp=score[7-c-1]+score1[7-c-1]+retenue;
    score[7-c-1]= tmp%10;
    retenue=tmp/10;

  }
  for (i=0;i<7;i++){
    if (score[i]==0){
      score2[i]='0';
    }
    if (score[i]==1){
      score2[i]='1';
    }
    if (score[i]==2){
      score2[i]='2';
    }
    if (score[i]==3){
      score2[i]='3';
    }
    if (score[i]==4){
      score2[i]='4';
    }
    if (score[i]==5){
      score2[i]='5';
    }
    if (score[i]==6){
      score2[i]='6';
    }
    if (score[i]==7){
      score2[i]='7';
    }
    if (score[i]==8){
      score2[i]='8';
    }
    if (score[i]==9){
      score2[i]='9';
    }
  }
}

void affichageNiveau(struct Jeu* Jeu, struct Config* Config) {
  EcrireTexte(Config->longueurGrille*20+15, 50, "Niveau", 2);
  ChoisirCouleurDessin(CouleurParNom("pink"));
  int niveau = Jeu->niveau + 1;
  if (niveau >= 10) {
    int dizaine = niveau / 10;
    int unite = niveau % 10;
    char entierTab[3] = {'0', '0', '\0'};
    entierTab[0] = '0' + dizaine;
    entierTab[1] = '0' + unite;
    EcrireTexte(Config->longueurGrille*20+110, 51, entierTab, 2);
  }
  else if (niveau < 10) {
    char entierTab[2] = {'0', '\0'};
    entierTab[0] = '0' + niveau;
    EcrireTexte(Config->longueurGrille*20+110, 51, entierTab, 2);
  }
}

void genererObstacles(struct Jeu* Jeu, struct Config* Config) {
  int i = 0, tailleGrille = Config->hauteurGrille * Config->longueurGrille, nombreAleatoire;
  ChoisirCouleurDessin(CouleurParNom("black"));

  while (i < Jeu->niveau) {
    nombreAleatoire = rand()%tailleGrille+1;
    if (Jeu->tabCases[nombreAleatoire] == pomme || Jeu->tabCases[nombreAleatoire] == obstacle)
      ;
    else {
      Jeu->tabCases[nombreAleatoire] = obstacle;
      RemplirRectangle(avoirColonne(nombreAleatoire, Config), avoirLigne(nombreAleatoire, Config), 20, 20);
      i++;
    }
  }
}

int score[7]= {0,0,0,0,0,0,0};
int score1[7]= {0,0,0,0,0,0,5};

void fenetre(struct Config* Config, struct Jeu* Jeu, char score2[]) {
  
  int tailleGrille = Config->longueurGrille * Config->hauteurGrille;
  initialiserTabCases(Jeu, tailleGrille);
  Jeu->tailleSerpent = 1;
  Jeu->pommesRestantes = Config->nombrePastille;
  Jeu->direction = 5;
  int tailleSerpent = Config->tailleSerpent;

  InitialiserGraphique();
  CreerFenetre(0,0,20*Config->longueurGrille+150,20*Config->hauteurGrille);
  affichageNiveau(Jeu, Config);
  genererPommes(Jeu, Config);
  genererObstacles(Jeu, Config);
  ChoisirCouleurDessin(CouleurParNom("green"));
  EcrireTexte(20*Config->longueurGrille+25,20*Config->hauteurGrille-20,score2,2);

  ChoisirCouleurDessin(CouleurParNom("grey"));
  RemplirRectangle(Config->longueurGrille*20, 0, 2, Config->hauteurGrille*20);

  int caseDebut = tailleGrille/2+Config->longueurGrille/2+1;
  int caseActuelle = caseDebut;
  int perdu = 0, gagne = 0, pause = 0, commencer = 0, touche, hitPomme = 0;
  struct Snake Snake;

  ChoisirCouleurDessin(CouleurParNom("green"));
  RemplirRectangle(avoirColonne(caseDebut, Config), avoirLigne(caseDebut, Config),20,20);

  while (!perdu && !gagne) {
    if (ToucheEnAttente()) {
      touche = Touche();
      
      switch(touche) {
      case XK_Right:
	if (avoirColonne(caseActuelle, Config) == (Config->longueurGrille-1)*20)
	  perdu = 1;
	if (Jeu->direction == gauche)
	  caseActuelle--;
	else {
	  caseActuelle++;
	  Jeu->direction = droit;
	  commencer = 1;
	}
	break;
      case XK_Left:
	if (avoirColonne(caseActuelle, Config) == 0)
          perdu = 1;
	if (Jeu->direction == droit)
	  caseActuelle++;
	else {
	  caseActuelle--;
	  Jeu->direction = gauche;
	  commencer = 1;
	}
	break;
      case XK_Down:
	if (Jeu->direction == haut)
	  caseActuelle -= Config->longueurGrille;
	else {
	  caseActuelle += Config->longueurGrille;
	  if (caseActuelle > tailleGrille)
	    perdu = 1;
	  Jeu->direction = bas;
	  commencer = 1;
	}
	break;
      case XK_Up:
	if (Jeu->direction == bas)
	  caseActuelle += Config->longueurGrille;
	else {
	  caseActuelle -= Config->longueurGrille;
	  if (caseActuelle < 1)
	    perdu = 1;
	  Jeu->direction = haut;
	  commencer = 1;
	}
	break;
      case XK_space:
	pause = 1;
	while (Touche() != XK_space)
	  ;
	break;
      case XK_Escape:
	return;
      }      
    }

    else if (commencer) {
      if (Jeu->direction == droit) {
	if (avoirColonne(caseActuelle, Config) == (Config->longueurGrille-1)*20)
          perdu = 1;
	else
	  caseActuelle++;
      }
      else if (Jeu->direction == gauche) {
	if (avoirColonne(caseActuelle, Config) == 0)
	  perdu = 1;
	caseActuelle--;
      }
      else if (Jeu->direction == bas) {
	caseActuelle += Config->longueurGrille;
	if (caseActuelle > tailleGrille)
          perdu = 1;
      }
      else if (Jeu->direction == haut) {
	caseActuelle -= Config->longueurGrille;
	if (caseActuelle < 1)
	  perdu = 1;
      }
    }
    
    if (perdu || pause) {
      if (pause)
	pause = 0;
    }
    else {
      if (commencer) {
	Jeu->tailleSerpent++;

	RemplirRectangle(avoirColonne(caseActuelle, Config), avoirLigne(caseActuelle, Config),20,20);	
	if (toucheSerpent(Jeu, &Snake, caseActuelle, Config))
	  perdu = 1;

	if (touchePomme(Jeu, caseActuelle)) {
	  addition(score,score1,score2);
	  ChoisirCouleurDessin(CouleurParNom("white"));
	  RemplirRectangle(20*Config->longueurGrille+25,20*Config->hauteurGrille-45,100,25);
	  ChoisirCouleurDessin(CouleurParNom("green"));
	  EcrireTexte(20*Config->longueurGrille+25,20*Config->hauteurGrille-20,score2,2);
	  Jeu->pommesRestantes--;
	  hitPomme++;
	  Config->tailleSerpent++;
	}
	
	if (Jeu->tailleSerpent > 1 && Jeu->tailleSerpent < Config->tailleSerpent)
	  agrandirSerpent(&Snake, caseActuelle);
	else if (Jeu->tailleSerpent >= Config->tailleSerpent) {
	  agrandirSerpent(&Snake, caseActuelle);
	  if (!hitPomme)
	    reduireSerpent(&Snake, Config);
	  else
	    hitPomme = 0;
	}
      }
      fflush(stdout);
      usleep(Jeu->temps);
    }
    if (!(Jeu->pommesRestantes))
      gagne = 1;

    if (Jeu->tailleSerpent == 1)
      creerSerpent(&Snake, caseDebut, caseActuelle);
  }

  if (perdu) {
    FermerGraphique();
    fin(score2, Jeu, Config);
  }
  else if (gagne) {
    Jeu->niveau++;
    if (Jeu->temps <= 50000)
      ;
    else
      Jeu->temps -= 50000;
    Config->nombrePastille++;
    Config->tailleSerpent = tailleSerpent;
    FermerGraphique();
    fenetre(Config, Jeu, score2);
  }
  
}
