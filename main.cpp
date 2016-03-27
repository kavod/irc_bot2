/*
 * Auteurs : Brice GRICHY et Loïc JOUHANNET
 * Ecole Polytechnique de l'Université de Nantes
 * SILR 2
 *
 * Mini-Projet Réseaux
 * 
 * Pour compiler : make
 * Pour lancer le bot : ./bot
 * Fichier de configuration : shiva.conf
 */
using namespace std;

#include <stdio.h>
#include <string>
#include <iostream>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <signal.h>

#include "Fonction.h"
#include "connexionIRC.h"
#include "messageWhois.h"
#include "messagePrivmsg.h"
#include "messageBienvenue.h"
#include "messageEndWhois.h"

#define FILE_CONFIG "shiva.conf"

// Fonction permettant la réception du code de retour des fils
void tuerFils(int);

// Fonction permettant la fermeture du programme
void quitter(int);

// Traitement des messages reçus
int traiter(ConnexionIRC *,MessagePrivmsg*,string[]);

// Récapitulatif des différentes configurations
int recap(string,int,string[10],string,string,string,int);

// Chargement d'une chaine de caractères depuis le fichier de configuration
string loadString(FILE *);

// Chargement d'un entier à partir du fichier de configuration
int loadInt(FILE*);

// Fonction permettant de remettre à jour la liste des fonctions utilisateurs
void reloadConfigFile(int);

// Fonction min
int min(int,int);

// Fonction permettant de mettre tous les caractères en minuscule
string toLowerCase(string);

