#include "board.hpp"
#include "logic.hpp"

int main(){
    Tictactoe board(4, 4, 'x', 'o');

    game(board);
}