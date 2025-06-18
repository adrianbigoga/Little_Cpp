#include "board.hpp"
#include "logic.hpp"

int main(){
    Tictactoe board(4,4);
    board.display();

    game(board);
}