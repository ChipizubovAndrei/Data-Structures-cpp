#include <iostream>
#include "array.h"

int main()
{
    int N = 10;
    DynamicArray<int> a1(N);
    a1.print();
    for (int i = 0; i < 5; ++i) {
        a1.push_back(i+1);
    }
    a1.insert(10, 2);
    a1.erase(3);
    a1.print();
    return EXIT_SUCCESS;
}