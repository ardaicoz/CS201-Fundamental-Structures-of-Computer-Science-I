#include "BankingSystem.h"
using namespace std;

BankingSystem::BankingSystem() {
    branchList = NULL;
    branchNum = 0;

    customerList = NULL;
    customerNum = 0;

    accountList = NULL;
    accountNum = 0;
    accountCounter = 0;
}

BankingSystem::~BankingSystem() {
    delete[] accountList;
    delete[] customerList;
    delete[] branchList;
}

void BankingSystem::addBranch(const int branchId, const std::string branchName) {
    //if there are no branches no need to check if its already added
    if (branchNum == 0) {
        //set the number of branches to 1
        branchNum = 1;
        //create the branch array and add the first branch
        branchList = new Branch[branchNum];
        branchList[branchNum-1].setId(branchId);
        branchList[branchNum-1].setName(branchName);

        cout << "Branch " << branchId << " has been added" << endl;
    }
    else {
        //check if the branch already added
        for (int i = 0; i < branchNum; i++) {
            if (branchList[i].getId() == branchId) {
                cout << "Branch " << branchId << " already exists" << endl;
                return;
            }
        }

        //save branchList to an temp array
        Branch* tempList = branchList;
        //increment the branch num
        branchNum++;
        //create a bigger array and copy
        branchList = new Branch[branchNum];
        for (int i = 0; i < branchNum-1; i++) {
            branchList[i] = tempList[i];
        }
        //add the new branch to the end
        branchList[branchNum-1].setId(branchId);
        branchList[branchNum-1].setName(branchName);
        cout << "Branch " << branchId << " has been added" << endl;

        //deleting the array pointed by temp
        delete[] tempList;
    }
}

void BankingSystem::deleteBranch(const int branchId) {
    //lets check if this branch exist
    bool flagBranch = false;
    int index = -1;
    for (int i = 0; i < branchNum; i++) {
        if (branchList[i].getId() == branchId) {
            flagBranch = true;
            index = i;
        }
    }

    //if does not exist print error message
    if (!flagBranch) {
        cout << "Branch " << branchId << " does not exist" << endl;
    }
    else {
        //first, delete the accounts of this branch
        //Why decrementing variable i in every deletion? When a deletion happens, elements of the array move left by 1. So in order not to
        //skip an element, we decrease i ONLY after a deletion.
        for (int i = 0; i < accountNum; i++) {
            if (accountList[i].getBranch() == branchId) {
                deleteAccountWithoutMsg(accountList[i].getUnique());
                i--;
            }
        }
        
        //now delete this branch
        if (branchNum == 1) {
            //set the number of customer to 0
            branchNum = 0;
            //deleting the customerList array compeletely
            delete[] branchList;
            branchList = NULL;

            cout << "Branch " << branchId << " has been deleted" << endl;
        }
        else {
            //decrease the customer num
            branchNum--;
            //create a temp list and create a new list with less size
            Branch* tempList = branchList;
            branchList = new Branch[branchNum];
            //transfer the accounts in temp list to new accountList array until the index we want to delete
            for (int i = 0; i < index; i++) {
                branchList[i] = tempList[i];
            }
            //skip that account and transfer others that left
            for (int i = index+1; i < branchNum+1; i++) {
                branchList[i-1] = tempList[i];
            }

            cout << "Branch " << branchId << " has been deleted" << endl;

            //deleting the old array
            delete[] tempList;
        }
    }
}

void BankingSystem::addCustomer(const int customerId, const std::string customerName) {
    //if there are no customers no need to check if its already added
    if (customerNum == 0) {
        //set the number of branches to 1
        customerNum = 1;
        //create the branch array and add the first branch
        customerList = new Customer[customerNum];
        customerList[customerNum-1].setId(customerId);
        customerList[customerNum-1].setName(customerName);

        cout << "Customer " << customerId << " has been added" << endl;
    }
    else {
        //check if the customer already added
        for (int i = 0; i < customerNum; i++) {
            if (customerList[i].getId() == customerId) {
                cout << "Customer " << customerId << " already exists" << endl;
                return;
            }
        }

        //save customerList to an temp array
        Customer* tempList =customerList;
        //increment the customer num
        customerNum++;
        //create a bigger array and copy
        customerList = new Customer[customerNum];
        for (int i = 0; i < customerNum-1; i++) {
            customerList[i] = tempList[i];
        }
        //add the new customer to the end
        customerList[customerNum-1].setId(customerId);
        customerList[customerNum-1].setName(customerName);
        cout << "Customer " << customerId << " has been added" << endl;

        //deleting the array pointed by temp
        delete[] tempList;
    }
}

