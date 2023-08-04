files = src/main.c src/menu.c

main: $(files)
	gcc -o $@ $(files) -Wall -lraylib -lGL -lm -pthread -ldl
