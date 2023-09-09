#include "location.h"

std::string Location::to_string(Location::Country country)
{
    switch (country)
    {
        case Country::UnitedStates:
            return "UnitedStates";
        case Country::Canada:
            return "Canada";
        case Country::UnitedKingdom:
            return "UnitedKingdom";
        case Country::Germany:
            return "Germany";
        case Country::France:
            return "France";
        case Country::Japan:
            return "Japan";
        case Country::Australia:
            return "Australia";
        case Country::China:
            return "China";
        case Country::Brazil:
            return "Brazil";
        case Country::SouthKorea:
            return "South Korea";
        case Country::Ireland:
            return "Ireland";
        case Country::Spain:
            return "Spain";
        case Country::India:
            return "India";
        case Country::Switzerland:
            return "Switzerland";
        default:
            return "UnknownCountry";
    }
}

std::string Location::to_string(Location::Continent continent)
{
    switch (continent)
    {
        case Continent::NorthAmerica:
            return "North America";
        case Continent::SouthAmerica:
            return "South America";
        case Continent::Europe:
            return "Europe";
        case Continent::Asia:
            return "Asia";
        case Continent::Africa:
            return "Africa";
        case Continent::Oceania:
            return "Oceania";
        default:
            return "UnknownContinent";
    }
}

Location::Country Location::from_string(std::string_view str)
{
    if (str == "UnitedStates" || str == "United States" || str == "USA")
        return Country::UnitedStates;
    else if (str == "Canada")
        return Country::Canada;
    else if (str == "UnitedKingdom" || str == "United Kingdom" || str == "UK")
        return Country::UnitedKingdom;
    else if (str == "Germany")
        return Country::Germany;
    else if (str == "France")
        return Country::France;
    else if (str == "Japan")
        return Country::Japan;
    else if (str == "Australia")
        return Country::Australia;
    else if (str == "China")
        return Country::China;
    else if (str == "Brazil")
        return Country::Brazil;
    else if (str == "SouthKorea" || str == "South Korea")
        return Country::SouthKorea;
    else if (str == "Ireland")
        return Country::Ireland;
    else if (str == "Spain")
        return Country::Spain;
    else if (str == "India")
        return Country::India;
    else if (str == "Switzerland")
        return Country::Switzerland;
    else
        return Country::UnknownCountry;
}

Location::Continent Location::country_to_continent(Location::Country country)
{
    switch (country)
    {
        case Country::UnitedStates:
        case Country::Canada:
            return Continent::NorthAmerica;
        case Country::UnitedKingdom:
        case Country::Germany:
        case Country::France:
        case Country::Ireland:
        case Country::Spain:
        case Country::Switzerland:
            return Continent::Europe;
        case Country::Japan:
        case Country::China:
        case Country::SouthKorea:
        case Country::India:
            return Continent::Asia;
        case Country::Australia:
            return Continent::Oceania;
        case Country::Brazil:
            return Continent::SouthAmerica;
        default:
            return Continent::UnknownContinent;
    }
}

std::string Location::continent_to_string(Location::Continent continent)
{
    switch (continent)
    {
        case Continent::NorthAmerica:
            return "NorthAmerica";
        case Continent::SouthAmerica:
            return "SouthAmerica";
        case Continent::Europe:
            return "Europe";
        case Continent::Asia:
            return "Asia";
        case Continent::Africa:
            return "Africa";
        case Continent::Oceania:
            return "Oceania";
        default:
            return "Unknown";
    }
}