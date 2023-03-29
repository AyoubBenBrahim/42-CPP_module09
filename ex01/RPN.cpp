#include "RPN.hpp"

RPN::RPN() {}

RPN::RPN(std::string const &_exp) : exp(_exp)
{
    this->resultOperation = evaluateRPN();
}

RPN::RPN(RPN const &copy) : exp(copy.exp), resultOperation(copy.resultOperation) {}

RPN::~RPN(void) {}

std::string RPN::getExp() const { return this->exp; }
double RPN::getResult() const { return this->resultOperation; }
void RPN::setExp(std::string _exp) { this->exp = _exp; }

RPN &RPN::operator=(RPN const &rhs)
{
    if (this == &rhs)
        return *this;

    this->resultOperation = rhs.resultOperation;
    this->setExp(rhs.getExp());
    return *this;
}

bool RPN::isOperator(std::string s)
{
    return (s == "+" || s == "-" || s == "*" || s == "/");
}

double RPN::performOperation(double op1, double op2, std::string _operator)
{
    double res;

    switch (_operator[0])
    {
    case '+':
        res = op1 + op2;
        break;
    case '-':
        res = op1 - op2;
        break;
    case '*':
        res = op1 * op2;
        break;
    case '/':
        if (op2 != 0)
            res = op1 / op2;
        else
        {
            std::cerr << "Error: Divide by 0" << std::endl;
            exit(1);
        }
        break;
    default:
        std::cerr << "Error: Invalid operator: " << _operator << std::endl;
        exit(1);
        break;
    }

    return res;
}

double RPN::evaluateRPN()
{
    std::stack<double> stak;

    std::istringstream iss(getExp());
    std::string token;
    while (iss >> token)
    {
        if (token.length() == 1 && isdigit(token[0]))
            stak.push(atoi(token.c_str()));
        else if (token.length() == 1 && isOperator(token))
        {
            if (stak.size() < 2)
            {
                std::cerr << "Format Error: " << getExp() << std::endl;
                exit(1);
            }
            double op2 = stak.top();
            stak.pop();
            double op1 = stak.top();
            stak.pop();
            double res = performOperation(op1, op2, token);
            stak.push(res);
        }
        else
        {
            std::cerr << "Format Error: " << getExp() << std::endl;
            exit(1);
        }
    }

    if (stak.size() != 1)
    {
        std::cerr << "Format Error: " << getExp() << std::endl;
        exit(1);
    }

    return stak.top();
}