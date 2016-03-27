/*
 * Auteurs : Brice GRICHY et Lo�c JOUHANNET
 * Ecole Polytechnique de l'Universit� de Nantes
 * SILR 2
 *
 * Mini-Projet R�seaux
 * 
 * Classe Connexion
 * Classe m�re, mod�lise la connexion (sur n'importe quel type de serveur)
 */
#ifndef _CONNEXION
#define _CONNEXION
 
using namespace std;

#include <string>
class Connexion
{
	protected:
		int port;	// port de connexion
		string host;	// adresse de connexion
		int connected;	// bool�en indiquant si on est connect�
		int sock;	// socket associ�e
		
		
	public:
		Connexion(string arg_host=NULL,int arg_port=0);	// Constructeur
		~Connexion();					// destructeur
		int sendServer(string message=NULL);		// M�thode d'envoi de messages
		string receiveServer();				// M�thode de r�ception de messages
};
#endif
