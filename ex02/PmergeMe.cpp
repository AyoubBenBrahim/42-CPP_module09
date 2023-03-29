#include <iostream>
#include <vector>
#include <deque>
#include <cstdlib>
#include <ctime>

#include "PmergeMe.hpp"

static long val;

PmergeMe::PmergeMe() {}

PmergeMe::PmergeMe(char *_argv[], int _argc) : argv(_argv), argc(_argc)
{
    PmergeHandler(argv, argc);

    printContainer(this->veq_sequence, "Before");

    double elapsed_time_vec = sortVector();
    double elapsed_time_deq = sortDequeu();

    printContainer(this->veq_sequence, "After");

    printTimeComplexity(this->veq_sequence, "std::vector", elapsed_time_vec);
    printTimeComplexity(this->deq_sequence, "std::deque ", elapsed_time_deq);
}

PmergeMe::PmergeMe(PmergeMe const &copy)
{
    argv = copy.argv;
    argc = copy.argc;
    veq_sequence = copy.veq_sequence;
    deq_sequence = copy.deq_sequence;
}

PmergeMe::~PmergeMe(void) {}

PmergeMe &PmergeMe::operator=(PmergeMe const &rhs)
{
    if (this == &rhs)
        return *this;

    argv = rhs.argv;
    argc = rhs.argc;
    veq_sequence = rhs.veq_sequence;
    deq_sequence = rhs.deq_sequence;

    return *this;
}

template <typename T>
void PmergeMe::printTimeComplexity(const T &container, std::string container_name, double elapsed_time)
{
    std::cout << "Time to process a range of " << container.size() 
              << " elements with " << container_name << " : "
              << std::fixed << std::setprecision(5) << elapsed_time << " us" << std::endl;
}

template <typename T>
void PmergeMe::printContainer(const T &container, std::string prefixMsg)
{
    typename T::const_iterator it;
    std::cout << std::setw(8) << prefixMsg + ": ";
    for (it = container.begin(); it != container.end(); ++it)
        std::cout << *it << " ";
    std::cout << std::endl;
}

bool PmergeMe::is_integer(const std::string &str)
{
    if (str.empty())
        return false;
    for (size_t i = 0; i < str.length(); i++)
    {
        if (!isdigit(str[i]) && !(i == 0 && (str[i] == '+' || str[i] == '-')))
            return false;
    }
    char *endptr;
    val = std::strtol(str.c_str(), &endptr, 10);
    return (*endptr == '\0' && val >= 0);
}

void PmergeMe::PmergeHandler(char *argv[], int argc)
{
    for (int i = 1; i < argc; i++)
    {
        if (!is_integer(argv[i]))
        {
            std::cerr << "Error: Input contains non-numeric/negative elements." << std::endl;
            exit(0);
        }
        this->veq_sequence.push_back(val);
    }

    std::copy(this->veq_sequence.begin(), this->veq_sequence.end(), std::back_inserter(this->deq_sequence));
}

template <typename T>
void PmergeMe::insertionSort(T &container)
{
    for (size_t i = 1; i < container.size(); i++)
    {
        long temp = container[i];
        long j = i - 1;
        while (j >= 0 && container[j] > temp)
        {
            container[j + 1] = container[j];
            j--;
        }
        container[j + 1] = temp;
    }
}

template <typename T>
void PmergeMe::mergeInsertionSort(T &container)
{
    if (container.size() <= THRESHOLD)
        insertionSort(container);
    else
    {
        T left(container.begin(), container.begin() + container.size() / 2);
        T right(container.begin() + container.size() / 2, container.end());
        mergeInsertionSort(left);
        mergeInsertionSort(right);
        std::merge(left.begin(), left.end(), right.begin(), right.end(), container.begin());
    }
}

double PmergeMe::sortVector()
{
    clock_t start = clock();

    mergeInsertionSort(this->veq_sequence);

    clock_t end = clock();

    double elapsed_time = 1000000 * (double)(end - start) / CLOCKS_PER_SEC;
    
    return elapsed_time;
}

double PmergeMe::sortDequeu()
{
    clock_t start = clock();

    mergeInsertionSort(this->deq_sequence);

    clock_t end = clock();

    double elapsed_time = 1000000 * (double)(end - start) / CLOCKS_PER_SEC;
    
    return elapsed_time;
}