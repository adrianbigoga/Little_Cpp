#pragma once

#include "board.hpp"
#include <iostream>
#include <vector>

class cpu
{
    Tictactoe memory;
    char p;

    public:
    cpu(Tictactoe& t, char c): memory(t), p(c) {}

    std::pair<int, int> best_move(Tictactoe& t);
    
};