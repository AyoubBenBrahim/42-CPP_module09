#include "RPN.hpp"

int main(int argc, char *argv[])
{
    if (argc < 2)
    {
        std::cerr << "Usage: \n     " << argv[0] << " RPN_expression" << std::endl;
        exit(1);
    }

    std::string expr = argv[1];
    
    RPN rpnCalc(expr);

    std::cout << std::setprecision(4) << rpnCalc.getResult() << std::endl;

    return 0;
}