void BankingSystem::deleteCustomer(const int customerId) {
    //lets check if this customer exist
    bool flagCustomer = false;
    int index = -1;
    for (int i = 0; i < customerNum; i++) {
        if (customerList[i].getId() == customerId) {
            flagCustomer = true;
            index = i;
        }
    }

    //if does not exist print error message
    if (!flagCustomer) {
        cout << "Customer " << customerId << " does not exist" << endl;
    }
    else {
        //first, delete the accounts of this customer
        //Why decrementing variable i in every deletion? When a deletion happens, elements of the array move left by 1. So in order not to
        //skip an element, we decrease i ONLY after a deletion.
        for (int i = 0; i < accountNum; i++) {
            if (accountList[i].getCustomer() == customerId) {
                deleteAccountWithoutMsg(accountList[i].getUnique());
                i--;
            }
        }
        
        //now delete this customer
        if (customerNum == 1) {
            //set the number of customer to 0
            customerNum = 0;
            //deleting the customerList array compeletely
            delete[] customerList;
            customerList = NULL;

            cout << "Customer " << customerId << " has been deleted" << endl;
        }
        else {
            //decrease the customer num
            customerNum--;
            //create a temp list and create a new list with less size
            Customer* tempList = customerList;
            customerList = new Customer[customerNum];
            //transfer the accounts in temp list to new accountList array until the index we want to delete
            for (int i = 0; i < index; i++) {
                customerList[i] = tempList[i];
            }
            //skip that account and transfer others that left
            for (int i = index+1; i < customerNum+1; i++) {
                customerList[i-1] = tempList[i];
            }

            cout << "Customer " << customerId << " has been deleted" << endl;

            //deleting the old array
            delete[] tempList;
        }
    }
}

int BankingSystem::addAccount(const int branchId, const int customerId, const double amount) {
    //lets look to every branch to see if its exists
    bool flagBranch = false;
    for (int i = 0; i < branchNum; i++) {
        if (branchList[i].getId() == branchId) {
            flagBranch = true;
        }
    }
    //and lets see if this customer exists
    bool flagCustomer = false;
    for (int i = 0; i < customerNum; i++) {
        if (customerList[i].getId() == customerId) {
            flagCustomer = true;
        }
    }
    
    //checkpoint
    if (!flagBranch) {
        cout << "Branch " << branchId << " does not exist" << endl;
        return -1;
    }
    else if (!flagCustomer) {
        cout << "Customer " << customerId << " does not exist" << endl;
        return -1;
    }
    else {
        //if there are no accounts no need to check if its already added
        if (accountNum == 0) {
            //set the number of accounts to 1
            accountNum = 1;
            accountCounter++;
            //create the account array and add the first branch
            accountList = new Account[accountNum];
            accountList[accountNum-1].setBranch(branchId);
            accountList[accountNum-1].setCustomer(customerId);
            accountList[accountNum-1].setAmount(amount);
            accountList[accountNum-1].setUnique(accountCounter);

            cout << "Account " << accountList[accountNum-1].getUnique() << " added for customer " << customerId << " at branch " << branchId << endl;
            return accountNum;
        }
        else {
            //save accountList to an temp array
            Account* tempList = accountList;
            //increment the account num
            accountNum++;
            accountCounter++;
            //create a bigger array and copy
            accountList = new Account[accountNum];
            for (int i = 0; i < accountNum-1; i++) {
                accountList[i] = tempList[i];
            }
            //add the new branch to the end
            accountList[accountNum-1].setBranch(branchId);
            accountList[accountNum-1].setCustomer(customerId);
            accountList[accountNum-1].setAmount(amount);
            accountList[accountNum-1].setUnique(accountCounter);
            
            cout << "Account " << accountList[accountNum-1].getUnique() << " added for customer " << customerId << " at branch " << branchId << endl;

            //deleting the array pointed by temp
            delete[] tempList;
            return accountNum;
        }
    }
    
    return -1; 
}

