all: phil

phil: phil.c
	gcc -Wall -o phil phil.c -lpthread -lrt

clean: 
	rm -fr *~ phil