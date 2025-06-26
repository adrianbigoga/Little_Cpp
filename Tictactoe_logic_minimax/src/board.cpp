#include "board.hpp"

Tictactoe::Tictactoe(const Tictactoe& t):
    grid(t.grid), p1(t.p1), p2(t.p2), limit(t.limit), max_moves(t.max_moves) {}

void Tictactoe::display() const{
    std::string line(this->grid[0].size() * 4, '-');
    line+='-';

    for (auto row: this->grid){
        std::cout << std::endl << line << std::endl << "| ";
        
        for (auto c: row){

            std::cout << c << " | ";

        }
    }

    std::cout << std::endl << line << std::endl;
}


bool Tictactoe::check_move(const int i, const int j){

    return in_range_x(i) && in_range_y(j);
}


std::pair<bool, int> Tictactoe::check_win(const int i, const int j, const char c){
    int score = 0;
    int count = 1;
    int i_1 = i+1, i_2 = i-1;

    int a = 1;
    while ((in_range_x(i_1) || in_range_x(i_2)) && count < this->limit){
        if (in_range_x(i_1)){
            if (this->grid[i_1][j] == c){
                // std::cout << "expanding down\n";
                score += a;
                a++;
                count ++;
                i_1 ++;
            }
            else {
                i_1 = -1; // stop expanding down
            }
            
        }
        if (in_range_x(i_2)){
            if(this->grid[i_2][j] == c){
                count ++;
                score += a;
                a++;
                i_2 --;
                // std::cout << "expanding up\n";
            }
            else {
                i_2 = -1; // stop expanding up
            }
        }
    }

    if (count >= this->limit) return std::make_pair(true, score);

    count = 1;
    int j_1 = j+1, j_2 = j-1;

    a = 1;
    while ((in_range_y(j_1) || in_range_y(j_2)) && count < this->limit){
        
        if (in_range_y(j_1)){
            if(this->grid[i][j_1] == c){
                count ++;
                score += a;
                a ++;
                // std::cout << "expanding right\n";
                j_1 ++;
            }
            else {
                j_1 = -1; // stop expanding right
            }
        }
        if (in_range_y(j_2)){
            if(this->grid[i][j_2] == c){
                count ++;
                score += a;
                a ++;
                j_2 --;
                // std::cout << "expanding left\n";
            }
            else {
                j_2 = -1; // stop expanding left
            }
            
        }
    }

    if (count >= this->limit) return {true, score};

    count = 1;
    i_1 = i+1, i_2 = i-1, j_1 = j+1, j_2 = j-1;
    
    a = 1;
    while (((in_range_x(i_1) && in_range_y(j_1)) || (in_range_x(i_2) && in_range_y(j_2))) && count < this->limit){
        
        if (in_range_x(i_1) && in_range_y(j_1)){
            if (this->grid[i_1][j_1] == c){
                count ++;
                score += a;
                a ++;
                i_1 ++;
                j_1 ++;
                // std::cout << "expanding down, right\n";
            }
            else {
                i_1 = -1; // stop expanding down, right
                j_1 = -1;
            }
            
        }
        if (in_range_x(i_2) && in_range_y(j_2)){
            if (this->grid[i_2][j_2] == c){
                count ++;
                score += a;
                a ++;
                i_2 --;
                j_2 --;
                // std::cout << "expanding up, left\n";
            }
            else {
                i_2 = -1; // stop expanding up, left
                j_2 = -1;
            }
        }
    }

    if (count >= this->limit) return std::make_pair(true, score);

    count = 1;
    i_1 = i+1, i_2 = i-1, j_1 = j-1, j_2 = j+1;

    a = 1;
    while (((in_range_x(i_1) && in_range_y(j_1)) || (in_range_x(i_2) && in_range_y(j_2))) && count < this->limit){
        if (in_range_x(i_1) && in_range_y(j_1)){
            if (this->grid[i_1][j_1] == c){
                count ++;
                score += a;
                a ++;
                i_1 ++;
                j_1 --;
                // std::cout << "expanding down, left\n";
            }
            else {
                i_1 = -1; // stop expanding down, left
                j_1 = -1;
            }
            
        }
        if (in_range_x(i_2) && in_range_y(j_2)){
            if (this->grid[i_2][j_2] == c){
                count ++;
                score += a;
                a ++;
                i_2 --;
                j_2 ++;
                // std::cout << "expanding up, right\n";
            }
            else {
                i_2 = -1; // stop expanding up, right
                j_2 = -1;
            }
        }
    }

    if (count >= this->limit) return {true, score};

    return {false, score};
}


