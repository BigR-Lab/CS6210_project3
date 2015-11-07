GEN_SRC := Webcache.cpp file_constants.cpp file_types.cpp Random.cpp LRU.cpp LRU_min.cpp ll.cpp
GEN_OBJ := $(patsubst %.cpp,%.o, $(GEN_SRC))

THRIFT_DIR := /usr/local/include/thrift
BOOST_DIR := /usr/include

INC := -I$(THRIFT_DIR) -I$(BOOST_DIR)

.PHONY: all clean

all: Webcache_server Webcache_client

%.o: %.cpp
		$(CXX) -Wall -DHAVE_INTTYPES_H -DHAVE_NETINET_IN_H $(INC) -c $< -o $@

Webcache_server: Webcache_server.o $(GEN_OBJ)
		$(CXX) $^ -o $@ -L/usr/local/lib -lthrift -lcurl 

Webcache_client: Webcache_client.o $(GEN_OBJ)
		$(CXX) $^ -o $@ -L/usr/local/lib -lthrift 

clean:
		$(RM) *.o Webcache_server Webcache_client
