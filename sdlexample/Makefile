LDFLAGS:= -lSDL2
CFLAGS:= -I/usr/local/include/sdl2
CC := g++ 


all:	sdlexample


sdlexample:	sdlexample.cpp
	$(CC) $(CFLAGS) $(LDFLAGS) sdlexample.cpp -o sdlexample

clean:
	rm sdlexample

