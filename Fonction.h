/*
 * Auteurs : Brice GRICHY et Lo�c JOUHANNET
 * Ecole Polytechnique de l'Universit� de Nantes
 * SILR 2
 *
 * Mini-Projet R�seaux
 * 
 * Classe Fonction
 * Mod�lise les fonctions utilisateurs du bot
 */
#ifndef _FONCTION_H
#define _FONCTION_H
using namespace std;

#include <string>

class Fonction
{
	protected:
		string nom;	// nom de la fonction
		string cmd;	// commande associ�e
	
	public:
		Fonction();			// Constructeur par d�faut
		Fonction(string commande); 	// Autre constructeur
		Fonction(const Fonction&);	// constructeur de recopie
		string getName();		// accesseur
		string execute(string exp,string dest,string args);	// M�thode qui permet d'ex�cuter une fonction
};
#endif
