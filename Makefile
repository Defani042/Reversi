Reversi: build/main.o build/gameWindow.o
	gcc -o Reversi  build/main.o build/gameWindow.o `pkg-config --libs-only-other --libs-only-L --libs-only-l MLV`

build/main.o: src/main.c src/gameWindow.h
	gcc -c -Wall -W -std=c89 -pedantic -O2 `pkg-config --cflags MLV` src/main.c -o build/main.o

build/gameWindow.o: src/gameWindow.c src/gameWindow.h
	gcc -c -Wall -W -std=c89 -pedantic -O2 `pkg-config --cflags MLV` src/gameWindow.c -o build/gameWindow.o

clean:
	rm -rf build/*.o *~ Reversi

