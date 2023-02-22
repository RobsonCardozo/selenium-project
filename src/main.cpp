#include <iostream>
#include <curl/curl.h>
#include "dotenv.hpp"

static size_t WriteCallback(void *contents, size_t size, size_t nmemb, void *userp)
{
    ((std::string*)userp)->append((char*)contents, size * nmemb);
    return size * nmemb;
}

int main() {
    // Load the environment variables from the .env file
    dotenv::load();

    // Get the API key from the environment variables
    std::string api_key = dotenv::get("NEWS_API_KEY");

    // Build the API URL
    std::string url = "https://newsapi.org/v2/top-headlines?country=us&apiKey=" + api_key;

    // Initialize curl
    CURL *curl;
    CURLcode res;
    std::string readBuffer;

    curl = curl_easy_init();
    if(curl) {
        // Set the API URL
        curl_easy_setopt(curl, CURLOPT_URL, url.c_str());

        // Set the callback function to receive the response
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &readBuffer);

        // Send the request
        res = curl_easy_perform(curl);

        // Check for errors
        if(res != CURLE_OK) {
            std::cerr << "curl_easy_perform() failed: " << curl_easy_strerror(res) << std::endl;
        }

        // Cleanup curl
        curl_easy_cleanup(curl);
    }

    // Output the response
    std::cout << readBuffer << std::endl;

    return 0;
}
