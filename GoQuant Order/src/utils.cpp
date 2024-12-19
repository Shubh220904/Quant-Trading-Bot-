#include <iostream>
#include <curl/curl.h>
#include <json/json.h>
#include "utils.h"

std::string authenticate(const std::string& client_id, const std::string& client_secret) {
    CURL* curl = curl_easy_init();
    if (!curl) throw std::runtime_error("Failed to initialize cURL");

    std::string url = "https://test.deribit.com/api/v2/public/auth";
    url += "?client_id=" + client_id + "&client_secret=" + client_secret + "&grant_type=client_credentials";

    curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
    curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1L);

    std::string response;
    auto write_callback = [](char* ptr, size_t size, size_t nmemb, void* userdata) -> size_t {
        ((std::string*)userdata)->append(ptr, size * nmemb);
        return size * nmemb;
    };

    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_callback);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response);

    CURLcode res = curl_easy_perform(curl);
    if (res != CURLE_OK) throw std::runtime_error("cURL request failed");

    curl_easy_cleanup(curl);

    Json::Reader reader;
    Json::Value json;
    reader.parse(response, json);

    if (!json.isMember("result")) throw std::runtime_error("Invalid authentication response");

    return json["result"]["access_token"].asString();
}
