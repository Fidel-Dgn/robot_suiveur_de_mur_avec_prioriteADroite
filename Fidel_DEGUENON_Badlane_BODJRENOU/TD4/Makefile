# Nom de l'exécutable
TARGET = go

# Compilateur utilisé
CC = gcc

# Options de compilation
CCFLAGS += -g -Wall -Wextra -I. -Iterminal


# Répertoire d'installation de la bibliothèque MRPiZ
# pour la compilation à destination de la cible MRPiZ (à adapter) :
LIB_MRPIZ = $(realpath $(wildcard ../lib_mrpiz*/) )

# Options de compilation pour l'utilisation de la bibliothèque MRPiZ
export CCFLAGS  += -DINTOX -DINTOX_ADDRESS=127.0.0.1 -DINTOX_PORT=12341
CCFLAGS += -I$(LIB_MRPIZ)/include/mrpiz/
LDFLAGS += -L$(LIB_MRPIZ)/lib/ -lintoxmrpiz -lintox




# Règle par défaut
all: $(TARGET)

# Construction de l'exécutable à partir des fichiers objets
$(TARGET): main.o robot.o pilot.o  solver.o follower.o
	$(CC) main.o robot.o pilot.o solver.o follower.o $(LDFLAGS)  -o $(TARGET)



#edition des liens 

# Compilation de main.c en main.o
main.o: main.c pilot.h
	$(CC) $(CCFLAGS) -c main.c -o main.o

# Compilation de robot.c en robot.o
robot.o: robot.c robot.h
	$(CC) $(CCFLAGS) -c robot.c -o robot.o

# Compilation de pilot.c en pilot.o
pilot.o: pilot.c pilot.h
	$(CC) $(CCFLAGS) -c pilot.c -o pilot.o

# Compilation de copilot.c en copilot.o
copilot.o: copilot.c copilot.h move.h
	$(CC) $(CCFLAGS) -c copilot.c -o copilot.o

#Compilation de copilot.c en copilot.o
solver.o: solver.c solver.h
	$(CC) $(CCFLAGS) -c solver.c -o solver.o

#Compilation de copilot.c en copilot.o
follower.o: follower.c follower.h 
	$(CC) $(CCFLAGS) -c follower.c -o follower.o


# Nettoyage des fichiers générés
clean:
	rm -f $(TARGET) main.o pilot.o copilot.o robot.o solver.o follower.o 
