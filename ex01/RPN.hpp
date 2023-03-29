#ifndef RPN_HPP
#define RPN_HPP

#include <iostream>
#include <fstream>
#include <map>
#include <string>
#include <iomanip>
#include <sstream>
#include <stack>
#include <sstream>
#include <cstdlib>

class RPN
{
private:
	std::string exp;
	double resultOperation;

public:
			RPN(void);
			RPN(std::string const &exp);
			RPN(RPN const &copy);
			RPN &operator=(const RPN &rhs);
			~RPN(void);

std::string	getExp() const;
void		setExp(std::string _exp);
double		getResult() const;

bool		isOperator(std::string s);
double		performOperation(double op1, double op2, std::string op);
double		evaluateRPN();
};

#endif