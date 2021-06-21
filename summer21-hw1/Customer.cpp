#include "Customer.h"
using namespace std;

Customer::Customer(const int id, const string name) {
    customerId = id;
    customerName = name;
}

Customer::~Customer() {}

void Customer::setId(const int id) {
    customerId = id;
}

void Customer::setName(const string name) {
    customerName = name;
}

int Customer::getId() const {
    return customerId;
}

string Customer::getName() const {
    return customerName;
}