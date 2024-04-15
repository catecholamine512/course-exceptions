#include <cassert>
#include <iostream>
#include <exception>
#include "IntegerArray.h"


int main(void) {
    try {
        int size_neg = -10;
        std::cout << "trying to create an array of negative length " << size_neg << std::endl;
        IntegerArray a1(size_neg);
    }
    catch (bad_length& e) {
        std::cout << "caught exception: " << e.what() << std::endl;
    }
    catch (std::exception& e) {
        std::cout << "unexpected exception: " << e.what() << std::endl;
    }

    try {
        IntegerArray a2(10);
        int i_neg = -10;
        std::cout << "trying to access at a negative index " << i_neg << std::endl;
        std::cout << a2[i_neg] << std::endl;
    }
    catch (bad_range& e) {
        std::cout << "caught exception: " << e.what() << std::endl;
    }
    catch (std::exception& e) {
        std::cout << "unexpected exception: " << e.what() << std::endl;
    }

    try {
        IntegerArray a3(10);
        int i_over = 100;
        std::cout << "trying to access at a too large index " << i_over << std::endl;
        std::cout << a3[i_over] << std::endl;
    }
    catch (bad_range& e) {
        std::cout << "caught exception: " << e.what() << std::endl;
    }
    catch (std::exception& e) {
        std::cout << "unexpected exception: " << e.what() << std::endl;
    }

    IntegerArray a(5);
    std::cout << a[2] << std::endl;
    a[2] = 200;
    std::cout << a[2] << std::endl;

    IntegerArray b(a);
    b.resize(1);
    std::cout << a << std::endl;
    std::cout << b << std::endl;
    try {
        b.resize(-1);
    }
    catch (bad_length& e) {
        std::cout << "caught exception: " << e.what() << std::endl;
    }
    catch (std::exception& e) {
        std::cout << "unexpected exception: " << e.what() << std::endl;
    }

    try {
        b.remove(0);
    }
    catch (std::exception& e) {
        std::cout << "unexpected exception: " << e.what() << std::endl;
    }

    try {
        b.remove(0);
    }
    catch (bad_range& e) {
        std::cout << "caught exception: " << e.what() << std::endl;
    }
    catch (std::exception& e) {
        std::cout << "unexpected exception: " << e.what() << std::endl;
    }

    try {
        a.insert(2, 100);
        std::cout << a << std::endl;
        a.push_start(150);
        std::cout << a << std::endl;
        a.push_end(250);
        std::cout << a << std::endl;
        a.remove(0);
        std::cout << a << std::endl;
    }
    catch (std::exception& e) {
        std::cout << "unexpected exception: " << e.what() << std::endl;
    }

    int idx = a.search(200);
    if (idx >= 0)
        std::cout << "found value 200 at index " << idx << std::endl;


	return 0;
}

