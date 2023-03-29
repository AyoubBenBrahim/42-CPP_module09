#include "BitcoinExchange.hpp"

#define MAIN1

#ifdef MAIN1

int main(int ac, char **av)
{
    try
    {
        if (ac != 2)
        {
            throw std::string("Error: invalid number of arguments.");
            return 1;
        }

        BitcoinExchange btc(database, av[1]);
    }
    catch(std::string err)
    {
        std::cout << err << '\n';
    }
    return 0;
}

#else

/*
** main driver that tests the copy constructor, operator overload, and getters
*/

int main(int ac, char **av)
{
    if (ac != 2)
    {
        std::cerr << "Error: invalid number of arguments." << std::endl;
        return 1;
    }

    BitcoinExchange b1(database, av[1]);

    // Print the contents of the map
    std::cout << "\n***************************************" << std::endl;
    std::cout << "Database map in original object:" << std::endl;
    std::cout << "***************************************\n"
              << std::endl;

    std::map<std::string, double> map1 = b1.getDatabaseMap();
    std::map<std::string, double>::const_iterator it;
    // for (it = map1.begin(); it != map1.end(); ++it)
    // {
    //     std::cout << it->first << ": " << it->second << std::endl;
    // }
    std::cout << "Size of the map: " << map1.size() << std::endl
              << std::endl;

    // Test the copy constructor
    BitcoinExchange b2 = b1;

    // Print the contents of the map in the copied object
    std::cout << "\n***************************************" << std::endl;
    std::cout << "Database map in copied object:" << std::endl;
    std::cout << "***************************************\n"
              << std::endl;

    std::map<std::string, double> map2 = b2.getDatabaseMap();
    // for (it = map2.begin(); it != map2.end(); ++it)
    // {
    //     std::cout << it->first << ": " << it->second << std::endl;
    // }
    std::cout << "Size of the map: " << map2.size() << std::endl
              << std::endl;

    // Test the assignment operator overload by assigning the original object to a new object
    BitcoinExchange b3(database, av[1]);
    b3 = b1;

    // Print the contents of the map in the reassigned object
    std::cout << "\n***************************************" << std::endl;
    std::cout << "Database map in reassigned object:" << std::endl;
    std::cout << "***************************************\n"
              << std::endl;

    std::map<std::string, double> map3 = b3.getDatabaseMap();
    // for (it = map3.begin(); it != map3.end(); ++it)
    // {
    //     std::cout << it->first << ": " << it->second << std::endl;
    // }

    std::cout << "Size of the map: " << map3.size() << std::endl
              << std::endl;

    return 0;
}

#endif