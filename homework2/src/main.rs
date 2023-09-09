#[derive(PartialEq, Eq)]
enum Paymentype {
    Cash,
    DigitalToken,
}

struct Seller {
    payment_type: Paymentype,
    price: f32,
    balance: f32,
}

struct Buyer {
    name : String,
    payment_type: Paymentype,
    balance: f32,
}

struct BuyerGroup {
    buyers: Vec<Buyer>,
}

impl BuyerGroup {
    fn add_member(&mut self, buyer: Buyer) {
        self.buyers.push(buyer);
    }
    fn find_buyer(&self, payment_type: &Paymentype) -> i32 {
        for i in 0..self.buyers.len() {
            if self.buyers[i].payment_type == *payment_type {
                return i as i32;
            }
        }
        return -1;
    }
    fn buy(&mut self, index : i32, seller: &mut Seller) {
        if index != -1 {
            if seller.price <= self.buyers[index as usize].balance {
                self.buyers[index as usize].balance -= seller.price;
                seller.balance += seller.price;

                println!("Buyer {} bought item for {}",
                         self.buyers[index as usize].name,
                         seller.price);
            }
            else {
                println!("Buyer {} does not have enough money",
                         self.buyers[index as usize].name);
            }
        }
    }
}

fn main() {
    println!("Hello, world!");
    let mut buyer_group = BuyerGroup { buyers: Vec::new() };
    let buyer_john  = Buyer {
        name: String::from("John"),
        payment_type: Paymentype::Cash,
        balance: 100.0,
    };
    let buyer_sally = Buyer {
        name: String::from("Sally"),
        payment_type: Paymentype::DigitalToken,
        balance: 100.0,
    };

    buyer_group.add_member(buyer_john);
    buyer_group.add_member(buyer_sally);

    let mut seller = Seller {
        payment_type: Paymentype::Cash,
        price: 10.0,
        balance: 0.0,
    };

    let index = buyer_group.find_buyer(&seller.payment_type);
    buyer_group.buy(index, &mut seller);
    buyer_group.buy(index, &mut seller);
    buyer_group.buy(index, &mut seller);
    buyer_group.buy(index, &mut seller);
    buyer_group.buy(index, &mut seller);
    buyer_group.buy(index, &mut seller);

    for i in 0..10{ buyer_group.buy(index, &mut seller); };
}
