#include "tokenizer.hpp"
#include "solver.hpp"
#include <cmath>

int main () {
    std::string exp;   

    exp = "ln(0)"; 

    std::cout << exp ;

    std::cout << " = " << compute(exp);
}