#include <iostream>
#include <cstdlib>

#include "array.h"
#include "linked_list.h"
#include "binary_tree.h"

int main()
{
    BinaryTree<int> a(20);
    a.insert(5);
    a.insert(24);
    a.insert(2);
    a.insert(16);
    a.insert(11);
    a.insert(18);
    a.insert(13);
    a.print();
    a.remove(20);
    a.print();
    std::cout << a.getRoot()->value << std::endl;
    return EXIT_SUCCESS;
}