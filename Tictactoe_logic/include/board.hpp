#pragma once

#include <iostream>
#include <vector>
#include <string>
#include <optional>

class Tictactoe{
    std::vector<std::vector<char>> grid;
    int limit;
    int max_moves;

    public:
    Tictactoe(int i = 3, int j = 3): 
        max_moves(i*j), limit(std::min(i, j)), grid(std::vector<std::vector<char>>(i, std::vector<char>(j, ' ')))
    {}

    int get_max_moves() const{ return this-> max_moves;}

    void display() const;

    bool move(const int i, const int j, const char c) {
        if(this->grid[i][j] != ' ') return false;
        this->grid[i][j] = c;
        return true;
    }

    bool in_range_x(const int i){
        return i >= 0 && i < this->grid.size();
    }

    bool in_range_y(const int j){
        return j >= 0 && j < this->grid[0].size();
    }

    bool check_move(const int i, const int j);

    bool check_win(const int i, const int j, const char c);

};

void game(Tictactoe& board);