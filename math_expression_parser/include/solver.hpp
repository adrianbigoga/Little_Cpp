
#pragma once

#include <iostream>
#include <vector>
#include <string>


bool is_plus (std::string);

bool is_minus (std::string);

bool is_prod (std::string);

bool is_div (std::string);

bool is_pow (std::string);

bool is_sin (std::string);

bool is_cos (std::string);

bool is_tan (std::string);

bool is_ln (std::string);

bool is_sqrt (std::string);

bool is_operator (std::string);

void unit_solve (std::vector<std::string>&, int&);

std::string solver (std::vector<std::string>);

float compute (std::string);
