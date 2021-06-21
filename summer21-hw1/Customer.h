#ifndef CUSTOMER_H
#define CUSTOMER_H
#include <iostream>

class Customer {
public:
    Customer(const int id = 0, const std::string name = "");
    ~Customer();
    
    void setId(const int id);
    void setName(const std::string name);
    
    int getId() const;
    std::string getName() const;

private:
    int customerId;
    std::string customerName;
};

#endif