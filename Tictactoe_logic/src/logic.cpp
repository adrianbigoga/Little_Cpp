#include "logic.hpp"

void game(Tictactoe& board){
    char p1 = 'x', p2 = 'o', cp;
    int moves = 0;
    int max_moves = board.get_max_moves();
    cp = p2;
    board.display();
    while (moves < max_moves){
        int i, j;
        cp = (cp == p1)? p2: p1;
        std::cout << "\nenter i and j for " << cp << "\n";
        std::cin >> i >> j;

        while (!board.in_range_x(i) || !board.in_range_y(j)){
            std::cout << "\nEnter valid coordinates";
            std::cin >> i >> j;
        }
        while (!board.move(i, j, cp)){
            std::cout << "\nmove invalid: cell occupied, try again";
            std::cin >> i >> j;
        }

        board.display();

        if (board.check_win(i, j, cp)){
            std::cout << cp << " wins";
            return;
        }
        moves++;
    }


    std::cout <<" draw";

}