// variable globale (désolé) indiquant :
ConnexionIRC		*maConnexion;				// Objet ConnexionIRC
int main(void)
{
	char 			*buf1;					// buffer char *
	string 			buf,bufstr,host,nick,pass,name,ident;	// buffer / différentes variables de configuration
	int 			port=0;					// booléen de sorti /  N° du port de connexion
	int 			pid,i;					// pid du processus fils / variable de boucle
	FILE 			*configFile;				// Fichier de configuration
	string 			proprio[10];				// Liste des propriétaires.
	MessagePrivmsg		*bufMsg[64];				// Buffer des messages en attente de traitement
	Message			*newMsg;				// Message reçu (sans tenir compte du type)
	Fonction 		*listeFonctions = new Fonction[255];	// Liste des fonctions 

	buf1 = (char *)calloc(255,sizeof(char));			// Allocation dynamique du buffer


	printf("=========================================================\n");

	cout << "Bienvenue sur le bot IRC Eilema\n\n";
	cout << "Conception : Brice GRICHY et Loïc JOUHANNET\n";
	cout << "Ecole Polytechnique de l'Université de Nantes\n\n";

	configFile = fopen(FILE_CONFIG,"ra");	// Ouverture du fichier de configuration
	if (configFile==NULL)	// Si le fichier de configuration n'existe pas
	{	// on le créé
		cout << "Fichier de configuration introuvable\n";
		cout << "Veillez saisir le serveur\n";
		cin >> host;
		cout << "Veillez saisir le port de connexion\n";
		cin >> buf;
		port = atoi(buf.data());
		buf = "";
		cout << "Veillez saisir un propriétaire\n";
		for (i = 0;i<10 && buf.compare("EOF")!=0;i++)	// Tant que le drapeau EOF n'est pas atteint
		{
			if (i!=0)
				cout << "Veillez saisir un autre propriétaire (sinon, tapez EOF)" << endl;
			cin >> buf;
			if (buf.compare("EOF")!=0)
				proprio[i] = buf;
		}
		cout << "Veillez saisir le nickname de votre bot\n";
		cin >> nick;
		nick = nick.substr(0,nick.find(" "));
		cout << "Veillez saisir le mot de passe nickserv\n";
		cin >> pass;
		cout << "Veillez saisir le nom complet\n";
		scanf("%s\n",buf1);
		name = buf1;
		ident = name.substr(0,min(name.find("_"),name.find(" ")));

		configFile = fopen(FILE_CONFIG,"wa");
		if (configFile==NULL)
			cout << "Erreur d'écriture";
		else
		{	// On écrit dans le fichier de conf les paramètres saisis
			fprintf(configFile,
				"%s\n%i\n%s\n%s\n%s\n%s\n",
				host.data(),
				port,
				nick.data(),
				ident.data(),
				name.data(),
				pass.data());
			for (int j = 0 ; j < i - 1 ;j++)
				fprintf(configFile,"%s\n",proprio[j].data());
		}
		fprintf(configFile,"EOF\nEOF\n");
		fclose(configFile);	// Fermeture du fichier

	} else
	{
		cout << "Lecture du fichier de configuration\n";
		host = loadString(configFile);
		port = loadInt(configFile);
		nick = loadString(configFile);
		ident = loadString(configFile);
		name = loadString(configFile);
		pass = loadString(configFile);

		proprio[0] = toLowerCase(loadString(configFile));
		for (i=0;proprio[i] != "eof";i++)
			proprio[i+1] = toLowerCase(loadString(configFile));
		
		buf = loadString(configFile);
		for (i=0; buf!="EOF";i++)
		{
			listeFonctions[i]= Fonction(buf);	// Création des instances de Fonction
			buf = loadString(configFile);
		}
		cout << "Chargement terminé\n\n";
		fclose(configFile);
	}

	recap(host,port,proprio,nick,ident,name,i);	// Affichage du paramètres de connexion

	printf("Initialisation de la connexion\n");
	maConnexion = new ConnexionIRC(host,port,nick,ident,name,pass,listeFonctions);
	printf("Connexion : OK\n");

	for (i=0;i<50;i++)
		bufMsg[i]=NULL;

	// Signaux interceptés
	signal(SIGUSR1,tuerFils);
	signal(SIGUSR2,reloadConfigFile);
	signal(SIGQUIT,quitter);

	while(1)	// Tant que la commande de fermeture du programme n'a pas été reçu
	{
		// On initiallise newMsg
		newMsg = NULL;
		// On connecte
		buf = maConnexion->receiveServer();

		if (buf==string(""))
			return 0;
		// On prend la chaine à partir du premier espace
		bufstr = buf.substr(buf.find(" ")+1);
		// On tente de trouver un second espace
		if (bufstr.find(" ")!=string::npos)
		{
			// On l'a trouvé : on choppe la sous chaine entre les deux espaces
			bufstr = bufstr.substr(0,bufstr.find(" "));
			// On regarde le type de msg
			if (bufstr=="307")
			{
				// Le message est de type Whois
				newMsg = new MessageWhois(buf);
				for (i=0;i<50;i++) // On va parcourir notre liste de messages en attente
				{
					// Si le message est définit
					//  que son auteur n'a pas déjà été identifié
					//  que son auteur est le même que le nickname identifié par Whois
					if (bufMsg[i]!=NULL && bufMsg[i]->getid() != 1 && (toLowerCase(bufMsg[i]->getNickExp())==toLowerCase(((MessageWhois*) newMsg)->getNickIdentifie())))
						bufMsg[i]->setid(1);	// On marque le message comme ayant un auteur identifié
				}
				delete newMsg;
			}
			else
			{
				if (bufstr=="PRIVMSG")
				{
					// C'est un message de type privmsg
					newMsg = new MessagePrivmsg(buf);
					for (i=0;i<50 && bufMsg[i]!=NULL;i++)	// On trouve une place dans la liste des messages
						;				// en attente
					bufMsg[i]= (MessagePrivmsg*)newMsg;	// et on l'y insère
					// Nous allons ensuite envoyer une requète Whois pour savoir si l'auteur est identifié 
					//  auprès du nickserv
					maConnexion->sendServer(string("WHOIS ")+((MessagePrivmsg *)newMsg)->getNickExp()+"\n");
				}
				else
				{
					if (bufstr=="376")
					{
						// Notre connexion au serveur est terminée : on s'identifie auprès du nickserv
						newMsg = new MessageBienvenue(buf);
						maConnexion->sendIdent();
					} 
					else 
					{
						if (bufstr=="318")
						{
							// Fin d'une réponse Whois
							// Si un message de cet utilisateur était en attente et qu'il n'a pas été
							// identifié, on marque le message comme pouvant être traité (mais en ayant un
							// auteur non identifié auprès du nickserv).
							newMsg = new MessageEndWhois(buf);
							for (i=0; i<50 && (bufMsg[i]!=NULL) && bufMsg[i]->getid() == 0 &&  toLowerCase(bufMsg[i]->getNickExp())==toLowerCase(((MessageEndWhois*)newMsg)->getNickIdentifie()) ;i++)
								bufMsg[i]->setid(3);
						}
					}
				}
			}
		}

		if (newMsg != NULL)
		{
			for (i=0;i<50;i++)	// Pour chaque message en attente
			{
				if (bufMsg[i]!=NULL && (bufMsg[i]->getid()==1 || bufMsg[i]->getid()==3))
				{
					// Si nous avons reçu une réponse du Whois
					cout << "On va traiter le message N°" << i << endl;
				
					pid = fork();	// On fork pour libérer le processus père
					
					if (pid==0)	// Si c'est le processus fils
					{
						traiter(maConnexion,((MessagePrivmsg*)bufMsg[i]),proprio);
						
						kill(getppid(),SIGUSR1); // On envoie un signal au père pour que celui-ci
									// reçoive son code de retour
						_exit(0);
					}
					delete bufMsg[i];
					
					bufMsg[i]=NULL;
					
				}
			}
		}
		buf.erase();
	}
}

