CC=gcc
cflags= -Wall


# old_main: old_main.c animation.o display.o music.o player.o
# 	$(CC) $(cflags) old_main.c animation.o display.o music.o player.o utils.o -o old_main $(shell pkg-config allegro-5 allegro_font-5 allegro_image-5 allegro_acodec-5 allegro_audio-5 --libs --cflags)

allegro_test:
	$(CC) $(cflags) allegro_test.c -o allegro_test $(pkg-config allegro-5 allegro_font-5 --libs --cflags) 

main: main.c animation.o display.o music.o player.o
	$(CC) $(cflags) -g main.c animation.o display.o music.o player.o utils.o -o main $(shell pkg-config allegro-5 allegro_font-5 allegro_image-5 allegro_acodec-5 allegro_audio-5 --libs --cflags)

animation.o: animation.c animation.h utils.o
	$(CC) $(cflags) -c animation.c utils.o -o animation.o 

display.o: display.c display.h
	$(CC) $(cflags) -c display.c -o display.o $(shell pkg-config allegro-5 allegro_font-5 allegro_image-5 --libs --cflags)

music.o: music.c music.h
	$(CC) $(cflags) -c music.c -o music.o $(shell pkg-config allegro-5 allegro_acodec-5 allegro_audio-5 --libs --cflags)

player.o: player.c player.h
	$(CC) $(cflags) -c player.c -o player.o $(shell pkg-config allegro-5 allegro_font-5 allegro_image-5 --libs --cflags)

utils.o: utils.c utils.h
	$(CC) $(cflags) -c utils.c -o utils.o

clean:
	rm -rf *.o