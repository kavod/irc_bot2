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
#include <string>
#include "messageBienvenue.h"
#include <iostream>


// format d'un message Bienvenue (là encore, celui qui nous intéresse) : :addresse_expediteur 376 nickDest :End of /MOTD command.
MessageBienvenue :: MessageBienvenue(string msg)	// constructeur
{
	string mess;
	int pos1, pos2;

	mess  = msg;
	pos1 = mess.find("376");
	pos2 = 0;
	if ((mess.data()[0] == ':') && (pos1 != string::npos))	// extrait les sous chaines du messages pour remplir l'attribut
	{
		addrExp = mess.substr(1,pos1 - 2);
		mess = mess.erase(0,1);
		pos2 = mess.find(':');
		nickDest = mess.substr(pos1 + 3, pos2 - pos1 -4);
	}

}

MessageBienvenue :: ~MessageBienvenue()
{

}

string MessageBienvenue :: getNickDest()
{
	return nickDest;
}

string MessageBienvenue :: getType() // renvoie "376"
{
	return "376";
}
