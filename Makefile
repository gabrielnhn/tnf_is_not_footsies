CC=gcc
cflags= -Wall $(shell pkg-config allegro-5 allegro_font-5 allegro_image-5 allegro_acodec-5 allegro_audio-5 allegro_primitives-5 --libs --cflags)
 
all: main

valmain: main.c animation.o display.o music.o player.o utils.o input.o logic.o attacks.o
	$(CC) -g main.c animation.o display.o music.o player.o utils.o input.o logic.o attacks.o -o main $(cflags) 

main: main.c animation.o display.o music.o player.o utils.o input.o logic.o attacks.o
	$(CC) main.c animation.o display.o music.o player.o utils.o input.o logic.o attacks.o -o main $(cflags) 

animation.o: animation.c animation.h utils.o
	$(CC) $(cflags) -c animation.c -o animation.o 

display.o: display.c display.h
	$(CC) $(cflags) -c display.c -o display.o

music.o: music.c music.h
	$(CC) $(cflags) -c music.c -o music.o 

player.o: player.c player.h
	$(CC) $(cflags) -c player.c -o player.o

utils.o: utils.c utils.h
	$(CC) $(cflags) -c utils.c -o utils.o

input.o: input.c input.h
	$(CC) $(cflags) -c input.c -o input.o

logic.o: logic.c logic.h
	$(CC) $(cflags) -c logic.c -o logic.o

attacks.o: attacks.c attacks.h
	$(CC) $(cflags) -c attacks.c -o attacks.o


purge: clean
	rm -rf main

clean:
	rm -rf *.o