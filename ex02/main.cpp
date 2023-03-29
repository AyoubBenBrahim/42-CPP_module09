#include "PmergeMe.hpp"





int main(int argc, char* argv[]) 
{
    if (argc < 2) {
        std::cerr << "Usage: PmergeMe nb nb nb" << std::endl;
        return 1;
    }

    

    // srand(time(NULL));
    // for (size_t i = 0; i < 3000 - sequence.size(); i++) {
    //     sequence.push_back(rand() % 1000000 + 1); // add random positive integers if sequence has less than 3000 numbers
    // }


PmergeMe pm(argv, argc);

    // pm.mergeInsertionSort(sequence);

    // for (size_t i = 0; i < sequence.size(); i++) {
    //     std::cout << sequence[i] << " ";
    // }
    // std::cout << std::endl;

    return 0;
}