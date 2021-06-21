#include "Branch.h"
using namespace std;

Branch::Branch(int id, string name) {
    branchId = id;
    branchName = name;
}

Branch::~Branch() {}

void Branch::setId(int id) {
    branchId = id;
}

void Branch::setName(string name) {
    branchName = name;
}

int Branch::getId() const {
    return branchId;
}

string Branch::getName() const {
    return branchName;
}