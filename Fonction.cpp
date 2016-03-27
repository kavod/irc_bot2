/*
 * Auteurs : Brice GRICHY et Loïc JOUHANNET
 * Ecole Polytechnique de l'Université de Nantes
 * SILR 2
 *
 * Mini-Projet Réseaux
 * 
 * Classe Fonction
 * Modélise les fonctions utilisateurs du bot
 */
#include <stdio.h>

#include "Fonction.h"

Fonction::Fonction()	// Constructeur par défaut
{
	Fonction("");
}
//format de message demandant une création de fonction : !addfunction salut privmsg $chan :Salut $nick
Fonction::Fonction(string commande)	// commande est tout ce qui se situe après le !addfunction
{
	if (commande.find(" ")==string::npos)
	{
		nom="";
		cmd="";
	} else
	{
		nom=commande.substr(0,commande.find(" "));	// le nom la sous chaine se trouvant avant le premier espace
		cmd=commande.substr(commande.find(" ")+1);	// commande est le reste de la chaine
	}
}

Fonction::Fonction(const Fonction &maFonction)
{
	nom=maFonction.nom;
	cmd=maFonction.cmd;
}

string Fonction::execute(string exp,string dest,string args)
{
	string str,debut,fin,requete;
	int pos=0;
	string arguments[10];
	char nombre[2];
	
	str=args;

	pos=str.find(" ");
	for (int i=0; i<10 ; i++)		// extrait les arguments de la chaîne d'exécution
	{					// Exemple : !salut var0 var1 var2
		if (pos!=string::npos)		// le premier argument sera var0, le second : var1 etc...
		{
			arguments[i]=str.substr(0,pos);
			str=str.substr(pos+1);
		} else
		{
			arguments[i]=str;
			str="";
		}
		pos=str.find(" ");
	}
	
	requete=cmd;
	
	pos=requete.find(" $chan");	// Remplace la variable $chan par le nick de l'utilisateur si la commande a été exécutée
	while (pos!=string::npos)	//  en privé, le nom du channel sinon
	{
		fin=requete.substr(pos+6);
		debut=requete.substr(0,pos+1);
		if (dest[0]=='#')
			requete=debut+dest+fin;
		else
			requete=debut+exp+fin;
		pos=requete.find(" $chan");
	}

	pos=requete.find("$nick");	// Remplace la variable $nick par le nickname de l'utilisateur (toujours)
	while (pos!=string::npos)
	{
		fin=requete.substr(pos+5);
		debut=requete.substr(0,pos);
		requete=debut+exp+fin;
		pos=requete.find("$nick");
	}


	for (int i=0;i<10;i++)		// Remplace les variables $0, $1, etc... par les arguments
	{
		sprintf(nombre,"%i",i);
		pos=requete.find(" $"+string(nombre));
		while (pos!=string::npos)
		{
			fin=requete.substr(pos+3);
			debut=requete.substr(0,pos+1);
			requete=debut+arguments[i]+fin;
			pos=requete.find(" $"+string(nombre));
		}
	}
	
	return requete;
}

string Fonction::getName()
{
	return nom;
}
