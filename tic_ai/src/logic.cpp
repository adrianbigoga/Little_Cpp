#include "logic.hpp"

void game(board& board){
    std::pair<char, char> p = board.chars();
    char p1 = p.first, p2 = p.second, cp;
    int moves = 0;
    int max_moves = board.get_max_moves();
    cp = p2;
    board.display();
    while (moves < max_moves){
        int i, j;
        cp = (cp == p1)? p2: p1;
        std::cout << "\nenter i and j for " << cp << "\n";

        if (cp == p2) {
            std::cout << "AI is making a move...\n";
            auto [x, y] = board.best_move(true);
            i = x;
            j = y;
            std::cout << "AI chose: " << i << ", " << j << "\n";
        } else {
            std::cout << "Player's turn\n";
        }
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
            std::cout << board.evaluate_board() << std::endl;
            std::cout << cp << " wins";
            return;
        }

        std::cout << board.evaluate_board() << std::endl;
        moves++;
    }


    std::cout <<" draw";

}