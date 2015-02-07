#LDFLAGS:= -lboost_system -lboost_thread  -L/usr/local/lib
LDFLAGS:= -ldirectfb
CFLAGS:= -I/usr/local/include/directfb
CC := cc


all:	dft


dft:	directfbtest.c
	$(CC) $(CFLAGS) $(LDFLAGS) directfbtest.c -o dft

clean:
	rm dft 

#-I/usr/local/include/directfb -ldirectfb
