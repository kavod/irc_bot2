/*
 * Auteurs : Brice GRICHY et Loïc JOUHANNET
 * Ecole Polytechnique de l'Université de Nantes
 * SILR 2
 *
 * Mini-Projet Réseaux
 * 
 * Classe MessageBienvenue (hérite de Message)
 * Modélise les messages IRC qui indiquent la fin du message de bienvenue sur le serveur
 */
#ifndef _MESSAGE_BIENVENUE
#define _MESSAGE_BIENVENUE
#include <string>
#include "message.h"

class MessageBienvenue : public Message
{
	protected :
		string nickDest;	// notre nickname

	public :
		MessageBienvenue(string);	// constructeur
		~MessageBienvenue();		// destructeur
		string getNickDest();		// accesseur
		string getType(); 		// renvoie "376"; (type de message)
};
#endif
