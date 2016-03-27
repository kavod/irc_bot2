/*
 * Auteurs : Brice GRICHY et Lo�c JOUHANNET
 * Ecole Polytechnique de l'Universit� de Nantes
 * SILR 2
 *
 * Mini-Projet R�seaux
 * 
 * Classe MessagePrivmsg (h�rite de Message)
 * Mod�lise les messages IRC qui transmettent les messages utilisateurs
 */
#ifndef _MESSAGE_PRIVMSG
#define _MESSAGE_PRIVMSG

#include <string>
#include "message.h"

class MessagePrivmsg : public Message
{
	protected :
		string nickExp;		// nickname de l'exp�diteur du message
		string identExp;	// Identifiant de l'exp�diteur du message
		string nickDest;	// Notre nickname en cas de message priv�, le channel de diffusion sinon
		string contenu;		// Contenu du message
		int identifie;		// 0 : l'auteur du message n'a pas encore �t� identifi�
					// 1 : L'auteur du message a �t� reconnu comme identifi�
					// 2 : obsol�te
					// 3 : L'auteur du message a �t� reconnu comme non identifi�

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