void BankingSystem::deleteAccount(const int accountId) {
    //lets check if this account exist
    bool flagAccount = false;
    int index = -1;
    for (int i = 0; i < accountNum; i++) {
        if (accountList[i].getUnique() == accountId) {
            flagAccount = true;
            index = i;
        }
    }
    
    //if this account does not exist, return
    if (!flagAccount) {
        cout << "Account " << accountId << " does not exist" << endl;
    }
    else {
        //now lets delete the account in accountList array
        if (accountNum == 1) {
            //set the number of account to 0
            accountNum = 0;
            //deleting the accountList array compeletely
            delete[] accountList;
            accountList = NULL;

            cout << "Account " << accountId << " has been deleted" << endl;
        }
        else {
            //decrease the account num
            accountNum--;
            //create a temp list and create a new list with less size
            Account* tempList = accountList;
            accountList = new Account[accountNum];
            //transfer the accounts in temp list to new accountList array until the index we want to delete
            for (int i = 0; i < index; i++) {
                accountList[i] = tempList[i];
            }
            //skip that account and transfer others that left
            for (int i = index+1; i < accountNum+1; i++) {
                accountList[i-1] = tempList[i];
            }

            cout << "Account " << accountId << " has been deleted" << endl;

            //deleting the old array
            delete[] tempList;
        }
    }  
}

void BankingSystem::showAllAccounts() {
    if (accountNum == 0) {
        cout << "No account exist" << endl;
    }
    else {
        cout << "Account id" << "\t" << "Branch id" << "\t" << "Branch name" << "\t\t" << "Customer id" << "\t\t" << "Customer name" << "\t" << "Balance  " << endl;
        for (int i = 0; i < accountNum; i++) {
            showAccount(accountList[i].getUnique());
        }
    }
}

void BankingSystem::showAccount(const int accountId) {
    for (int i = 0; i < accountNum; i++) {
        if (accountList[i].getUnique() == accountId) {
            cout << accountList[i].getUnique() << "\t\t" << accountList[i].getBranch() << "\t\t" << 
            getBranchName( accountList[i].getBranch() ) << "\t\t\t" << accountList[i].getCustomer() << "\t\t\t" <<
            getCustomerName( accountList[i].getCustomer() ) << "\t" << (accountList[i].getAmount()) << endl;
            
            break;
        }
    }
}

void BankingSystem::showBranch(const int branchId) {
    //check if this branch exits
    bool isBranch = false;
    for (int i = 0; i < branchNum; i++) {
        if (branchList[i].getId() == branchId) {
            isBranch = true;
        }
    }
    
    if (!isBranch) {
        cout << "Branch " << branchId << " does not exist" << endl; 
    }
    else {
        int accounts = 0;
        string name = "";

        //searching for the name of this branch    
        for (int i = 0; i < branchNum; i++) {
            if (branchList[i].getId() == branchId) {
                name = branchList[i].getName();
                break;
            }
        }
        //getting no of accounts
        for (int i = 0; i < accountNum; i++) {
            if (accountList[i].getBranch() == branchId) {
                accounts++;
            }
        }

        cout << "Branch id: " << branchId << "  Branch name: " << name << "  Number of accounts: " << accounts << endl; 
        
        //printing all accounts in this branch
        if (accounts > 0) {
            cout << "Accounts at this branch:" << endl;
            cout << "Account id" << "\t" << "Customer id" << "\t" << "Customer name" << "\t" << "Balance" << endl;

            for (int i = 0; i < accountNum; i++) {
                if (accountList[i].getBranch() == branchId) {
                    cout << accountList[i].getUnique() << "\t\t" << accountList[i].getCustomer() << "\t\t" << 
                    getCustomerName(accountList[i].getCustomer()) << "\t\t" << accountList[i].getAmount() << endl;
                }
            }
        }
    }  
}

void BankingSystem::showCustomer(const int customerId) {
    //check if this customer exits
    bool isCustomer = false;
    for (int i = 0; i < customerNum; i++) {
        if (customerList[i].getId() == customerId) {
            isCustomer = true;
        }
    }

    if (!isCustomer) {
        cout << "Customer " << customerId << " does not exist" << endl; 
    }
    else {
        int accounts = 0;
        string name = "";

        //searching for the name of this customer   
        for (int i = 0; i < customerNum; i++) {
            if (customerList[i].getId() == customerId) {
                name = customerList[i].getName();
                break;
            }
        }
        //getting no of accounts
        for (int i = 0; i < accountNum; i++) {
            if (accountList[i].getCustomer() == customerId) {
                accounts++;
            }
        }

        cout << "Customer id: " << customerId << "  Customer name: " << name << "  Number of accounts: " << accounts << endl; 
        
        //printing all accounts for this customer
        if (accounts > 0) {
            cout << "Accounts of this customer:" << endl;
            cout << "Account id" << "\t" << "Branch id" << "\t" << "Branch name" << "\t" << "Balance" << endl;

            for (int i = 0; i < accountNum; i++) {
                if (accountList[i].getCustomer() == customerId) {
                    cout << accountList[i].getUnique() << "\t\t" << accountList[i].getBranch() << "\t\t" << 
                    getBranchName(accountList[i].getBranch()) << "\t\t" << accountList[i].getAmount() << endl;
                }
            }
        }
    }
}

