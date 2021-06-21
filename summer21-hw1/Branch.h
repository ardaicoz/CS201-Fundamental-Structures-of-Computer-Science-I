#ifndef BRANCH_H
#define BRANCH_H
#include <iostream>

class Branch {
public:
    Branch(int id = 0, std::string name = "");
    ~Branch();
    
    void setId(int id);
    void setName(std::string name);
    int getId() const;
    std::string getName() const;

private:
    int branchId;
    std::string branchName;
};

#endif