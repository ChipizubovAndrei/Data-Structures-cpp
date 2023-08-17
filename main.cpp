#include <iostream>
#include <cstdlib>

#include "array.h"
#include "linked_list.h"
#include "binary_tree.h"

int main()
{
    BinaryTree<int> tree(23);
    for (int i = 0; i < 20; ++i) {
        tree.insert(std::rand() % 100);
    }
    tree.print();
    tree.insert(10000);
    tree.print();
    std::cout << tree.getMax() << std::endl;
    std::cout << tree.getMin() << std::endl;
    return EXIT_SUCCESS;
}