# Coloration de graphe

Projet universitaire de résolution mathématique du problème de K-Coloration d'un graphe donné dans l'UE Sécurité et Aide à la Décision en L2 Informatique à l'Université de Caen Normandie.

<img src="logo-UNICAEN.jpg" style="width: 100px;" />


## Table des matières
1. [Introduction au sujet](#introduction)
2. [Setup](#setup)
3. [Utilisation](#utilisation)

## Introduction
Le but du projet est de déterminer le nombre mamimum de couleurs, de façon optimale, pouvant colorer un graphe (dans le fichier `graph.dimacs`) en respectant une contrainte, **il ne faut pas que les couleurs de 2 noeuds reliés soient les mêmes**. 

L'autre but était de faire cela avec l'API d'un outil, **lp_solve**. Cet outil permet de faire de la programmation linéaire afin de résoudre des problèmes mathématiques comme des problèmes d'optimisation et de maximisation de certaines valeurs. [Lien vers l'API](http://lpsolve.sourceforge.net/5.5/lp_solveAPIreference.htm).

## Setup
Pour Windows :
Rendez-vous sur [ce site](http://lpsolve.sourceforge.net/5.5/distribution.htm) afin d'installer la version développeur de lp_solve. Sans cela, il vous sera impossible d'utiliser l'API de lp_solve.

Pour MacOS et Linux:
Exécutez la commande suivante : ```sudo apt install liblpsolve55-dev```

## Utilisation
Vous pouvez exécuter le script avec cette commande : ```g++ main.cpp -llpsolve55 -lcolamd -ldl -o exe```
Pour modifier le graphe, veuillez modifier le fichier `graph.dimacs` en respectant les règles d'écriture.
