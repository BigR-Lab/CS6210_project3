# CS6210_project3

----------------
Building
----------------

This project requires a number of tools to be installed on a unix machine to build.
Download and install apache thrift per the apache thrift documentation; this will
require a number of requisite packages as well. Also, using a package manager, get 
and install some version of libcurl-dev (such as libcurl-gnutls-dev).

Call

thrift --gen cpp file.thrift 

at the root directory to generate new source files.

Calling make within gen-cpp will make the application files.

----------------
Usage
----------------
The server must be run first, to do so, run the following command:

./Webcache_server [policy cache_size]

	The policy can be specified as "Random" "LRU" or "LRU_min"; the default is "Random"

	cache_size can be any number up to 2^31
	
The client can then be run with the following command:

./Webcache_client [web_address] | [address_file load_mode ip_addr]

	web_address is a single web address to be requested; server must be the localhost in this case
	
	address_file is a text file with websites to be accessed, each on its own line
	
	load_mode: 1 for looped linear in file, 2 for random
	
	ip_addr is the IP address of the server
	
----------------
Operation
----------------

Webcache_client will send either a single url request or 100 (if a single or file was given, respectively)
to webcache_server. Webcache_server will fetch the web page from either its cache or, if it
is not present in the cache, from the internet and return the contents as a string to Webcache_client.