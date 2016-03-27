/*
 * Auteurs : Brice GRICHY et Loïc JOUHANNET
 * Ecole Polytechnique de l'Université de Nantes
 * SILR 2
 *
 * Mini-Projet Réseaux
 * 
 * Classe MessagePrivmsg (hérite de Message)
 * Modélise les messages IRC qui transmettent les messages utilisateurs
 */
#include <string>
#include "messagePrivmsg.h"
#include <iostream>


// format d'un Privmsg : :nickExp!~identExp@addresse_expediteur PRIVMSG nickDest :contenu
MessagePrivmsg :: MessagePrivmsg(string msg)		// Constructeur
{
	string mess;
	int pos1, pos2;

	mess  = msg;
	pos1 = mess.find("PRIVMSG");
	pos2 = 0;
	if ((mess.data()[0] == ':') && (pos1 != string::npos)) 	// On extraits les sous chaines du message selon le format des PRIVMSG
	{							// (voir ci-dessus) et on remplit les attributs
		pos1 = mess.find("!~");				//position de la chaine "!~"
		nickExp = mess.substr(1, pos1-1);
		pos2 = mess.find('@');				//position du caratère "@"
		identExp = mess.substr(pos1 + 2,pos2 - pos1 - 2);
		pos1 = pos2;
		pos2 = mess.find(" PRIVMSG");			// position de PRIVMSG
		addrExp = mess.substr(pos1 + 1,pos2 - pos1 - 1);
		pos1 = pos2 + 9;
		mess = mess.erase(0,1);
		pos2 = mess.find(':');
		nickDest = mess.substr(pos1 - 1, pos2 - pos1);
		pos1 = pos2;
		pos2 = mess.find("\n");
		contenu = mess.substr(pos1 + 1, pos2 - pos1 - 1);
		identifie = 0;
	}

}

MessagePrivmsg :: ~MessagePrivmsg()
{
}

string MessagePrivmsg :: getNickExp()
{
	return nickExp;
}

string MessagePrivmsg :: getIdentExp()
{
	return identExp;
}

string MessagePrivmsg :: getNickDest()
{
	return nickDest;
}

string MessagePrivmsg :: getContenu()
{
	return contenu;
}

string MessagePrivmsg :: getAddr()
{
	return addrExp;
}

int MessagePrivmsg :: setid(int id) 
{
	identifie=id;
	return 0;
}

int MessagePrivmsg :: getid() // renvoie identifie
{
	return identifie;
}

string MessagePrivmsg :: getType() // renvoie "PRIVMSG"
{
	return "PRIVMSG";
}
