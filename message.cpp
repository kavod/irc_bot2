/*
 * Auteurs : Brice GRICHY et Loïc JOUHANNET
 * Ecole Polytechnique de l'Université de Nantes
 * SILR 2
 *
 * Mini-Projet Réseaux
 * 
 * Classe Message
 * Classe abstraite, modélise tous les messages du protocole IRC 
 */
#include <string>
#include "message.h"


string Message :: getAddr()
{
	return addrExp;
}
