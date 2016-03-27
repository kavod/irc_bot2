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
#ifndef _MESSAGE_PRIVMSG
#define _MESSAGE_PRIVMSG

#include <string>
#include "message.h"

class MessagePrivmsg : public Message
{
	protected :
		string nickExp;		// nickname de l'expéditeur du message
		string identExp;	// Identifiant de l'expéditeur du message
		string nickDest;	// Notre nickname en cas de message privé, le channel de diffusion sinon
		string contenu;		// Contenu du message
		int identifie;		// 0 : l'auteur du message n'a pas encore été identifié
					// 1 : L'auteur du message a été reconnu comme identifié
					// 2 : obsolète
					// 3 : L'auteur du message a été reconnu comme non identifié

	public :
		MessagePrivmsg(string);	// Constructeur
		~MessagePrivmsg();	// Destructeur
		string getNickExp();	// accesseurs
		string getIdentExp();
		string getNickDest();
		string getContenu();
		string getAddr();
		int setid(int); 	// Change la variable identifie
		int getid(); 		// renvoie identifie
		string getType(); 	// renvoie "PRIVMSG" (type du message)
};
#endif
