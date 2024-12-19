#include "websocket_server.h"
#include <websocketpp/server.hpp>
#include <websocketpp/config/asio_no_tls.hpp>

typedef websocketpp::server<websocketpp::config::asio> server;

void runWebSocketServer() {
    server ws_server;

    // Set up handlers for connection, message, etc.
    ws_server.init_asio();
    ws_server.start_accept();

    ws_server.run();
}
