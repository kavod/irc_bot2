/*
 * Auteurs : Brice GRICHY et Loïc JOUHANNET
 * Ecole Polytechnique de l'Université de Nantes
 * SILR 2
 *
 * Mini-Projet Réseaux
 * 
 * Classe Connexion
 * Classe mère, modélise la connexion (sur n'importe quel type de serveur)
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
		int connected;	// booléen indiquant si on est connecté
		int sock;	// socket associée
		
		
	public:
		Connexion(string arg_host=NULL,int arg_port=0);	// Constructeur
		~Connexion();					// destructeur
		int sendServer(string message=NULL);		// Méthode d'envoi de messages
		string receiveServer();				// Méthode de réception de messages
};
#endif
