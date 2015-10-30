# CS6210_project3

This project requires a number of tools to be installed on a unix machine to build.
Download and install apache thrift per the apache thrift documentation; this will
require a number of requisite packages as well. Also, using a package manager, get 
and install some version of libcurl-dev (such as libcurl-gnutls-dev).

Call

thrift --gen cpp file.thrift 

at the root directory to generate new source files.

Calling make within gen-cpp will make the application files.
