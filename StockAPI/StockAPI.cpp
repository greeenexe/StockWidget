// StockAPI.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <string>

#define CPPHTTPLIB_OPENSSL_SUPPORT
#include "httplib.h"
#include "json.hpp"
#include <algorithm>

using json = nlohmann::json;

int main()
{

    //Prompt user
    std::cout << "Type a ticker...(ex: AMZN, AAPL, NVDA...)\n";

    while (true) {
        std::string ticker_input;
        std::cin >> ticker_input;
        std::string API_KEY = "REPLACEME";

        // Initializing the SSL Client
        httplib::Client cli("https://api.polygon.io");

        cli.set_connection_timeout(5);

        std::string path = "/v1/open-close/" + ticker_input + "/2025-10-14?adjusted=true&apiKey=" + API_KEY;


        auto res = cli.Get(path);
        //std::cout << "\nResponse Body:\n" << res->body.substr(0, 500) << "..." << std::endl;


        //parsing json
        json response_data = json::parse(res->body);

        double closing_price = response_data["close"].get<double>();
        std::cout << "The closing price for " << response_data["symbol"].get<std::string>() << " was: $" << closing_price << std::endl;
        std::cout << "VOLUME: " << response_data["volume"].get<double>();
        std::cout << std::endl;
        std::cout << std::endl;
        std::cout << std::endl;
        std::cout << std::endl;

        std::cout << "-------------------------------------------------------------------------------------------\n";
        std::cout << "Type in next stock ticker symbol: \n";
    }
    return 0;
}
