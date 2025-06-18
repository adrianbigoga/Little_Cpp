#include "tokenizer.hpp"
#include "solver.hpp"
#include <string>
#include <sstream>

std::map<std::string, float> operators = 
{
    {"+", 1}, {"-", 1}, {"*", 2}, {"/", 2}, {"(", 0}, {")", 0}, {"^", 3}, {"sin", 4}, {"tan", 4}, {"cos", 4}, {"ln", 4}, {"sqrt", 4}
};

std::map<std::string, std::string> constants =
{
    {"e", "2.7182818"}, {"pi", "3.1415926"}
};


std::vector<std::string> tokenize (std::string s) 
{
    std::vector<std::string> v;
    int i = 0;
    int n = s.length();

    while (i < n) 
    {
        std::string str4 = s.substr(i, 4);
        if (constants.find(str4) != constants.end()){
            v.push_back(constants[str4]);
            i += 2;
            continue;
        }
        if (operators.find(str4) != operators.end())
        {
            v.push_back(str4);
            i += 4;
            continue;
        }

        std::string str2 = s.substr(i, 2);
        if (constants.find(str2) != constants.end()){
            v.push_back(constants[str2]);
            i += 2;
            continue;
        }
        if (operators.find(str2) != operators.end())
        {
            v.push_back(str2);
            i += 2;
            continue;
        }

        std::string str3 = s.substr(i, 3);
        if (constants.find(str3) != constants.end()){
            v.push_back(constants[str3]);
            i += 3;
            continue;
        }
        if (operators.find(str3) != operators.end())
        {
            v.push_back(str3);
            i += 3;
            continue;
        }

        std::string str = std::string(1, s[i]);
        if (constants.find(str) != constants.end()){
            v.push_back(constants[str]);
            i ++;
            continue;
        }
        if (operators.find(str) != operators.end() || operators.find(str2) != operators.end() || operators.find(str3) != operators.end())
        {   
            v.push_back(str);
            i++;
            continue;
        }
        if (s[i] == ' ') 
        {
            i++;
            continue;
        }
        std::string token;
        while (i < n && isdigit(s[i])) 
        {
            token += s[i];
            i++;
            if (s[i] == '.')
            {
                token += s[i];
                i++;
                while (i < n && isdigit(s[i])) {
                    token += s[i];
                    i++;
                }
            }
        }
        if (!token.empty()) 
        {
            v.push_back(token);
            continue;
        }
        i++;
    }
    return v;
}

std::vector<std::string> to_postfix (std::vector<std::string> v) 
{
    std::vector<std::string> output, sign;
    for (auto& token : v)
    {
        if (operators.find(token) != operators.end()) 
        {
            if (token == "(") 
            {
                sign.push_back(token);
                continue;
            }
            if (token == ")") 
            {
                while (!sign.empty() && sign.back() != "(") 
                {
                    output.push_back(sign.back());
                    sign.pop_back();
                }

                if (!sign.empty())
                {
                    sign.pop_back();
                }

                continue;
            }
            while (!sign.empty() && operators[sign.back()] >= operators[token] && sign.back() != "(") 
            {
                output.push_back(sign.back());
                sign.pop_back();
            }

            sign.push_back(token);

            continue;
        }
        
        output.push_back(token);
    }
    while (!sign.empty()) 
    {
        output.push_back(sign.back());
        sign.pop_back();
    }

    return output;
}