

#[derive(Debug, PartialEq)]
//enum for country
pub enum Country
{
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
}


#[derive(Debug, PartialEq)]
//enum for continent
pub enum Continent
{
    NorthAmerica,
    SouthAmerica,
    Europe,
    Asia,
    Africa,
    Oceania
}

impl Continent
{
    //converts continent to string
    pub fn to_string(&self) -> String
    {
        match self
        {
            Continent::NorthAmerica => "North America".to_string(),
            Continent::SouthAmerica => "South America".to_string(),
            Continent::Europe => "Europe".to_string(),
            Continent::Asia => "Asia".to_string(),
            Continent::Africa => "Africa".to_string(),
            Continent::Oceania => "Oceania".to_string()
        }
    }
}

impl Country
{
    //converts country to continent
    pub fn country_to_continent(&self) -> Continent{
        match self{
            Country::UnitedStates => Continent::NorthAmerica,
            Country::Canada => Continent::NorthAmerica,
            Country::UnitedKingdom => Continent::Europe,
            Country::Germany => Continent::Europe,
            Country::France => Continent::Europe,
            Country::Japan => Continent::Asia,
            Country::Australia => Continent::Oceania,
            Country::China => Continent::Asia,
            Country::Brazil => Continent::SouthAmerica,
            Country::SouthKorea => Continent::Asia,
            Country::Ireland => Continent::Europe,
            Country::Spain => Continent::Europe,
            Country::India => Continent::Asia,
            Country::Switzerland => Continent::Europe
        }
    }
    //converts country to string
    pub fn to_string(&self) -> String
    {
        match self
        {
            Country::UnitedStates => "United States".to_string(),
            Country::Canada => "Canada".to_string(),
            Country::UnitedKingdom => "United Kingdom".to_string(),
            Country::Germany => "Germany".to_string(),
            Country::France => "France".to_string(),
            Country::Japan => "Japan".to_string(),
            Country::Australia => "Australia".to_string(),
            Country::China => "China".to_string(),
            Country::Brazil => "Brazil".to_string(),
            Country::SouthKorea => "South Korea".to_string(),
            Country::Ireland => "Ireland".to_string(),
            Country::Spain => "Spain".to_string(),
            Country::India => "India".to_string(),
            Country::Switzerland => "Switzerland".to_string()
        }
    }
}

//converts string to country
impl std::str::FromStr for Country{
    type Err = &'static str;
    fn from_str(s: &str) -> Result<Self, Self::Err>
    {
        match s
        {
            "USA" => Ok(Country::UnitedStates),
            "Canada" => Ok(Country::Canada),
            "UK" => Ok(Country::UnitedKingdom),
            "Germany" => Ok(Country::Germany),
            "France" => Ok(Country::France),
            "Japan" => Ok(Country::Japan),
            "Australia" => Ok(Country::Australia),
            "China" => Ok(Country::China),
            "Brazil" => Ok(Country::Brazil),
            "South Korea" => Ok(Country::SouthKorea),
            "Ireland" => Ok(Country::Ireland),
            "Spain" => Ok(Country::Spain),
            "India" => Ok(Country::India),
            "Switzerland" => Ok(Country::Switzerland),
            _ => Err("Invalid country name!")
        }
    }
}