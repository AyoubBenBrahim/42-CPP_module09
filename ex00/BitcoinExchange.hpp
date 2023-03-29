#ifndef BitcoinExchange_HPP
#define BitcoinExchange_HPP

#include <iostream>
#include <fstream>
#include <map>
#include <string>
#include <iomanip>
#include <sstream>

const double MAX_BTC_VALUE = 1000.0;
const double MIN_BTC_VALUE = 0;
const std::string database = "data.csv";

# define RESET			"\033[0m"
# define GREEN			"\033[32m"

class BitcoinExchange
{
private:
	std::string database;
	std::string inputFile;
	std::map<std::string, double> databaseMap;


public:
	BitcoinExchange(void);
	BitcoinExchange(std::string const &_database, std::string const &_file);
	BitcoinExchange(const BitcoinExchange& copy);
	BitcoinExchange &operator=(const BitcoinExchange &rhs);
	~BitcoinExchange(void);

// void parseFile(std::string, char, std::map<std::string, double> &);
std::string const& getInputFile() const { return inputFile; }
std::string const& getDatabase() const { return database; }
std::map<std::string, double> const& getDatabaseMap() const { return databaseMap; }
bool isValidDate(std::string&);
double toDouble(std::string , bool );

  void parsingFactory(std::string fileName, char delimiter);

	
};

#endif