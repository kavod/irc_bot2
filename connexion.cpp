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
#include "connexion.h"

#include <stdio.h>
#include <string>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <netinet/in.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <ctype.h>
#include <iostream>

using namespace std;

typedef struct sockaddr_in SOCKADDR_IN; 

Connexion::Connexion(string arg_host,int arg_port)
{
	unsigned int addr;
        struct hostent *hp;
        struct sockaddr_in sin;

	connected = -1;
	port = arg_port;
	host.assign(arg_host);
	
        if (isalpha(host[0]))	// Si l'adresse est de type alphab�tique : c'est une adresse DNS
                hp=gethostbyname(host.data());
        else
        { 
                addr = inet_addr(host.data());	// Sinon, c'est une adresse IP
                hp = gethostbyaddr((char *)&addr,4,AF_INET); 
        }

        sin.sin_addr.s_addr =   *((u_int32_t *) hp->h_addr);
        sin.sin_family = AF_INET;
        sin.sin_port=htons(port);

        this->sock = socket(PF_INET, SOCK_STREAM, 0);

        connected = connect(sock,(struct sockaddr *)&sin,sizeof(SOCKADDR_IN));
	printf("Connected : %i\n",connected);
}

int Connexion::sendServer(string message)
{
	cout << ">>" << message << endl;		// On affiche les messages envoy�s pr�c�d�s de ">>"
	return send(sock,message.data(),message.length(),0);
}

string Connexion::receiveServer()
{
	int pos;
	char c;
	int buf_len;
	char *buf=NULL;
	string buf_str;

	buf = (char *)(malloc(10*sizeof(char)));
	for (pos = 0 ; pos<10 ; pos++)
		buf[pos]=0;
	
	pos=0;
	buf_len = 10;
	c=0;
	while (c!='\n')		// Tant qu'on ne re�oit pas le caract�re \n, on met les caract�res re�us dans un buffer
	{
		if (recv(sock,&c,sizeof(char),0)==-1)
			return string("");
		if (c!='\r')
			buf[pos]=c;
		pos++;
		if (pos == buf_len)
		{
			buf_len += 10;
			buf = (char *)realloc(buf,buf_len * sizeof(char));
			for (int i = pos ; i < (pos + 10) ; i++)
				buf[i]=0;
		}
		buf[pos]='\0';
	}
	cout << buf << "\n";
	buf_str = string(buf);
		
	return buf_str;
}

Connexion::~Connexion()
{
	close(sock);	// On ferme la socket
}
