#include "Account.h"
using namespace std;

Account::Account(const int branchId, const int customerId, const double amount) {
    this->branchId = branchId;
    this->customerId = customerId;
    this->amount = amount;
}

Account::~Account() {}

void Account::setBranch(const int branch) {
    branchId = branch;
}

void Account::setCustomer(const int customer) {
    customerId = customer;
}

void Account::setAmount(const double amount) {
    this->amount = amount;
}

void Account::setUnique(const int id) {
    uniqueId = id;
}

int Account::getBranch() const {
    return branchId;
}
    
int Account::getCustomer() const {
    return customerId;
}
    
double Account::getAmount() const {
    return amount;
}
    
int Account::getUnique() const {
    return uniqueId;
}