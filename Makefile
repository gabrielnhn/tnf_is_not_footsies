allegro_test:
	gcc allegro_test.c -o allegro_test $(pkg-config allegro-5 allegro_font-5 --libs --cflags) 

main: main.c music.c display.c
	gcc main.c -o main $(shell pkg-config allegro-5 allegro_font-5 allegro_image-5 allegro_acodec-5 allegro_audio-5 --libs --cflags)