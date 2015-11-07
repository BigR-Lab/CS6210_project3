// This autogenerated skeleton file illustrates how to build a server.
// You should copy it to another filename to avoid overwriting it.

#include "Something.h"
#include <thrift/protocol/TBinaryProtocol.h>
#include <thrift/server/TSimpleServer.h>
#include <thrift/transport/TServerSocket.h>
#include <thrift/transport/TBufferTransports.h>

#include "Cache.h"
#include "Random.h"
#include "LRU.h"
#include "LRU_min.h"

#include <curl/curl.h>
#include <stdlib.h>
#include <stdio.h>

using namespace ::apache::thrift;
using namespace ::apache::thrift::protocol;
using namespace ::apache::thrift::transport;
using namespace ::apache::thrift::server;

using boost::shared_ptr;

using namespace  ::Test;
using namespace std;

string data;
string policy;
Cache* proxyCache;

size_t write_to_string(char *buf, size_t size, size_t count, void *stream) {
	for (unsigned int c = 0; c < size*count; c++){
		data.push_back(buf[c]);
	}
	return size*count;
}

class SomethingHandler : virtual public SomethingIf {
 public:
  SomethingHandler() {
    cout << "Caching Server Started with policy: "<< policy << "!" << endl;
  }

	int32_t ping() {
		// Your implementation goes here
		cout << "ping" << endl;

		return 1;
	}

	void request(string& _return, const Url_req& req) {
		
		CURL   *curl;
		string key, temp;
				
		temp = proxyCache->get(req.url);
		if( temp == "0" ) {
			curl = curl_easy_init();
			_return = "ERROR";
			
			cout << "URL Requested: " << req.url << "; miss in cache" << endl;
		
			if (curl) {
				curl_easy_setopt(curl, CURLOPT_URL, req.url.c_str());

				curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, &write_to_string);
				//curl_easy_setopt(curl, CURLOPT_WRITEDATA, &_return);

				curl_easy_perform(curl);
				
				printf("Retrieved site of size %d!\n",(int)data.size());
				_return = data;
				proxyCache->set(req.url, data);
			
				curl_easy_cleanup(curl);    					
				data.clear(); 
			} else {
				cout << "Failed to init curl!" << endl;
			}
		}
		else {
			cout << "URL Requested: " << req.url << "; hit in cache" << endl;
			_return = temp;
		}

	}

};

int main(int argc, char **argv) {
  
  int cacheSize;
  int port = 9090;
  if (argc == 3){
    policy = argv[1];
    cacheSize = atoi(argv[2]);
  }
  else{
    policy = "Random";
	cacheSize = 0;
  }
  if (policy == "Random"){		
    proxyCache = new Random(cacheSize);
  }
  if (policy == "LRU"){		
    proxyCache = new Lru(cacheSize);
  }
  if (policy == "LRU_min"){		
    proxyCache = new Lrum(cacheSize);
  }

  shared_ptr<SomethingHandler> handler(new SomethingHandler());
  shared_ptr<TProcessor> processor(new SomethingProcessor(handler));
  shared_ptr<TServerTransport> serverTransport(new TServerSocket(port));
  shared_ptr<TTransportFactory> transportFactory(new TBufferedTransportFactory());
  shared_ptr<TProtocolFactory> protocolFactory(new TBinaryProtocolFactory());

  TSimpleServer server(processor, serverTransport, transportFactory, protocolFactory);
  server.serve();
  return 0;
}

