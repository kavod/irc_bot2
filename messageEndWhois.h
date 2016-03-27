/*
 * Auteurs : Brice GRICHY et Lo�c JOUHANNET
 * Ecole Polytechnique de l'Universit� de Nantes
 * SILR 2
 *
 * Mini-Projet R�seaux
 * 
 * Classe MessageEndWhois (h�rite de Message)
 * Mod�lise les messages IRC qui indiquent la fin d'une r�ponse Whois
 */
#ifndef _MESSAGE_END_WHOIS
#define _MESSAGE_END_WHOIS
#include <iostream>
#include <string>

#include "message.h"

// format d'un message Whois (du moins, celui qui nous int�resse) : :addrExp 318 nickDest nickIdentifie :End of /WHOIS list.
class MessageEndWhois : public Message 
{
	private:
		string nickDest;	// Nickname du destinataire du message (en toute logique : nous)
		string nickIdentifie;	// Nickname de la personne � identifier
	public:
		MessageEndWhois(string);// constructeur
		string getNickDest();	// accesseurs...
		string getNickIdentifie();
		string getType(); 	// renvoie "318" (type de message)
};
#endif