void reloadConfigFile(int sign)
{
	FILE 			*configFile;
	Fonction 		*listeFonctions = new Fonction[255];
	string 			buf;
	
	// Idem que pour le chargement initial
	configFile = fopen(FILE_CONFIG,"ra");
	while (loadString(configFile)!="EOF")
		;
		
	for (int i=0 ; i < 255 ; i++)
		listeFonctions[i] = Fonction();
	buf = loadString(configFile);
	for (int i=0 ; buf != "EOF" ; i++)
	{
		listeFonctions[i] = Fonction(buf);
		buf = loadString(configFile);
	}
	
	maConnexion->setFonction(listeFonctions);
	
	fclose(configFile);
}

void tuerFils(int sign)
{
	//cout << "*** TOI AUSSI MON PERE ? ***" << endl; (dixit Brutus)
	wait(NULL);
}

void quitter(int sign)
{
	cout << "Fermeture de la connexion\n";
	delete maConnexion;
	cout << "Merci d'avoir utilisé Eilema\nAu revoir !\n\n";
}

int traiter(ConnexionIRC *maConnexion, MessagePrivmsg *message,string proprio[])
{
	int estProprio=0;
	
	if (message->getContenu()[0]=='!') // Si le message commence par "!" il est possible que ce soit une fonction utilisateur
	{
		string maFonction = message->getContenu().substr(1);
		string buf;
		int i=0;
		
		i = maConnexion->getFonction(toLowerCase(maFonction.substr(0,maFonction.find(" ")))); 	// on recherche la fonction
													// dans notre liste
	
		if (i>=0)	// Si une fonction correspond
		{
			buf = maConnexion->execute(i,
				message->getNickExp(),
				message->getNickDest(),
				maFonction.substr(maFonction.find(" ")+1)); // on l'exécute
			maConnexion->sendServer(buf+"\n"); // Et on envoie la réponse
		}
	}
	
	/* Fonctions réservées aux utilisateurs indentifiés */
	
	if (message->getid()==1)
	{
		
		// On regarde si l'utilisateur est propriétaire du bot
		for (int i=0;estProprio==0 && i<10;i++)
		{
			if (proprio[i] == toLowerCase(message->getNickExp()))
				estProprio=1;
		}
		
		/* Fonctions réservées aux propriétaires identifiés */
		if (estProprio==1)
		{
			if ((toLowerCase(message->getContenu()).substr(0,7))=="!join #")
			{
				// Commande administratrice pour rejoindre un channel
				// La requète JOIN est simplement de la forme "JOIN #channel"
				maConnexion->sendServer((message->getContenu()).substr(1)+"\n");
			}
			if (toLowerCase((message->getContenu()).substr(0,7))=="!part #")
			{
				// Commande administratrice pour quitter un channel
				// La requète PART est simplement de la forme "PART #channel"
				maConnexion->sendServer((message->getContenu()).substr(1)+"\n");
			}
			if (toLowerCase((message->getContenu()).substr(0,5))=="!quit")
			{
				// Commande administratrice pour déconnecter du serveur
				// On envoie le signal de sortie au père
				kill(getppid(),SIGQUIT);
			}
			if (toLowerCase((message->getContenu()).substr(0,6))=="!nick ")
			{
				// Commande administratrice pour changer le nickname du bot
				// La requète NICK est simplement de la forme "NICK nickname"
				maConnexion->sendServer((message->getContenu()).substr(1)+"\n");
			}
			if (toLowerCase((message->getContenu()).substr(0,4))=="!do ")
			{
				// Commande administratrice pour envoyer n'importe quelle requète IRC
				maConnexion->sendServer((message->getContenu()).substr(4)+"\n");
			}
			if (toLowerCase((message->getContenu()).substr(0,13))=="!addfunction ")
			{
				// Ajout de fonction utilisateur
				if (((message->getContenu()).substr(13)).find(" ")!=string::npos)
				{
					// Ecrit la nouvelle fonction dans le fichier de configuration
					string debut,buf;
					FILE *configFile;
					configFile = fopen(FILE_CONFIG,"ra");
					debut = string("");
					buf = loadString(configFile);
					while (buf!="EOF")
					{
						debut +=buf+"\n";
						buf=loadString(configFile);
					}
					debut += "EOF\n";
					
					debut += (message->getContenu()).substr(13)+"\n";
					
					buf = loadString(configFile);
					while (buf!="EOF")
					{
						debut += buf+"\n";
						buf=loadString(configFile);
					}
					debut += "EOF\n";
					fclose(configFile);
					
					unlink(FILE_CONFIG);
					
					fopen(FILE_CONFIG,"wa");
					fprintf(configFile,debut.data());
					fclose(configFile);
					
					kill(getppid(),SIGUSR2); // Et envoie un signal au processus père pour qu'il recharge 
								// la liste des fonctions
					
				} else
				{
					maConnexion->sendServer("PRIVMSG "+message->getNickExp()+" :Syntaxe correcte : !addfunction nom_fonction commande IRC\n");
				}
			}
			if (toLowerCase((message->getContenu()).substr(0,13))=="!delfunction ")
			{
				// Fonction administratrice pour supprimer une fonction utilisatrice
				string debut,buf,buf1;
				FILE *configFile;
				
				buf1 = (message->getContenu()).substr(13);
				
				configFile = fopen(FILE_CONFIG,"ra");
				debut = string("");
				buf = loadString(configFile);
				while (buf!="EOF")
				{
					debut +=buf+"\n";
					buf=loadString(configFile);
				}
				debut += "EOF\n";
				buf = loadString(configFile);
				while (buf!="EOF")
				{
					if (buf.substr(0,buf.find(" "))!=buf1)
						debut += buf+"\n";
						
					buf=loadString(configFile);
				}
				debut += "EOF\n";
				fclose(configFile);
				
				unlink(FILE_CONFIG);
				
				fopen(FILE_CONFIG,"wa");
				fprintf(configFile,debut.data());
				fclose(configFile);
				
				kill(getppid(),SIGUSR2);
			}
		}
	}
	return 0;
}


