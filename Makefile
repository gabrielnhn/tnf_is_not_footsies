CC=gcc
cflags= -fcommon -std=c99 -Wall $(shell pkg-config allegro-5 allegro_font-5 allegro_image-5 allegro_acodec-5 allegro_audio-5 allegro_primitives-5 --libs --cflags)
 
all: TNF

TNF: main.c animation.o display.o music.o player.o utils.o input.o logic.o attacks.o loops.o autoplayer.o sounds.o score.o
	$(CC) main.c animation.o display.o music.o player.o utils.o input.o logic.o attacks.o loops.o autoplayer.o sounds.o score.o -o TNF $(cflags) 
# TNF: main.c animation.o display.o music.o player.o utils.o input.o logic.o attacks.o loops.o autoplayer.o sounds.o score.o
# TNF: main.c 
# 	$(CC) main.c *.c -o TNF $(cflags) 

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

loops.o: loops.c loops.h
	$(CC) $(cflags) -c loops.c -o loops.o

autoplayer.o: autoplayer.c autoplayer.h
	$(CC) $(cflags) -c autoplayer.c -o autoplayer.o

sounds.o: sounds.c sounds.h
	$(CC) $(cflags) -c sounds.c -o sounds.o

score.o: score.c score.h
	$(CC) $(cflags) -c score.c -o score.o


purge: clean
	rm -rf TNF
	rm -rf highscores.txt

clean:
	rm -rf *.o