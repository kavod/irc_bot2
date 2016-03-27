CC		=	g++
CLASSES_O	=	Fonction.o connexion.o connexionIRC.o message.o messagePrivmsg.o messageBienvenue.o messageWhois.o messageEndWhois.o
CLASSES_C	=	Fonction.cpp connexion.cpp connexionIRC.cpp message.cpp messagePrivmsg.cpp messageBienvenue.cpp messageWhois.cpp messageEndWhois.cpp
MAIN		=	main
BIN		=	bot


all: ${MAIN}.o ${CLASSES_O}
	${CC} ${MAIN}.o ${CLASSES_O} -o bot

%.o: %cpp
	${CC} -c $<
clean: ${MAIN}.o ${CLASSES_O}
	rm *.o

mrproper: clean
	rm bot
