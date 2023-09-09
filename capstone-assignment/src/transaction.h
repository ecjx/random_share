#ifndef TRANSACTION_H
#define TRANSACTION_H

#include "location.h"
#include <string>
#include <variant>
#include <vector>
#include <iostream>

struct TransactionResult;

class Transaction
{
public:
    uint32_t id_;
    uint32_t clientId_;
    std::string assetName_;
    Location::Country country_;
    Location::Continent continent_;
    double amount_;
    uint64_t daysUnderManagement_;

    static TransactionResult from_csv_line(std::string_view line);
    static std::ostream& print_total_invested_per_continent(std::ostream& os, const std::vector<Transaction>& transactions);
    static std::ostream& print_asset_from_continent(std::ostream& os, const std::vector<Transaction>& transactions, Location::Continent continent);

};

std::ostream& operator<<(std::ostream& os, const Transaction& transaction);

struct TransactionResult
{
    std::variant<std::string,Transaction> result_;
    uint32_t success_;
};

#endif // TRANSACTION_H