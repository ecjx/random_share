#include "transaction.h"
#include "utils.h"
#include <ranges>
#include <charconv>
#include <concepts>
#include <string>
#include <unordered_set>
#include <unordered_map>

std::ostream& operator<<(std::ostream& os, const Transaction& transaction)
{
    os << "Transaction id: " << transaction.id_ << '\n';
    os << "Client id: " << transaction.clientId_ << '\n';
    os << "Asset name: " << transaction.assetName_ << '\n';
    os << "Country: " << Location::to_string(transaction.country_) << '\n';
    os << "Continent: " << Location::to_string(transaction.continent_) << '\n';
    os << "Amount: " << transaction.amount_ << '\n';
    os << "Days under management: " << transaction.daysUnderManagement_ << '\n';
    return os;
}

TransactionResult Transaction::from_csv_line(std::string_view line)
{
    auto fields = std::ranges::views::split(line, ',') 
    | std::ranges::views::transform([](auto&& rng) ->std::string_view {
        return std::string_view(rng.begin(), rng.end());
    });

    if (std::ranges::distance(fields) != 7)
        return { .result_ = "Invalid number of fields", .success_ = 0 };
    

    std::vector<std::string_view> fields_vec = { fields.begin(), fields.end() };

    Transaction transaction;
    std::from_chars_result result = std::from_chars(fields_vec[0].data(), fields_vec[0].data() + fields_vec[0].size(), transaction.id_);
    if (result.ec != std::errc())
        return { .result_ = "Invalid id", .success_ = 0 };
    

    result = std::from_chars(fields_vec[1].data(), fields_vec[1].data() + fields_vec[1].size(), transaction.clientId_);
    if (result.ec != std::errc())
        return { .result_ = "Invalid client id", .success_ = 0 };
    

    transaction.assetName_ = std::string(fields_vec[2]);

    if(transaction.assetName_.empty())
        return { .result_ = "Invalid asset name", .success_ = 0 };
    
    const auto start_date = edwin_utils::parse_date(fields_vec[3]);
    const auto end_date = edwin_utils::parse_date(fields_vec[4]);

    if(start_date.tm_year == 0 || end_date.tm_year == 0)
        return { .result_ = "Invalid date format: yyyy-mm-dd", .success_ = 0 };
    
    transaction.daysUnderManagement_ = std::abs(edwin_utils::days_between(start_date, end_date));

    transaction.country_ = Location::from_string(fields_vec[5]);
    if(transaction.country_ == Location::Country::UnknownCountry)
        return { .result_ = "Invalid country", .success_ = 0 };
        
    transaction.continent_ = Location::country_to_continent(transaction.country_);

    bool success = false;
    transaction.amount_ = fields_vec[6].empty() ? 0.0 : edwin_utils::string_to<double>(fields_vec[6], success);

    if (!success)
        return { .result_ = "Invalid amount", .success_ = 0 };

    return { .result_ = std::move(transaction), .success_ = 1 };
}

std::ostream& Transaction::print_asset_from_continent(std::ostream& os, const std::vector<Transaction>& transactions, Location::Continent continent)
{
    auto continent_transactions = transactions | std::ranges::views::filter([continent](const Transaction& t) {
        return t.continent_ == continent;
    });

    if (std::ranges::empty(continent_transactions))
        return os << "No transactions from this continent\n";

    std::unordered_set<std::string_view> asset_set;

    for (const auto& t : continent_transactions)
        asset_set.insert(t.assetName_);

    for (const auto& asset : asset_set)
        os << asset << '\n';

    return os;
}

std::ostream& Transaction::print_total_invested_per_continent(std::ostream& os, const std::vector<Transaction>& transactions)
{
    std::unordered_map<Location::Continent, double> continent_map;

    for (const auto& t : transactions)
        continent_map[t.continent_] += t.amount_;

    for (const auto& [continent, amount] : continent_map)
        os << Location::continent_to_string(continent) << ": " << amount << '\n';

    return os;
}