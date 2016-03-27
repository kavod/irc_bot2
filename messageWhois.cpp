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
#include <string>
#include "messageWhois.h"

// format d'un message Whois (du moins, celui qui nous int�resse) : :addresse_expediteur 307 nickDest nickIdentifie :has identified for this nick
MessageWhois::MessageWhois(string message) 				// Constructeur
{
	int pos;							// Position du curseur
	if (message[0]==':' && message.find(" 307 ") != string::npos)	// Si le message est bien de type 307
	{
		message = message.substr(1);				// On acc�de � la sous chaine entre le : et au premier espace
		pos = message.find(' ');				// pour la mettre dans addrExp
		addrExp = message.substr(0,pos);
		message = message.substr(pos+5);
		
		pos = message.find(' ');				// ... � la sous chaine entre le 2�me et le 3�me espace
		nickDest = message.substr(0,pos);			// pour la mettre dans nickDest
		message = message.substr(pos+1);
		
		pos = message.find(' ');				// ... � la sous chaine entre le 3�me et le 4�me espace
		nickIdentifie = message.substr(0,pos);			// pour la mettre dans nickIdentifie
	}
}

string MessageWhois::getNickDest()
{
	return nickDest;
}

string MessageWhois::getNickIdentifie()
{
	return nickIdentifie;
}

string MessageWhois::getType()
{
	string str;
	str =  string("307"); 
	return str;
}
 


