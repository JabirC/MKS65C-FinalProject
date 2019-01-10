all: client server

server: server.o networking.o
	gcc -g -o server server.o networking.o

client: client.o networking.o
	gcc -g -o client client.o networking.o

client.o: client.c fxn.c networking.h
	gcc -g -c client.c

server.o: server.c fxn.c networking.h
	gcc -g -c server.c

networking.o: networking.c networking.h
	gcc -g -c networking.c

run: fxn
	./fxn

fxn: fxn.c
	gcc -g -o fxn fxn.c

clean:
	rm *.o
	rm *~
