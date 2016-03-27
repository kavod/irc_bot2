/*
 * Auteurs : Brice GRICHY et Lo�c JOUHANNET
 * Ecole Polytechnique de l'Universit� de Nantes
 * SILR 2
 *
 * Mini-Projet R�seaux
 * 
 * Classe ConnexionIRC (h�rite de Connexion)
 * Mod�lise la connexion au serveur IRC
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
		string receiveServer();		// m�thode de r�ception de messages
		int sendIdent();		// m�thode permettant de s'identifier aupr�s du nickserv
		string getNick();		// accesseur
		int setFonction(Fonction*);	// Met � jour la liste des fonctions
		int getFonction(string name);	// Renvoie l'indice de la fonction ayant le nom "name"
		string execute(int i,string,string,string);	// ex�cute la fonction d'indice i
};
#endif
