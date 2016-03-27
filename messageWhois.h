/*
 * Auteurs : Brice GRICHY et Lo�c JOUHANNET
 * Ecole Polytechnique de l'Universit� de Nantes
 * SILR 2
 *
 * Mini-Projet R�seaux
 * 
 * Classe MessageWhois (h�rite de Message)
 * Mod�lise les messages IRC indiquant si un utilisateur est identifi� ou non
 */
#ifndef _MESSAGE_WHOIS
#define _MESSAGE_WHOIS


#include <iostream>
#include <string>

#include "message.h"

// format d'un message Whois (du moins, celui qui nous int�resse) : :addresse_expediteur 307 nickDest nickIdentifie :has identified for this nick
class MessageWhois : public Message 
{
	private:
		string nickDest; 	// Le nickname du destinataire de ce message, c'est � dire notre nickname (en toute logique)
		string nickIdentifie; 	// Le nickname de l'utilisateur identifi�
	public:
		MessageWhois(string);		// Constructeur
		string getNickDest();		// accesseur du nickDest
		string getNickIdentifie();	// accesseur du nickIdentifie
		string getType(); 		// renvoie "307" (type du message)
};
#endif
