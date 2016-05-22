#CFLAG = -02
CFLAG = -Wall -std=c++11
# -g activa la informacion de debug
#CFLAG = -g
LIB_PATH = -L../lib -L.
LIBS = -lpthread -lbingrep

all: main move strip clean

main: main.o utils.o
	g++ $(CFLAG) main.o utils.o -o bingrep $(LIB_PATH) $(LIBS)

main.o: main.cpp
	g++ $(CFLAG) -c main.cpp -o main.o

utils.o:
	g++ $(CFLAG) -c utils.cpp -o utils.o

move:
	mkdir -p ../bin
	mv bingrep ../bin

strip:
	strip -s ../bin/*

clean:
	rm -Rf *.o

distclean: clean
	rm -Rf ../bin
