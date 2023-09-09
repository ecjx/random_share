
use crate::location::Continent;
use crate::transaction::Transaction;

//prints companies from continent
pub fn print_companies_from_continent(transactions : &Vec<Transaction>, continent: &Continent)
{
    let mut companies: Vec<String> = Vec::new();

    for transaction in transactions
    {
        if transaction.country.country_to_continent() == *continent
        {
            companies.push(transaction.asset_name.clone());
        }
    }
    companies.sort();
    companies.dedup();

    println!("{:?}", companies);
}

