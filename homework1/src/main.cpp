#include <iostream>
#include <string>
#include <tuple>


struct User
{
    std::string name;
    std::tuple<float,std::string> balance;
    
    void print_user_details()
    {
        std::cout << "Name: " << name << std::endl;
        std::cout << "Balance: " << std::get<0>(balance) << " " << std::get<1>(balance) << std::endl;
    }

    static void accrue_interest(User& user, float rate)
    {
        std::get<0>(user.balance) += (rate / 100.f) * std::get<0>(user.balance);
    }
};

int main()
{
    User user{"John Doe", {1000.f, "SGD"}};
    user.print_user_details();
    User::accrue_interest(user, 10.f);
    User::accrue_interest(user, 10.f);
    User::accrue_interest(user, 10.f);
    User::accrue_interest(user, 10.f);
    User::accrue_interest(user, 10.f);

    user.print_user_details();
    return 0;
}