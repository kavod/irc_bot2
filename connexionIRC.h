/*
 * Auteurs : Brice GRICHY et Loïc JOUHANNET
 * Ecole Polytechnique de l'Université de Nantes
 * SILR 2
 *
 * Mini-Projet Réseaux
 * 
 * Classe ConnexionIRC (hérite de Connexion)
 * Modélise la connexion au serveur IRC
 */
#ifndef _CONNEXION_IRC
#define _CONNEXION_IRC
 
using namespace std;

#include <string.h>
#include "Fonction.h"
#include "connexion.h"


class ConnexionIRC : public Connexion
{
	protected:
		string nick;	// nickname du bot sur le serveur IRC
		string ident;	// Son identifiant
		string name;	// Son nom
		string pass;	// son mot de passe nickserv (pour lui permettre d'enregistrer son nickname)
		Fonction *listFonction;
		
	public:
		ConnexionIRC(string arg_host=NULL,int arg_port=0,string nick=string(""), string ident=string(""), string name=string(""), string pass=string(""), Fonction *listeFonctions=new Fonction[255]); // constructeur
		string receiveServer();		// méthode de réception de messages
		int sendIdent();		// méthode permettant de s'identifier auprès du nickserv
		string getNick();		// accesseur
		int setFonction(Fonction*);	// Met à jour la liste des fonctions
		int getFonction(string name);	// Renvoie l'indice de la fonction ayant le nom "name"
		string execute(int i,string,string,string);	// exécute la fonction d'indice i
};
#endif
