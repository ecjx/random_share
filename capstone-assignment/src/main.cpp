#include "transaction.h"
#include <fstream>
#include <iostream>
#include <algorithm>

int main()
{
    std::ifstream file("transactions.csv");
    if (!file.is_open()) {
        std::cerr << "Could not open file transactions.csv\n";
        file.open("../transactions.csv");
        if (!file.is_open()) {
            std::cerr << "Could not open file transactions.csv\n";
            return 1;
        }
    }

    std::vector<std::pair<uint32_t,Transaction>> transactions;
    std::vector<std::pair<uint32_t,std::string>> errors;
    std::string line;

    for(uint32_t i = 0; std::getline(file, line); ++i) {
        if(i != 0)
        {
            auto result = Transaction::from_csv_line(line);
            if (result.success_) {
                transactions.push_back(std::make_pair(i,std::get<Transaction>(std::move(result.result_))));
            } else {
                errors.push_back(std::make_pair(i,std::move(std::get<std::string>(result.result_))));
            }
        }
    }

    std::cout << "--- Printing Transactions ---\n";
    for(int i = 0; i < transactions.size(); ++i)
    {
        std::cout << "--- Field " << transactions[i].first << " ---\n";
        std::cout << transactions[i].second << '\n';
    }

    std::cout << "\n--- Printing Errors ---\n";

    for(int i = 0; i < errors.size(); ++i)
    {
        std::cout << "--- Field " << errors[i].first << " ---\n";
        std::cout << "Error Message -> "<< errors[i].second << '\n';
    }

    const auto transform = [](const std::pair<uint32_t,Transaction>& t) {
        return t.second;
    };

    std::vector<Transaction> transactions_only;
    std::transform(transactions.begin(), transactions.end(), std::back_inserter(transactions_only), transform);

    std::cout << "\n--- Printing Total invested per continent ---\n";
    Transaction::print_total_invested_per_continent(std::cout, transactions_only);

    std::cout << "\n--- Printing Companies In Europe ---\n";
    Transaction::print_asset_from_continent(std::cout, transactions_only, Location::Continent::Europe);

    return 0;
}