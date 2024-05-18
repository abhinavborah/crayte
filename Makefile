build:
	gcc -Wall -std=c99 ./src/*.c -o ./bin/crayte -I/opt/homebrew/include -L/opt/homebrew/lib -lSDL2 -lm
 
run:
	./bin/crayte

clean:
	rm ./bin/crayte
