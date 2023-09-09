use crate::location::{Country, Continent};

use std::collections::HashMap;
use chrono::NaiveDate;

#[derive(Debug)]
//struct for transaction
pub struct Transaction {
    transaction_id: u32,
    client_id: u32,
    pub asset_name: String,
    pub country: Country,
    continent: Continent,
    amount: f64,
    days_under_management: i64
}

impl Transaction
{
    //prints total invested per continent
    pub fn print_total_invested_per_continent(transactions : &Vec<Transaction>){
        let mut total_invested_per_continent: HashMap<String, f64> = HashMap::new();
        for transaction in transactions.iter(){
            let continent = transaction.continent.to_string();
            let amount = transaction.amount;
            total_invested_per_continent.entry(continent).and_modify(|data: &mut f64| *data +=  amount).or_insert(amount);
        }
        println!("\nTotal invested per continent: {:?}", total_invested_per_continent);
    }

    //converts csv line to transaction
    pub fn from_csv_line(line : &str) -> Result<Transaction,String>{
        let fields_vec: Vec<_> = line.split(",").collect();

        if fields_vec.len() != 7 {
            println!("Invalid number of fields");
            return Err("Invalid number of fields".to_string())?;
        }
        
        let mut fields = fields_vec.iter();
        let transaction_id = fields.next().ok_or("No transaction id")?.parse::<u32>().map_err(|_| "Invalid transaction id")?;
        let client_id = fields.next().ok_or("No client id")?.parse::<u32>().map_err(|_| "Invalid client id")?;
        let asset_name = fields.next().ok_or("No asset name")?.to_string().to_uppercase();

        let default = NaiveDate::from_ymd_opt(1970, 1, 1).ok_or("Invalid Default date".to_string())?; // default date (1970-01-01
        let transaction_start_date_string = fields.next().ok_or("No transaction end date")?.to_string();
        let transaction_start_date = NaiveDate::parse_from_str(&transaction_start_date_string, "%Y-%m-%d").unwrap_or(default);
        let transaction_end_date_string = fields.next().ok_or("No transaction end date")?.to_string();
        let transaction_end_date = NaiveDate::parse_from_str(&transaction_end_date_string, "%Y-%m-%d").unwrap_or(default);

        let country = fields.next().ok_or("No country")?.parse::<Country>().map_err(|_| "Invalid country")?;
        let amount = fields.next().ok_or("No amount")?.parse::<f64>().map_err(|_| "Invalid amount")?;

        let continent = country.country_to_continent();
        let days_under_management = (transaction_start_date - transaction_end_date).num_days().abs();

        return Ok(Transaction{
            transaction_id,
            client_id,
            asset_name,
            country,
            continent,
            amount,
            days_under_management
        })
    }
}