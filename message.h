/*
 * Auteurs : Brice GRICHY et Loïc JOUHANNET
 * Ecole Polytechnique de l'Université de Nantes
 * SILR 2
 *
 * Mini-Projet Réseaux
 * 
 * Classe Message
 * Classe abstraite, modélise tous les messages du protocole IRC 
 */
#ifndef _MESSAGE_H
#define _MESSAGE_H

#include <string>

class Message
{
	protected:
		string addrExp;			// Le seul attribut commun à tous les messages : l'adresse de l'expéditeur

	public:
		string getAddr();		// accesseur
		virtual string getType()=0;	// méthode abstraite qui renvoie le type de message (utilisée dans les classes filles)
};
#endif