string BankingSystem::getBranchName(const int branchId) {
    string name = "";
    
    for (int i = 0; i < branchNum; i++) {
        if (branchList[i].getId() == branchId) {
            name = branchList[i].getName();
        }
    }
    
    return name;
}

string BankingSystem::getCustomerName(const int customerId) {
    string name = "";
    
    for (int i = 0; i < customerNum; i++) {
        if (customerList[i].getId() == customerId) {
            name = customerList[i].getName();
        }
    }

    return name;
}

void BankingSystem::showAllBranches() {
    if (branchNum == 0) {
        cout << "No branch exists" << endl;
    }
    else {
        for (int i = 0; i < branchNum; i++) {
            cout << branchList[i];
        }
    }
}

void BankingSystem::showAllCustomers() {
    if (customerNum == 0) {
        cout << "No customer exists" << endl;
    }
    else {
        for (int i = 0; i < customerNum; i++) {
            cout << customerList[i];
        }
    }
}

void BankingSystem::deleteAccountWithoutMsg(const int accountId) {
    //lets check if this account exist
    bool flagAccount = false;
    int index = -1;
    for (int i = 0; i < accountNum; i++) {
        if (accountList[i].getUnique() == accountId) {
            flagAccount = true;
            index = i;
        }
    }
    
    if (flagAccount) {
        //now lets delete the account in accountList array
        if (accountNum == 1) {
            //set the number of account to 0
            accountNum = 0;
            //deleting the accountList array compeletely
            delete[] accountList;
            accountList = NULL;
        }
        else {
            //decrease the account num
            accountNum--;
            //create a temp list and create a new list with less size
            Account* tempList = accountList;
            accountList = new Account[accountNum];
            //transfer the accounts in temp list to new accountList array until the index we want to delete
            for (int i = 0; i < index; i++) {
                accountList[i] = tempList[i];
            }
            //skip that account and transfer others that left
            for (int i = index+1; i < accountNum+1; i++) {
                accountList[i-1] = tempList[i];
            }

            //deleting the old array
            delete[] tempList;
        }
    }  
}

void BankingSystem::deleteCustomerWithoutMsg(const int customerId) {
    //lets check if this customer exist
    bool flagCustomer = false;
    int index = -1;
    for (int i = 0; i < customerNum; i++) {
        if (customerList[i].getId() == customerId) {
            flagCustomer = true;
            index = i;
        }
    }

    //if does not exist print error message
    if (flagCustomer) {
        //first, delete the accounts of this customer
        //Why decrementing variable i in every deletion? When a deletion happens, elements of the array move left by 1. So in order not to
        //skip an element, we decrease i ONLY after a deletion.
        for (int i = 0; i < accountNum; i++) {
            if (accountList[i].getCustomer() == customerId) {
                deleteAccountWithoutMsg(accountList[i].getUnique());
                i--;
            }
        }
        
        //now delete this customer
        if (customerNum == 1) {
            //set the number of customer to 0
            customerNum = 0;
            //deleting the customerList array compeletely
            delete[] customerList;
            customerList = NULL;
        }
        else {
            //decrease the customer num
            customerNum--;
            //create a temp list and create a new list with less size
            Customer* tempList = customerList;
            customerList = new Customer[customerNum];
            //transfer the accounts in temp list to new accountList array until the index we want to delete
            for (int i = 0; i < index; i++) {
                customerList[i] = tempList[i];
            }
            //skip that account and transfer others that left
            for (int i = index+1; i < customerNum+1; i++) {
                customerList[i-1] = tempList[i];
            }

            //deleting the old array
            delete[] tempList;
        }
    }
}

ostream& operator<<(ostream& out, const Branch& obj) {
    out << "Branch " << obj.getId() << " (" << obj.getName() << ")" << endl;
    return out;
}

ostream& operator<<(std::ostream& out, const Customer& obj) {
    out << "Customer " << obj.getId() << " (" << obj.getName() << ")" << endl;
    return out;
}