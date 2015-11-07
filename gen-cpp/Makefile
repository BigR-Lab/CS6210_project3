GEN_SRC := Something.cpp file_constants.cpp file_types.cpp Random.cpp LRU.cpp LRU_min.cpp ll.cpp
GEN_OBJ := $(patsubst %.cpp,%.o, $(GEN_SRC))

THRIFT_DIR := /usr/local/include/thrift
BOOST_DIR := /usr/include

INC := -I$(THRIFT_DIR) -I$(BOOST_DIR)

.PHONY: all clean

all: something_server something_client

%.o: %.cpp
		$(CXX) -Wall -DHAVE_INTTYPES_H -DHAVE_NETINET_IN_H $(INC) -c $< -o $@

something_server: Something_server.o $(GEN_OBJ)
		$(CXX) $^ -o $@ -L/usr/local/lib -lthrift -lcurl 

something_client: Something_client.o $(GEN_OBJ)
		$(CXX) $^ -o $@ -L/usr/local/lib -lthrift 

clean:
		$(RM) *.o something_server something_client
