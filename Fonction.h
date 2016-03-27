/*
 * Auteurs : Brice GRICHY et Loïc JOUHANNET
 * Ecole Polytechnique de l'Université de Nantes
 * SILR 2
 *
 * Mini-Projet Réseaux
 * 
 * Classe Fonction
 * Modélise les fonctions utilisateurs du bot
 */
#ifndef _FONCTION_H
#define _FONCTION_H
using namespace std;

#include <string>

class Fonction
{
	protected:
		string nom;	// nom de la fonction
		string cmd;	// commande associée
	
	public:
		Fonction();			// Constructeur par défaut
		Fonction(string commande); 	// Autre constructeur
		Fonction(const Fonction&);	// constructeur de recopie
		string getName();		// accesseur
		string execute(string exp,string dest,string args);	// Méthode qui permet d'exécuter une fonction
};
#endif
