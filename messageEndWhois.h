/*
 * Auteurs : Brice GRICHY et Loïc JOUHANNET
 * Ecole Polytechnique de l'Université de Nantes
 * SILR 2
 *
 * Mini-Projet Réseaux
 * 
 * Classe MessageEndWhois (hérite de Message)
 * Modélise les messages IRC qui indiquent la fin d'une réponse Whois
 */
#ifndef _MESSAGE_END_WHOIS
#define _MESSAGE_END_WHOIS
#include <iostream>
#include <string>

#include "message.h"

// format d'un message Whois (du moins, celui qui nous intéresse) : :addrExp 318 nickDest nickIdentifie :End of /WHOIS list.
class MessageEndWhois : public Message 
{
	private:
		string nickDest;	// Nickname du destinataire du message (en toute logique : nous)
		string nickIdentifie;	// Nickname de la personne à identifier
	public:
		MessageEndWhois(string);// constructeur
		string getNickDest();	// accesseurs...
		string getNickIdentifie();
		string getType(); 	// renvoie "318" (type de message)
};
#endif
