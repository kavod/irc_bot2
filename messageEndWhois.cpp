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
#include <string>
#include "messageEndWhois.h"

// format d'un message Whois (du moins, celui qui nous int�resse) : :addrExp 318 nickDest nickIdentifie :End of /WHOIS list.
MessageEndWhois::MessageEndWhois(string message) // Constructeur (remplit les attributs en extrayant les sous chaines)
{
	int pos;
	if (message[0]==':' && message.find(" 318 ") != string::npos)
	{
		message = message.substr(1);
		pos = message.find(' ');
		addrExp = message.substr(0,pos);
		message = message.substr(pos+5);
		
		pos = message.find(' ');
		nickDest = message.substr(0,pos);
		message = message.substr(pos+1);
		
		pos = message.find(' ');
		nickIdentifie = message.substr(0,pos);
	}
}

string MessageEndWhois::getNickDest()
{
	return nickDest;
}

string MessageEndWhois::getNickIdentifie()
{
	return nickIdentifie;
}

string MessageEndWhois::getType()
{
	string str;
	str =  string("318"); 
	return str;
}
 


