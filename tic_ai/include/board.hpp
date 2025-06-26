#pragma once

#include <iostream>
#include <vector>
#include <cmath>

class board
{
private:
    std::vector<std::vector<char>> grid; // 2D vector to represent the board
    // Size of the board (e.g., 3 for a 3x3 Tic-Tac-Toe board)
    int max_moves;
    int filled;
    char p1, p2;
    int limit;

public:
    board(int i = 3, int j = 3, int l = 3, char p_1 = 'x' ,char p_2 = 'o'): 
        max_moves(i*j), limit(l), grid(std::vector<std::vector<char>>(i, std::vector<char>(j, ' '))),
        p1(p_1), p2(p_2), filled(0)
    {}


    std::pair<char, char> chars(){
        return std::make_pair(p1,p2);
    }

    int get_max_moves() const{ return this-> max_moves;}

    int get_filled() const { return this->filled; }

    void display() const;

    bool move(const int i, const int j, const char c) {
        if (c == ' ')
        {
            this->grid[i][j] = ' ';
            filled--;
            return true;
        }
        if(this->grid[i][j] != ' ') return false;
        this->grid[i][j] = c;
        filled++;
        return true;
    }

    bool in_range_x(const int i){
        return i >= 0 && i < this->grid.size();
    }

    bool in_range_y(const int j){
        return j >= 0 && j < this->grid[0].size();
    }

    bool check_win(int, int, char);

    long long evaluate(int i, int j, char c);

    long long evaluate_board();

    long long minimax(int depth, bool is_maximizing, long long alpha, long long beta);

    std::pair<int, int> best_move(bool);

};

