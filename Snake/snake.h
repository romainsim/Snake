#ifndef SNAKE.H
#define SNAKE.H

enum etatCase {vide,pomme,obstacle};
enum direction {haut,bas,gauche,droit};

struct Jeu {
  enum etatCase* tabCases;
  enum direction direction;
  int tailleSerpent;
  int pommesRestantes;
  int temps;
  int niveau;
};

struct Membre {
  int idCase;
  struct Membre* precedent;
  struct Membre* suivant;
};

struct Snake {
  struct Membre* tete;
  struct Membre* queue;
};

void initialiserTabCases(struct Jeu*, int);
int avoirColonne(int, struct Config*);
int avoirLigne(int, struct Config*);
void genererPommes(struct Jeu*, struct Config*);
void creerSerpent(struct Snake*, int, int);
void agrandirSerpent(struct Snake*, int);
void reduireSerpent(struct Snake*, struct Config*);
int toucheSerpent(struct Jeu*, struct Snake*, int, struct Config*);
int touchePomme(struct Jeu*, int);
void addition(int*, int*, char*);
void affichageNiveau(struct Jeu*, struct Config*);
void genererObstacles(struct Jeu*, struct Config*);
void fenetre(struct Config*, struct Jeu*, char*);

#endif
