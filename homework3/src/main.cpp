#include <string>
#include <optional>
#include <variant>
#include <iostream>


template<typename T>
struct Result
{
    bool success_;
    std::variant<T,std::string> value_;
};

struct UserAccount
{
    std::string name;
    std::optional<uint32_t> age;
};


template <typename T>
concept TraitUserAccount = requires(T t)
{
    { t.name } -> std::convertible_to<std::string>;
    { t.age } -> std::convertible_to<std::optional<uint32_t>>;
};

struct Balance
{
    uint32_t get_balance() const
    {
        return 10;
    }

    template <typename T>
    Result<uint32_t> increase_balance(const T& user,uint32_t amount)
    {
        return Result<uint32_t>{false,std::string{"Not Impl!"}};
    }

    template<TraitUserAccount TUserAccount>
    Result<uint32_t> increase_balance(const TUserAccount& user, uint32_t amount)
    {
         if (amount <= 10)
            return Result<uint32_t>{true, uint32_t{ get_balance() + amount} };
        return Result<uint32_t>{false,std::string{"Increase must be less than 10!"}};
    }
};

int main()
{
    Balance balance;
    UserAccount user{"John", 20};
    auto result = balance.increase_balance(user, 10);
    if (result.success_)
    {
        std::cout << "Balance: " << std::get<0>(result.value_) << std::endl;
    }
    else
    {
        std::cout << "Error: " << std::get<1>(result.value_) << std::endl;
    }

    if(uint32_t age = user.age.value_or(0); age != 0)
    {
        std::cout << "Age: " << age << std::endl;
    }
    else
    {
        std::cout << "Age: " << "Not Found" << std::endl;
    }
    return 0;
}


