/*
 * Auteurs : Brice GRICHY et Loïc JOUHANNET
 * Ecole Polytechnique de l'Université de Nantes
 * SILR 2
 *
 * Mini-Projet Réseaux
 * 
 * Classe MessageWhois (hérite de Message)
 * Modélise les messages IRC indiquant si un utilisateur est identifié ou non
 */
#ifndef _MESSAGE_WHOIS
#define _MESSAGE_WHOIS


#include <iostream>
#include <string>

#include "message.h"

// format d'un message Whois (du moins, celui qui nous intéresse) : :addresse_expediteur 307 nickDest nickIdentifie :has identified for this nick
class MessageWhois : public Message 
{
	private:
		string nickDest; 	// Le nickname du destinataire de ce message, c'est à dire notre nickname (en toute logique)
		string nickIdentifie; 	// Le nickname de l'utilisateur identifié
	public:
		MessageWhois(string);		// Constructeur
		string getNickDest();		// accesseur du nickDest
		string getNickIdentifie();	// accesseur du nickIdentifie
		string getType(); 		// renvoie "307" (type du message)
};
#endif
