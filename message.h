/*
 * Auteurs : Brice GRICHY et Lo�c JOUHANNET
 * Ecole Polytechnique de l'Universit� de Nantes
 * SILR 2
 *
 * Mini-Projet R�seaux
 * 
 * Classe Message
 * Classe abstraite, mod�lise tous les messages du protocole IRC 
 */
#ifndef _MESSAGE_H
#define _MESSAGE_H

#include <string>

class Message
{
	protected:
		string addrExp;			// Le seul attribut commun � tous les messages : l'adresse de l'exp�diteur

	public:
		string getAddr();		// accesseur
		virtual string getType()=0;	// m�thode abstraite qui renvoie le type de message (utilis�e dans les classes filles)
};
#endif
