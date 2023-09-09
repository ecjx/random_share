#ifndef LOCATION_H
#define LOCATION_H
#include <string>
#include <string_view>

struct Location
{
    enum Country
    {
        UnknownCountry,
        UnitedStates,
        Canada,
        UnitedKingdom,
        Germany,
        France,
        Japan,
        Australia,
        China,
        Brazil,
        SouthKorea,
        Ireland,
        Spain,
        India,
        Switzerland
    };

    enum Continent
    {
        UnknownContinent,
        NorthAmerica,
        SouthAmerica,
        Europe,
        Asia,
        Africa,
        Oceania
    };

    static std::string to_string(Country country);
    static Country from_string(std::string_view str);
    static std::string to_string(Continent continent);
    static Continent country_to_continent(Country country);
    static std::string continent_to_string(Continent continent);
};

#endif // LOCATION_H