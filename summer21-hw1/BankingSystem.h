#ifndef BANKINGSYSTEM_H
#define BANKINGSYSTEM_H

#include "Branch.h"
#include "Customer.h"
#include "Account.h"
#include <iostream>
#include <iomanip> //setprecision

std::ostream& operator<<(std::ostream& out, const Branch& obj);
std::ostream& operator<<(std::ostream& out, const Customer& obj);

class BankingSystem {
public :
    BankingSystem();
    ~BankingSystem();

    void addBranch(const int branchId, const std::string branchName);
    void deleteBranch(const int branchId);

    void addCustomer(const int customerId, const std::string customerName);
    void deleteCustomer(const int customerId);

    int addAccount(const int branchId, const int customerId, const double amount);
    void deleteAccount(const int accountId);

    void showAllAccounts();
    void showBranch(const int branchId);
    void showCustomer(const int customerId);

    //additional functions
    void showAllBranches();
    void showAllCustomers();
    void showAccount(const int accountId);

    std::string getBranchName(const int branchId);
    std::string getCustomerName(const int customerId);

private:
    //data members
    Branch* branchList;
    int branchNum;

    Customer* customerList;
    int customerNum;

    Account* accountList;
    int accountNum;
    int accountCounter; //this will always increase even in account deletions to create unique ids

    //functions
    void deleteAccountWithoutMsg(const int accountId);
    void deleteCustomerWithoutMsg(const int customerId);
};

#endif