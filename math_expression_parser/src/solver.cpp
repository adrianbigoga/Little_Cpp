#include "solver.hpp"
#include "tokenizer.hpp"
#include <functional>
#include <cmath>
#include <sstream>
#include <iomanip>

std::vector<std::function<bool(std::string)>> signs=
{
    is_plus, is_minus, is_prod, is_div, is_pow, is_sin, is_cos, is_tan, is_ln, is_sqrt
};

bool is_plus (std::string s)
{
    return s == "+";
}

bool is_minus (std::string s)
{
    return s == "-";
}

bool is_prod (std::string s)
{
    return s == "*";
}

bool is_div (std::string s)
{
    return s == "/";
}

bool is_pow (std::string s)
{
    return s == "^";
}

bool is_sin (std::string s)
{
    return s == "sin";
}

bool is_cos (std::string s)
{
    return s == "cos";
}

bool is_tan (std::string s)
{
    return s == "tan";
}

bool is_ln (std::string s)
{
    return s == "ln";
}

bool is_sqrt (std::string s)
{
    return s == "sqrt";
}

bool is_operator (std::string s) 
{
    for(std::function<bool(std::string)> func: signs)
    {
        if (func(s)) return true;
    }
    return false;
}

void unit_solve(std::vector<std::string>& v, int& index)
{
    std::string sign = v[index];

    if (is_plus(sign) || is_minus(sign))
    {
        float left = std::stof(v[index - 2]);
        float right = std::stof(v[index - 1]);
        float ans = is_plus(sign) ? left + right : left - right;
        v.erase(v.begin() + index - 2, v.begin() + index + 1);
        v.insert(v.begin() + index-2, std::to_string(ans));
        index -= 2;
        return ;
    }

    if (is_prod(sign) || is_div(sign))
    {
        float left = std::stof(v[index-2]);
        float right = std::stof(v[index-1]);
        float ans = is_prod(sign) ? left * right : left / right;
        v.erase(v.begin() + index - 2, v.begin() + index + 1);
        v.insert(v.begin() + index - 2, std::to_string(ans));
        index -= 2;
        return ;
    }

    if (is_pow(sign))
    {
        float left = std::stof(v[index-2]);
        float right = std::stof(v[index-1]);
        float ans = std::pow(left, right);
        v.erase(v.begin() + index - 2, v.begin() + index + 1);
        v.insert(v.begin() + index - 2, std::to_string(ans));
        index -= 2;
        return ;
    }

    if (is_sin(sign))
    {
        float arg = std::stof(v[index-1]);
        float ans = sin(arg);
        v.erase(v.begin() + index - 1, v.begin() + index + 1);
        v.insert(v.begin() + index - 1, std::to_string(ans));
        index -= 1;
        return ;
    }

    if (is_cos(sign))
    {
        float arg = std::stof(v[index-1]);
        float ans = cos(arg);
        v.erase(v.begin() + index - 1, v.begin() + index + 1);
        v.insert(v.begin() + index - 1, std::to_string(ans));
        index -= 1;
        return ;
    }

    if (is_tan(sign))
    {
        float arg = std::stof(v[index-1]);
        float ans = tan(arg);
        v.erase(v.begin() + index - 1, v.begin() + index + 1);
        v.insert(v.begin() + index - 1, std::to_string(ans));
        index -= 1;
        return ;
    }

    if (is_ln(sign))
    {
        float arg = std::stof(v[index-1]);
        float ans = log(arg);
        v.erase(v.begin() + index - 1, v.begin() + index + 1);
        v.insert(v.begin() + index - 1, std::to_string(ans));
        index -= 1;
        return ;
    }

    if (is_sqrt(sign))
    {
        float arg = std::stof(v[index-1]);
        float ans = sqrt(arg);
        v.erase(v.begin() + index - 1, v.begin() + index + 1);
        v.insert(v.begin() + index - 1, std::to_string(ans));
        index -= 1;
        return ;
    }
}

std::string solver (std::vector<std::string> list)
{
    std::vector v(list);
    int index = 0;
    while (v.size() != 1)
    {
        while (index < v.size() && !is_operator(v[index]))
        {
            index ++;
            
        }
        if (index == v.size()) 
        {
            std::stringstream ss;
            ss << std::setprecision(2) << v[0];
            return ss.str();
        }

        unit_solve(v, index);
    }
    std::ostringstream ss;
    ss << std::fixed << std::setprecision(2) << v[0];
    return ss.str();
}

float compute (std::string s)
{
    std::vector v(tokenize(s));

    v = to_postfix(v);

    std::string str = solver(v);
    
    float answer = std::stof(str);

    return answer;
}


