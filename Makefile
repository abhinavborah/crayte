build:
	gcc -F/Library/Frameworks -framework SDL2 -rpath /Library/Frameworks/ -Wall -std=c99 ./src/*.c -o ./bin/crayte

run:
	./bin/crayte

clean:
	rm ./bin/crayte
