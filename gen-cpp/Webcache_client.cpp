#include "Webcache.h"  // As an example

#include <fstream>

#include <transport/TSocket.h>
#include <transport/TBufferTransports.h>
#include <protocol/TBinaryProtocol.h>

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define NUM_REQUESTS	100

using namespace apache::thrift;
using namespace apache::thrift::protocol;
using namespace apache::thrift::transport;

using namespace Test;
using namespace std;

ifstream in_file;
Url_req   request;


void loadmode1( WebcacheClient *client ) {
	string line;
	string _return;
	int i = 0;
	
	struct timespec ts0,ts1;
	long elapsed;
	
	while ( i < NUM_REQUESTS ) {
		while (getline(in_file, line)){
			request.url = line;
			clock_gettime(CLOCK_REALTIME, &ts0);
			
			client->request(_return, request);
			
			clock_gettime(CLOCK_REALTIME, &ts1);
			elapsed = (ts1.tv_nsec-ts0.tv_nsec)+((ts1.tv_sec-ts0.tv_sec)*1000000000);
			//should probably dump to a file instead?
			//cout << _return << endl;
			//cout << "Page " << request.url << " of size " << _return.size() << " returned in " << elapsed << " ns" << endl;
			cout << request.url << ", " << _return.size() << ", " << elapsed << endl;
			
			i++;
			sleep(1); // To prevent sending too many requests to a site too quickly
		}
		
		// Return to beginning of file
		in_file.clear();
		in_file.seekg(0, in_file.beg);
	}
}

void loadmode2( WebcacheClient *client ) {
	string _return;
	Url_req request;
	int r,i;

	struct timespec ts0,ts1;
	long elapsed;

	//puting addresses in vector, so can access in non-sequential order
	vector<string> addresses;
	string line;
	while (getline(in_file, line)){
		addresses.push_back(line);
	}
	
	for( i=0; i < NUM_REQUESTS; i++ ) {
		r = rand() % addresses.size();
		request.url = addresses[r];
		
		clock_gettime(CLOCK_REALTIME, &ts0);
				
		client->request(_return, request);
		
		clock_gettime(CLOCK_REALTIME, &ts1);
		elapsed = (ts1.tv_nsec-ts0.tv_nsec)+((ts1.tv_sec-ts0.tv_sec)*1000000000);
		//cout << "Page " << request.url << " of size " << _return.size() << " returned in " << elapsed << " ns" << endl;
		cout << request.url << ", " << _return.size() << ", " << elapsed << endl;
		
		sleep(1); // To prevent sending too many requests to a site too quickly
	}

}

int main(int argc, char **argv) {

	string    _return;
	string	  ip_addr;
	int       mode = 0;
	int       ret = 0;
	
	struct timespec ts0,ts1;
	long elapsed;

	if( argc == 2 ) {
		request.url = argv[1];
		ip_addr = "localhost";
		mode = 1;
	}
	else if( argc == 3 || argc == 4 ) {
		// Open file and pick load mode
		in_file.open(argv[1]);
		if ( in_file.fail() ) {
			printf("File failed to open!\n");
			return 0;
		}
		if(atoi(argv[2]) == 0) {
			printf("Invalid mode given!\n");
			return 0;
		}
		mode = 2 + atoi(argv[2]);
		
		ip_addr = argc == 4 ? argv[3] : "localhost";
	}
	else {
		printf("Usage: Webcache_client [web_address] | [address_file load_mode ip_addr]\nPinging\n");
		mode = 0;
	}

	boost::shared_ptr<TSocket> socket(new TSocket(ip_addr, 9090));
	boost::shared_ptr<TTransport> transport(new TBufferedTransport(socket));
	boost::shared_ptr<TProtocol> protocol(new TBinaryProtocol(transport));

	WebcacheClient client(protocol);
	transport->open();
	switch (mode) {
	case 0 :
		ret = client.ping();
		printf("ping returned: %d\n",ret);
		break;
	case 1 :
		cout << "requesting single page!" << endl;
		clock_gettime(CLOCK_REALTIME, &ts0);
				
		client.request(_return, request);
		
		clock_gettime(CLOCK_REALTIME, &ts1);
		elapsed = (ts1.tv_nsec-ts0.tv_nsec)+((ts1.tv_sec-ts0.tv_sec)*1000000000);
		cout << _return << endl;
		cout << "Page " << request.url << " of size " << _return.size() << " returned in " << elapsed << " ns" << endl;
		break;
	case 3 :
		loadmode1( &client );
		break;
	case 4 :
		loadmode2( &client );
		break;
	default :
		printf("INVALID MODE\n");
	}
	transport->close();

  return 0;
}
