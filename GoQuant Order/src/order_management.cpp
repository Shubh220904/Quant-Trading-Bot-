#include "order_management.h"
#include <iostream>
#include <curl/curl.h>
#include <json/json.h>

// Helper function to handle HTTP responses
static size_t writeCallback(void* contents, size_t size, size_t nmemb, std::string* output) {
    size_t totalSize = size * nmemb;
    if (output) {
        output->append((char*)contents, totalSize);
    }
    return totalSize;
}

// Place an order
bool placeOrder(const std::string& token, const std::string& instrument, double amount, double price, const std::string& type) {
    CURL* curl = curl_easy_init();
    if (!curl) {
        std::cerr << "Failed to initialize cURL." << std::endl;
        return false;
    }

    std::string url = "https://test.deribit.com/api/v2/private/" + type;
    std::string postFields = "instrument_name=" + instrument + "&amount=" + std::to_string(amount) + "&price=" + std::to_string(price);

    struct curl_slist* headers = NULL;
    headers = curl_slist_append(headers, ("Authorization: Bearer " + token).c_str());
    
    curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
    curl_easy_setopt(curl, CURLOPT_POSTFIELDS, postFields.c_str());
    curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);

    std::string response;
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, writeCallback);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response);

    CURLcode res = curl_easy_perform(curl);
    curl_easy_cleanup(curl);
    curl_slist_free_all(headers);

    if (res != CURLE_OK) {
        std::cerr << "cURL error: " << curl_easy_strerror(res) << std::endl;
        return false;
    }

    Json::Value jsonResponse;
    Json::Reader reader;
    if (!reader.parse(response, jsonResponse)) {
        std::cerr << "Failed to parse response: " << response << std::endl;
        return false;
    }

    if (jsonResponse.isMember("error")) {
        std::cerr << "Error placing order: " << jsonResponse["error"].toStyledString() << std::endl;
        return false;
    }

    std::cout << "Order placed successfully: " << jsonResponse.toStyledString() << std::endl;
    return true;
}

// Cancel an order
bool cancelOrder(const std::string& token, const std::string& order_id) {
    CURL* curl = curl_easy_init();
    if (!curl) {
        std::cerr << "Failed to initialize cURL." << std::endl;
        return false;
    }

    std::string url = "https://test.deribit.com/api/v2/private/cancel";
    std::string postFields = "order_id=" + order_id;

    struct curl_slist* headers = NULL;
    headers = curl_slist_append(headers, ("Authorization: Bearer " + token).c_str());

    curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
    curl_easy_setopt(curl, CURLOPT_POSTFIELDS, postFields.c_str());
    curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);

    std::string response;
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, writeCallback);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response);

    CURLcode res = curl_easy_perform(curl);
    curl_easy_cleanup(curl);
    curl_slist_free_all(headers);

    if (res != CURLE_OK) {
        std::cerr << "cURL error: " << curl_easy_strerror(res) << std::endl;
        return false;
    }

    Json::Value jsonResponse;
    Json::Reader reader;
    if (!reader.parse(response, jsonResponse)) {
        std::cerr << "Failed to parse response: " << response << std::endl;
        return false;
    }

    if (jsonResponse.isMember("error")) {
        std::cerr << "Error canceling order: " << jsonResponse["error"].toStyledString() << std::endl;
        return false;
    }

    std::cout << "Order canceled successfully: " << jsonResponse.toStyledString() << std::endl;
    return true;
}

// Get order book
std::string getOrderBook(const std::string& instrument) {
    CURL* curl = curl_easy_init();
    if (!curl) {
        std::cerr << "Failed to initialize cURL." << std::endl;
        return "";
    }

    std::string url = "https://test.deribit.com/api/v2/public/get_order_book?instrument_name=" + instrument;

    curl_easy_setopt(curl, CURLOPT_URL, url.c_str());

    std::string response;
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, writeCallback);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response);

    CURLcode res = curl_easy_perform(curl);
    curl_easy_cleanup(curl);

    if (res != CURLE_OK) {
        std::cerr << "cURL error: " << curl_easy_strerror(res) << std::endl;
        return "";
    }

    Json::Value jsonResponse;
    Json::Reader reader;
    if (!reader.parse(response, jsonResponse)) {
        std::cerr << "Failed to parse response: " << response << std::endl;
        return "";
    }

    if (jsonResponse.isMember("error")) {
        std::cerr << "Error retrieving order book: " << jsonResponse["error"].toStyledString() << std::endl;
        return "";
    }

    return jsonResponse.toStyledString();
}
