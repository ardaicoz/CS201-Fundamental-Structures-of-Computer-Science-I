#include "SinglyList.h"
using namespace std;

SinglyList::SinglyList() {
    size = 0;
    head = NULL;
}

SinglyList::~SinglyList() {
    while (!isEmpty)
        remove(1);
}

bool SinglyList::isEmpty() const {
    return size == 0;
}

int SinglyList::getLength() const {
    return size;
}

SinglyList::SinglyListNode* SinglyList::find(const int index) const {
    if (index < 1 || index > getLength())
        return NULL;
    else {
        SinglyListNode* cur = head;

        for (int skip = 1; skip < index; ++skip)
            cur = cur->next;
        return cur;
    }
}