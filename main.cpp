#include <iostream>
#include <memory>
#include "array.h"
#include "linked_list.h"

int main()
{
    SinglyLinkedList<int> a(1111, 2222);
    for (int i = 0; i < 10; i++) {
        a.push_back(i + 1);
    }
    a.print();
    a.reverse();
    a.print();
}