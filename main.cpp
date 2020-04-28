#include <lpsolve/lp_lib.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include <math.h>
#include <stdlib.h>
#include <cstdlib>

using namespace std;


/*
Question 1:
    a. Les variables représentent les noeuds et les couleurs qu'on peut utiliser.
    b. - toutes les variables doivent être des entiers compris entre 0 et 1 (inclus);
       - le nombre de couleurs utilisées pour chaque noeud doit être égale à 1 (avec k couleurs disponibles) (-> chaque noeud ne peut être colorer que d'une seule et même couleur);
       - la somme des couleurs utilisées par les extrémités de chaque arête doit être inférieure à la couleur utilisée pour le noeud (-> 2 noeuds adjacents sont de couleurs différentes).
    c. Minimisation des couleus utilisées (somme de toutes les couleurs utilisées).

    LETELLIER Guillaume 21804030 L2 Info groupe 4B
*/


void vider_row(REAL row[], int taille){
  for(int i = 0; i < taille; i++){
    row[i] = 0;
  }
}


int main(int argc, char const *argv[]) {
  string file = "./graph.dimacs";
  ifstream fichier (file);
  if(!fichier.is_open()){
    cout << "Impossible d'ouvrir le fichier du graphe." << endl;
    exit(EXIT_FAILURE);
  }

  string couleursList[20] = {"Bleu", "Rouge", "Vert", "Orange", "Jaune", "Violet", "Gris", "Cyan",
                             "Magenta", "Rose", "Beige", "Noir", "Blanc", "Turquoise", "Or", "Argent",
                             "Mauve", "Ambre", "Prune", "Acajou"};

  lprec* lp;
  int n, m, k;

  
  string ligne;
  while (getline(fichier, ligne)) {
    string mot1;
    istringstream iss (ligne);
    iss >> mot1;

    if("p" == mot1){
      string mot2;
      iss >> mot2 >> n >> m;
      k = n;
      break;
    }
  }

  int nb_var = k*n+k;
  lp = make_lp(0, nb_var);
  REAL row[nb_var+1];

  // Toutes les variables sont des entiers compris entre 0 et 1.
  for(int i = 1; i < nb_var+1; i++){
    vider_row(row, nb_var+1);
    set_int(lp, i, true);
    row[i] = 1;
    add_constraint(lp, row, LE, 1);
    add_constraint(lp, row, GE, 0);
  }

  // Le nombre de couleurs utilisées pour un noeud doit être égale à 1
  vider_row(row, nb_var+1);
  for(int i = 1; i <= k*n+1; i++){
    row[i] = 1;
    if(i % k == 0){
      add_constraint(lp, row, EQ, 1);
      vider_row(row, nb_var+1);
    }
  }
  

  ifstream fichier2 (file);
  if(!fichier2.is_open()){
    cout << "Impossible d'ouvrir le fichier du graphe." << endl;
    exit(EXIT_FAILURE);
  }
  string ligne2;
  while (getline(fichier2, ligne2)) {
    string mot1;
    istringstream iss (ligne2);
    iss >> mot1;

    if("e" == mot1){
      int mot2, mot3;
      iss >> mot2 >> mot3;

      // Défini que deux noeuds adjacents ont des couleurs différentes
      for(int i = 1; i <= k; i++){
        vider_row(row, k*n+k+1);
        int indexMot2 = i + k*(mot2-1);
        int indexMot3 = i + k*(mot3-1);
        int indexCouleur = i + k*n;
        row[indexMot2] = 1;
        row[indexMot3] = 1;
        row[indexCouleur] = -1;
        add_constraint(lp, row, LE, 0);
      }
    }
  }

  // Fonction objectif : somme de toutes les couleurs utilisées
  vider_row(row, nb_var+1);
  for(int i = k*n+1; i < nb_var+1; i++){
    row[i] = 1;
  }
  set_obj_fn(lp, row);

  int ret = solve(lp);
  // write_lp(lp, "test2.lp");
  cout << "Objective value : " << get_objective(lp) << endl;
  get_variables(lp, row);
  cout << "Toutes les variables : " << endl;
  for(int i = 0; i < n; i++){
    for(int j = 0; j < k; j++){
      if(row[i*n+j] == 1.0){
        cout << "Noeud " << i+1 << " : " << couleursList[j] << endl;
      }
    }
  }
  cout << "" << endl;
  cout << "Couleurs utilisées : " << endl;
  for(int i = 0; i < k; i++){
    cout << "Couleur " << couleursList[i] << " : " << row[i+k*n] << endl;
  }
  return 0;
}
