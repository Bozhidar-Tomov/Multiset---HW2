#include <iostream>
#include "Multiset.h"
#include <stdexcept>

int main()
{
    Multiset m(10, 2);

    try
    {
        m.add(1);
        m.add(1);
        m.add(1);
        m.add(1);
        m.add(2);
    }
    catch (const std::exception &e)
    {
        std::cerr << '\n'
                  << e.what() << '\n';
    }
}