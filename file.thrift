#!/usr/local/bin/thrift --gen cpp

namespace cpp Test

struct Url_req {
	1: string  url,
	2: i32   force
}

service Webcache {
	i32 ping(),
	
	string status(),

	string request(1: Url_req req)
}
