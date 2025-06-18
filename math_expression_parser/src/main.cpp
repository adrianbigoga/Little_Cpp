#include "tokenizer.hpp"
#include "solver.hpp"
#include <cmath>

int main () {
    std::string exp;   

    exp = "ln(2) + 3 * sqrt(4) - 5 / 2 + 6 ^ 2 - 7 * 8 + 9 * e ^ 2"; 

    std::cout << exp ;

    std::cout << " = " << compute(exp);
}