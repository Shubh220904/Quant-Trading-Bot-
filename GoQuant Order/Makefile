# CXX = g++
# CXXFLAGS = -std=c++17 -Wall -Iinclude

# LIBS = -lcurl -lboost_system -lpthread -ljsoncpp

# SRC = src/main.cpp src/utils.cpp src/order_management.cpp src/websocket_server.cpp
# OBJ = $(SRC:.cpp=.o)

# all: order_execution_system

# order_execution_system: $(OBJ)
# 	$(CXX) $(CXXFLAGS) -o $@ $^ $(LIBS)

# clean:
# 	rm -f $(OBJ) order_execution_system
CXX = g++                             # Compiler to use
CXXFLAGS = -std=c++17 -Wall -Iinclude -I/D/websocketpp  # Added -I for websocketpp directory

LIBS = -lcurl -lboost_system -lpthread -ljsoncpp -lssl -lcrypto  # Added OpenSSL libraries if needed

SRC = src/main.cpp src/utils.cpp src/order_management.cpp src/websocket_server.cpp
OBJ = $(SRC:.cpp=.o)

all: order_execution_system

order_execution_system: $(OBJ)
	$(CXX) $(CXXFLAGS) -o $@ $^ $(LIBS)

clean:
	rm -f $(OBJ) order_execution_system
