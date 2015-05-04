#LDFLAGS:= -lboost_system -lboost_thread  -L/usr/local/lib
LDFLAGS:= 
#-ldirectfb
CFLAGS:= 
#-I/usr/local/include/directfb
CC := g++ 


all:	sock	


sock:	sock.cpp
	$(CC) $(CFLAGS) $(LDFLAGS) sock.cpp -o sock

clean:
	rm sock 

