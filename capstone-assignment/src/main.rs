mod location;
use crate::location::Continent;

use std::fs::File;
use std::io::{BufRead, BufReader};

mod transaction;
use transaction::Transaction;
use utils::print_companies_from_continent;

mod utils;

fn main() {
    let file = File::open("transactions.csv").expect("Unable to open file");
    let reader = BufReader::new(file);

    let mut transactions: Vec<Transaction> = Vec::new();
    let mut err: Vec<(usize, String)> = Vec::new();

    for (i, line) in reader.lines().enumerate() {

        if i == 0 {
            continue;
        }

        let line_str = line.expect("Unable to read line");

        match Transaction::from_csv_line(&line_str)
        {
            Ok(t) => transactions.push(t),
            Err(error) => err.push((i, error))
        };
    }
    println!("\nPrinting Errors:\n");
    for (_i,data) in err.iter().enumerate(){
        println!("Error data line {} : {:?}",data.0 ,data.1);
    }
    println!("Total number of transactions: {}", transactions.len());
    println!("\nPrinting Transactions:\n");
    for (i,data) in transactions.iter().enumerate(){
        println!("object {} : {:?}",i +1 ,data);
    }
    
    Transaction::print_total_invested_per_continent(&transactions);

    println!("\nPrinting Companies in Europe:");
    print_companies_from_continent(&transactions, &Continent::Europe);
    

}
