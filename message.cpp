/*
 * Auteurs : Brice GRICHY et Lo�c JOUHANNET
 * Ecole Polytechnique de l'Universit� de Nantes
 * SILR 2
 *
 * Mini-Projet R�seaux
 * 
 * Classe Message
 * Classe abstraite, mod�lise tous les messages du protocole IRC 
 */
#include <string>
#include "message.h"


string Message :: getAddr()
{
	return addrExp;
}
