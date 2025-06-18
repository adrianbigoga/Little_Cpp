#pragma once

#include <iostream>
#include <vector>
#include <map>

extern std::map<std::string, float> operators;
extern std::map<std::string, std::string> constants;

std::vector<std::string> tokenize (std::string);

std::vector<std::string> to_postfix (std::vector<std::string>);