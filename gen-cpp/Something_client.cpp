#include "Something.h"  // As an example


#include <transport/TSocket.h>
#include <transport/TBufferTransports.h>
#include <protocol/TBinaryProtocol.h>

using namespace apache::thrift;
using namespace apache::thrift::protocol;
using namespace apache::thrift::transport;

using namespace Test;
using namespace std;

int main(int argc, char **argv) {

	Url_req   request;
	string    _return;
	int       mode = 0;
	int       ret = 0;

	if( argc == 2 ) {
		request.url = argv[1];
		mode = 1;
	}
	else {
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
		client.request(_return, request);
		cout << _return << endl;
		break;
	default :
		printf("INVALID MODE\n");
	}
	transport->close();

  return 0;
}
