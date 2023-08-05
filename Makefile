files = src/*.c

main: $(files)
	gcc -o $@ $(files) -Wall -lraylib -lGL -lm -pthread -ldl

clean:
	rm main
