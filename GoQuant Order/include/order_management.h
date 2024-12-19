#ifndef ORDER_MANAGEMENT_H
#define ORDER_MANAGEMENT_H

#include <string>

bool placeOrder(const std::string& token, const std::string& instrument, double amount, double price, const std::string& type);
bool cancelOrder(const std::string& token, const std::string& order_id);
std::string getOrderBook(const std::string& instrument);

#endif // ORDER_MANAGEMENT_H
