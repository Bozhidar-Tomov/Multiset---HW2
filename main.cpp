#include <iostream>
#include "Multiset.h"
#include <stdexcept>

int main()
{
    Multiset m(10, 1);

    try
    {
        m.add(11);
    }
    catch (const std::exception &e)
    {
        std::cerr << '\n'
                  << e.what() << '\n';
    }
}