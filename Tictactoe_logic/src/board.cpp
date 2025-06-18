#include "board.hpp"

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


bool Tictactoe::check_win(const int i, const int j, const char c){
    int count = 1;
    int i_1 = i+1, i_2 = i-1;

    while ((in_range_x(i_1) || in_range_x(i_2)) && count < this->limit){
        if (in_range_x(i_1)){
            if (this->grid[i_1][j] == c){
                std::cout << "expanding down\n";
                count ++;
            }
            i_1 ++;
        }
        if (in_range_x(i_2)){
            if(this->grid[i_2][j] == c){
                count ++;
                std::cout << "expanding up\n";
            }
            i_2 --;
        }
    }

    if (count >= this->limit) return true;

    count = 1;
    int j_1 = j+1, j_2 = j-1;
    while ((in_range_y(j_1) || in_range_y(j_2)) && count < this->limit){
        if (in_range_y(j_1)){
            if(this->grid[i][j_1] == c){
                count ++;
                std::cout << "expanding right\n";
            }
            j_1 ++;
        }
        if (in_range_y(j_2)){
            if(this->grid[i][j_2] == c){
                count ++;
                std::cout << "expanding left\n";
            }
            j_2 --;
        }
    }

    if (count >= this->limit) return true;

    count = 1;
    i_1 = i+1, i_2 = i-1, j_1 = j+1, j_2 = j-1;
    while (((in_range_x(i_1) && in_range_y(j_1)) || (in_range_x(i_2) && in_range_y(j_2))) && count < this->limit){
        if (in_range_x(i_1) && in_range_y(j_1)){
            if (this->grid[i_1][j_1] == c){
                count ++;
                std::cout << "expanding down, right\n";
            }
            i_1 ++;
            j_1 ++;
        }
        if (in_range_x(i_2) && in_range_y(j_2)){
            if (this->grid[i_2][j_2] == c){
                count ++;
                std::cout << "expanding up, left\n";
            }
            i_2 --;
            j_2 --;
        }
    }

    if (count >= this->limit) return true;

    count = 1;
    i_1 = i+1, i_2 = i-1, j_1 = j-1, j_2 = j+1;
    while (((in_range_x(i_1) && in_range_y(j_1)) || (in_range_x(i_2) && in_range_y(j_2))) && count < this->limit){
        if (in_range_x(i_1) && in_range_y(j_1)){
            if (this->grid[i_1][j_1] == c){
                count ++;
                std::cout << "expanding down, left\n";
            }
            i_1 ++;
            j_1 --;
        }
        if (in_range_x(i_2) && in_range_y(j_2)){
            if (this->grid[i_2][j_2] == c){
                count ++;
                std::cout << "expanding up, right\n";
            }
            i_2 --;
            j_2 ++;
        }
    }

    if (count >= this->limit) return true;

    return false;
}


