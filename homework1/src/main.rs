
struct User
{
    name: String,
    balance: (f32, String),
}

impl User
{
    fn new(name: String, balance: (f32, String)) -> User
    {
        User
        {
            name: name,
            balance: balance,
        }
    }

    fn print_user_details(&self)
    {
        println!("Name: {}", self.name);
        println!("Balance: {} {}", self.balance.0, self.balance.1);
    }

    fn accrue_interest(user: &mut User, rate: f32)
    {
        user.balance.0 += user.balance.0 * (rate / 100.0);
    }
    
}

fn main() {
    println!("Hello, world!");

    let mut user = User::new("John Doe".to_string()
                            , (100.0, "SGD".to_owned()));
    /*let mut user : User = User{
        name: String::from("John Doe"),
        balance: (100.0, String::from("SGD")),
    };*/
    user.print_user_details();
    User::accrue_interest(&mut user, 10.0);
    User::accrue_interest(&mut user, 10.0);
    User::accrue_interest(&mut user, 10.0);
    User::accrue_interest(&mut user, 10.0);
    User::accrue_interest(&mut user, 10.0);
    user.print_user_details();
}
