#ifndef ACCOUNT_H
#define ACCOUNT_H
#include <iostream>

class Account {
public:
    Account(const int branchId = 0, const int customerId = 0, const double amount = 0);
    ~Account();

    void setBranch(const int branch);
    void setCustomer(const int customer);
    void setAmount(const double amount);
    void setUnique(const int id);

    int getBranch() const;
    int getCustomer() const;
    double getAmount() const;
    int getUnique() const;

private:
    int branchId;
    int customerId;
    double amount;
    int uniqueId;
};

#endif