int recap(string host,int port,string proprio[10],string nick,string ident,string name,int nb_proprio)
{
	printf("Récapitulatif de votre configuration : \n Host : %s Port : %i",host.data(),port);
	for (int j = 0 ; j < nb_proprio - 1 ;j++)
		printf(" Propriétaire %i : %s",j,proprio[j].data());
	printf(" Nickname : %s",nick.data());
	printf(" Ident : %s",ident.data());
	printf(" Full Name : %s\n",name.data());

	return 0;
}

string loadString(FILE *configFile)
{
	// Renvoie une ligne du fichier
	string str;
	char *buf;

	buf = (char *)calloc(255,sizeof(char));

	fgets(buf,256,configFile);
	str = buf;
	str.erase(str.length()-1,1);// On vire le dernier caractère renvoyé par fgets qui est un \n
	cout << str << endl;

	return str;
}

int loadInt(FILE *configFile)
{
	// Renvoie une ligne du fichier de configuration sous la forme d'un entier
	char *buf;

	buf = (char *)calloc(255,sizeof(char));
	fgets(buf,256,configFile);
	return atoi(buf);
}

int min(int x, int y)
{
	// Fonction min (non disponible sur notre machine)
    if (x <= y)
        return x;
    return y;
}

string toLowerCase(string str)
{
	// Fonction qui met tout en minuscule
	for (int i=0;i<str.length();i++)
		str[i]=tolower(str[i]);
	return str;
}
