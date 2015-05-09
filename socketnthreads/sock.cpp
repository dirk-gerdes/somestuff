#include <iostream>

#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <netdb.h>
#include <thread>
#include <unistd.h>
#include <string.h>

using namespace std;

int sock;
char buffer[1024];


void receive()
{
	int k = recv( sock, buffer,1 , sizeof( buffer));
	cout << "recv -> " << k << endl;
}

int main()
{
	sockaddr_in addr;
	memset( &addr, 0, sizeof( addr));
	
	hostent *server = gethostbyname( "www.google.de");
	if( server == nullptr)
	{
		cout << "error" << endl;
		return -1;
	}
	bzero((char *) &addr, sizeof(addr));
	addr.sin_family = AF_INET;
	bcopy((char *)server->h_addr,
      	(char *)&addr.sin_addr.s_addr,
      	server->h_length);
	addr.sin_port = htons(80);
	sock = socket(AF_INET, SOCK_STREAM, 0);

	if( connect( sock, (sockaddr*)&addr, sizeof( addr)) <0)
	{
		return -1;
	}
	thread t( receive);

	cout << ".." << endl;

	sleep(1);
	close ( sock);
	cout << ".." << endl;
	t.join();
	cout << ".." << endl;

	cout << "done" << endl;

	return 0;
}
