#include "BitcoinExchange.hpp"

BitcoinExchange::BitcoinExchange(std::string const& _database, std::string const& _file)
: database(_database), inputFile(_file)
{
    parsingFactory(database, ',');
    if (this->databaseMap.size() == 0)
        throw std::string("Error: Empty database.");
    parsingFactory(inputFile, '|');
}


BitcoinExchange::BitcoinExchange(const BitcoinExchange& copy)
        : database(copy.database), inputFile(copy.inputFile), databaseMap(copy.databaseMap)
{
}


BitcoinExchange::~BitcoinExchange(void){}

BitcoinExchange &BitcoinExchange::operator=(BitcoinExchange const &rhs)
{
    if (this == &rhs)
        return *this;

    inputFile = rhs.getInputFile();
    database = rhs.getDatabase();
    databaseMap = rhs.getDatabaseMap();

    return *this;
}

bool BitcoinExchange::isValidDate(std::string &dateStr)
{
    int year, month, day;
    int len = dateStr.length();

    if (dateStr[10] == ' ') len--;
    if (len != 10) return false;

    if (dateStr[4] != '-' || dateStr[7] != '-') return false;

    for (int i = 0; i < 10; i++)
    {
        if (i == 4 || i == 7) continue;
        if (!isdigit(dateStr[i])) return false;
    }

 if (sscanf(dateStr.c_str(), "%4d-%2d-%2d", &year, &month, &day) != 3)
        return false;

    if (month < 1 || month > 12 || day < 1 || day > 31)
        return false;
    if (month == 2 && day > 29)
        return false;

    return true;
}

double BitcoinExchange::toDouble(std::string str, bool Flag)
{
    double btcValue;

    size_t decimal_pos = str.find('.');

    if (decimal_pos != std::string::npos)
    {
        std::string prefix = str.substr(0, decimal_pos + 1);

        std::string suffix = str.substr(decimal_pos + 1);

        if (suffix.size() > 2)
            suffix = suffix.substr(0, 2);

        str = prefix + suffix;
    }

    std::stringstream ss(str);
    ss >> std::fixed >> std::setprecision(2) >> btcValue;

    if (Flag == true)
    {
        if (btcValue > MAX_BTC_VALUE)
        {
            std::cerr << "Error: too large number. '" << std::fixed << std::setprecision(0) << btcValue << "'." << std::endl;
            return -1;
        }
    }
    if (btcValue < MIN_BTC_VALUE)
    {
        std::cerr << "Error: not a positive number. '" << btcValue << "'." << std::endl;
        return -1;
    }
    return btcValue;
}

void BitcoinExchange::parsingFactory(std::string fileName, char delimiter)
{
    std::ifstream inputStream(fileName);
    if (!inputStream)
        throw std::string("Error: while opening input file.");

    std::string line;
    std::getline(inputStream, line);
    int count = 0;
    while (std::getline(inputStream, line))
    {
        count++;
        std::istringstream iss(line);
        std::string date, value;
        double btcValue;

        if (std::getline(iss, date, delimiter) && std::getline(iss, value))
        {
            if (isValidDate(date))
            {
                if ((btcValue = toDouble(value, false)) < 0)
                    continue;
                if (fileName == this->database)
                    this->databaseMap.insert(make_pair(date, btcValue));
                else
                {
                    if ((btcValue = toDouble(value, true)) < 0)
                        continue;

                    std::string targetKey = date;
                    std::map<std::string, double>::iterator it = this->databaseMap.lower_bound(targetKey);

                    if (it != this->databaseMap.begin())
                        it--;
                    std::cout << date << " => " << std::setw(4) << btcValue << " = " << btcValue * it->second << std::endl;
                }
            }
            else
                std::cerr << "Error: Invalid date format '" << line << "'." << std::endl;
        }
        else
            std::cerr << "Error: Invalid input format '" << line << "'." << std::endl;
    }
    if (count == 0)
    {
        inputStream.close();
        throw std::string("Error: empty file.");
    }
    inputStream.close();
}