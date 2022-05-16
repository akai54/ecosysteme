#  Makefile 
#  Auteur : Besher AL ADDAM
#  Email  : beshoux@outlook.fr
#  Date   : 13/05/2022

SHELL = /bin/sh

# définition des commandes utilisées
CC = g++
RM = rm -f

# définition des fichiers et dossiers
PROGNAME = ecosysteme
VERSION = 1.0
SOURCES = ecosystem.cpp
HEADERS = class.h map.h

all: $(PROGNAME)

$(PROGNAME): $(SOURCES) $(HEADERS)
	$(CC) $(SOURCES) -o $(PROGNAME) -Wall -Wextra

clean:
	@$(RM) -r $(PROGNAME)
