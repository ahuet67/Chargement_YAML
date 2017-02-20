# MAKEFILE projet de programmation structuree

#Variables
CFLAGS= -W -Wall
EXEC= exec
#On note pour compiler avec debug: make DEBUG=yes
#Pour compiler avec release: make DEBUG=no
DEBUG=yes/no
ifeq ($(DEBUG),yes)
	CFLAGS += -g -DDEBUG
endif

#cibles
#Compilation principale
$(EXEC): main.o fonction.o
	gcc -o $(EXEC) main.o fonction.o

main.o: main.c fonction.h
	gcc $(CFLAGS) -c main.c

# avec fonction.c le fichier c avec toutes les fonctions utiles au main.c
fonction.o: fonction.c fonction.h
	gcc $(CFLAGS) -c fonction.c

#Cibles usuelles
default: $(EXEC)

#Pour nettoyer le répertoire: make clean
clean:
	rm -rf *.o
	rm $(EXEC)
