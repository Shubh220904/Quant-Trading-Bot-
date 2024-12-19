#include "order_management.h"
#include <iostream>

int main() {
    std::string token;
    std::cout << "Enter your API token: ";
    std::cin >> token;

    while (true) {
        std::cout << "\nChoose an action:\n";
        std::cout << "1. Place Order\n";
        std::cout << "2. Cancel Order\n";
        std::cout << "3. Get Order Book\n";
        std::cout << "4. Exit\n";
        int choice;
        std::cin >> choice;

        if (choice == 1) {
            std::string instrument, type;
            double amount, price;

            std::cout << "Enter instrument name (e.g., BTC-PERPETUAL): ";
            std::cin >> instrument;

            std::cout << "Enter order type (buy/sell): ";
            std::cin >> type;

            std::cout << "Enter amount: ";
            std::cin >> amount;

            std::cout << "Enter price: ";
            std::cin >> price;

            if (!placeOrder(token, instrument, amount, price, type)) {
                std::cerr << "Failed to place order." << std::endl;
            }

        } else if (choice == 2) {
            std::string order_id;

            std::cout << "Enter order ID to cancel: ";
            std::cin >> order_id;

            if (!cancelOrder(token, order_id)) {
                std::cerr << "Failed to cancel order." << std::endl;
            }

        } else if (choice == 3) {
            std::string instrument;

            std::cout << "Enter instrument name to get order book (e.g., BTC-PERPETUAL): ";
            std::cin >> instrument;

            std::string orderBook = getOrderBook(instrument);
            if (!orderBook.empty()) {
                std::cout << "Order Book:\n" << orderBook << std::endl;
            } else {
                std::cerr << "Failed to retrieve order book." << std::endl;
            }

        } else if (choice == 4) {
            std::cout << "Exiting program." << std::endl;
            break;
        } else {
            std::cerr << "Invalid choice. Please try again." << std::endl;
        }
    }

    return 0;
}
