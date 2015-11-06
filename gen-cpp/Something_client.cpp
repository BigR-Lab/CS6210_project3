#include "Something.h"  // As an example


#include <transport/TSocket.h>
#include <transport/TBufferTransports.h>
#include <protocol/TBinaryProtocol.h>

#include <stdio.h>
#include <stdlib.h>

using namespace apache::thrift;
using namespace apache::thrift::protocol;
using namespace apache::thrift::transport;

using namespace Test;
using namespace std;

void loadmode1( SomethingClient *client, FILE *fp ) {

}

void loadmode2( SomethingClient *client, FILE *fp ) {

}

int main(int argc, char **argv) {

	Url_req   request;
	FILE      *fp;
	string    _return;
	int       mode = 0;
	int       ret = 0;

	if( argc == 2 ) {
		request.url = argv[1];
		mode = 1;
	}
	else if( argc == 3 ) {
		// Open file and pick load mode
		fp = fopen (argv[1],"r");
		if ( fp == NULL ) {
			printf("File failed to open!\n");
			return 0;
		}
		if(atoi(argv[2]) == 0) {
			printf("Invalid mode given!\n");
			return 0;
		}
		mode = 2 + atoi(argv[2]);
		
	}
	else {
		printf("Usage: something_client [web_address] | [address_file load_mode]\nPinging\n");
		mode = 0;
	}

	boost::shared_ptr<TSocket> socket(new TSocket("localhost", 9090));
	boost::shared_ptr<TTransport> transport(new TBufferedTransport(socket));
	boost::shared_ptr<TProtocol> protocol(new TBinaryProtocol(transport));

	SomethingClient client(protocol);
	transport->open();
	switch (mode) {
	case 0 :
		ret = client.ping();
		printf("ping returned: %d\n",ret);
		break;
	case 1 :
		printf("requesting single page!\n");
		client.request(_return, request);
		cout << _return << endl;
		break;
	case 3 :
		loadmode1( &client, fp );
		break;
	case 4 :
		loadmode2( &client, fp );
		break;
	default :
		printf("INVALID MODE\n");
	}
	transport->close();

  return 0;
}
