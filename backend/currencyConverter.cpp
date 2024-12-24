#include <iostream>
#include <string>
#include <map>
#include <cstdlib>

void printHTMLHeader() {
    std::cout << "Content-type: text/html\n\n";
    std::cout << "<!DOCTYPE html>\n";
    std::cout << "<html>\n<head>\n<title>Currency Converter</title>\n</head>\n<body>\n";
}

void printHTMLFooter() {
    std::cout << "</body>\n</html>\n";
}

int main() {
    printHTMLHeader();

    std::map<std::string, double> exchangeRates = {
        {"USD_TO_INR", 82.75},
        {"EUR_TO_INR", 89.34},
        {"GBP_TO_INR", 102.56}
    };

    const char* queryString = getenv("QUERY_STRING");
    if (queryString) {
        std::string query(queryString);
        std::string fromCurrency, toCurrency;
        double amount = 0.0;

        size_t fromPos = query.find("from=");
        size_t toPos = query.find("to=");
        size_t amountPos = query.find("amount=");

        if (fromPos != std::string::npos && toPos != std::string::npos && amountPos != std::string::npos) {
            fromCurrency = query.substr(fromPos + 5, toPos - fromPos - 6);
            toCurrency = query.substr(toPos + 3, amountPos - toPos - 4);
            amount = std::stod(query.substr(amountPos + 7));

            std::string key = fromCurrency + "_TO_" + toCurrency;

            if (exchangeRates.find(key) != exchangeRates.end()) {
                double convertedAmount = amount * exchangeRates[key];
                std::cout << "<h1>Converted Amount: " << convertedAmount << " " << toCurrency << "</h1>\n";
            } else {
                std::cout << "<h1>Error: Unsupported currency conversion.</h1>\n";
            }
        } else {
            std::cout << "<h1>Error: Invalid query string.</h1>\n";
        }
    } else {
        std::cout << "<h1>Error: No query string found.</h1>\n";
    }

    printHTMLFooter();
    return 0;
}