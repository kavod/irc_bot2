/*
 * Auteurs : Brice GRICHY et Lo�c JOUHANNET
 * Ecole Polytechnique de l'Universit� de Nantes
 * SILR 2
 *
 * Mini-Projet R�seaux
 * 
 * Classe ConnexionIRC (h�rite de connexion)
 * Mod�lise la connexion au serveur IRC
 */
#include <string>
#include <iostream>

#include "Fonction.h"
#include "connexionIRC.h"

// Constructeur
//  argument 1 : adresse du serveur
//  argument 2 : port du serveur
//  argument 3 : nickname du bot
//  argument 4 : nom du bot
//  argument 5 : mot de passe nickserv
//  argument 6 : tableau des fonctions utilisateurs
ConnexionIRC::ConnexionIRC(string arg_host,int arg_port,string arg_nick, string arg_ident, string arg_name, string arg_pass,Fonction *listFonctions) : Connexion(arg_host,arg_port)
{
	string requete;
	
	nick=arg_nick;
	ident=arg_ident;
	name=arg_name;
	pass=arg_pass;
	listFonction= listFonctions;

	requete = receiveServer();
	while (requete.find(" NOTICE ") == string::npos) // On attend une r�ponse � la connexion au serveur
	{
		requete = receiveServer();
	}
	
	cout << "On est connect�\n";
	
	requete=string("NICK ");
	requete += string(nick.data());
	requete += string("\n");
	
	sendServer(requete); // On envoie notre nickname
	
	requete = string("USER ") + ident + string(" localhost ") + host + string(" :") + name + string("\n");
	
	sendServer(requete); // On envoie notre commande d'identification
}

string ConnexionIRC::receiveServer() // R�ception des messages
{
	string buf="";
	buf.erase();
	buf = Connexion::receiveServer();
	if (buf==string(""))
		return string("");
	if (buf.substr(0,4)==string("PING"))	// Si c'est un message PING on y r�pond et on boucle sur l'�coute
	{
		buf[1]='O';
		sendServer(buf);
		buf.erase();
		buf = receiveServer();
	}
	return buf;
}

int ConnexionIRC::sendIdent()
{
	string buf;

	buf = "PRIVMSG nickserv :identify " + pass + "\n";
	sendServer(buf);	// On envoie la commande d'identification aupr�s du nickserv
	buf.erase();
	return 0;
}

string ConnexionIRC::getNick()
{
	return nick;
}

int ConnexionIRC::setFonction(Fonction *listFonction) // On met � jour la liste de nos fonctions
{
	for (int i=0 ; i<255 && (&listFonction[i] != NULL) ; i++)
		listFonction[i]= Fonction(listFonction[i]);
	
	return 0;
}

int ConnexionIRC::getFonction(string name)	// On renvoie l'indice de la fonction name
{
	for (int i=0 ; i<255 ; i++)
	{
		if (listFonction[i].getName()==name)
			return i;
	}
	return -1;
}

string ConnexionIRC::execute(int i,string exp,string dest,string args) // On ex�cute la fonction d'indice i
{
	return listFonction[i].execute(exp,dest,args);
}
