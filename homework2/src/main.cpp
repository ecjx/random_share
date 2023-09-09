#include <iostream>
#include <string>
#include <vector>
#include <utility>

enum PaymentType
{
    CASH,
    DIGITALTOKEN
};

struct Buyer
{
    PaymentType paymentType;
    std::string name;
    float balance;
};

struct Seller
{
    PaymentType paymentType;
    float balance;
    float price;
};

struct BuyersGroup
{
    std::vector<Buyer> buyers;

    void addBuyer(Buyer&& buyer)
    {
        buyers.emplace_back(std::move(buyer));
    }

   int findBuyer(PaymentType type)
   {
     for(int i = 0; const auto& buyer : buyers)
     {
         if(buyer.paymentType == type)
         {
             return i;
         }
         ++i;
     }
     return -1;
   }

   void buy(Seller& seller, int index)
   {
        
       if(index < 0 || seller.price > buyers[index].balance)
       {
           return;
       }
       seller.balance += seller.price;
       buyers[index].balance -= seller.price;
   }
};

int main()
{
    Buyer john{ PaymentType::CASH, "John", 100.0f };
    Buyer sally{ PaymentType::DIGITALTOKEN, "Sally", 100.0f };
    
    Seller seller{ PaymentType::CASH, 0.0f, 10.0f };

    BuyersGroup buyersGroup;
    buyersGroup.addBuyer(std::move(john));
    buyersGroup.addBuyer(std::move(sally));

    buyersGroup.buy(seller, buyersGroup.findBuyer(seller.paymentType));

}