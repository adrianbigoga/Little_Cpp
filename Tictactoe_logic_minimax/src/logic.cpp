#include "logic.hpp"

void game(Tictactoe& board){
    std::pair<char, char> p = board.chars();
    char p1 = p.first, p2 = p.second, cp;
    int moves = 0;
    int score = 0;
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

        std::pair<bool, int> result (board.check_win(i, j, cp));

        if (result.first){
            std::cout << cp << " wins, score : " << result.second << "\n";
            return;
        }
        std::cout << "score: " << std::get<1>(result)<< "\n";
        score = 0;
        moves++;
    }


    std::cout <<" draw";

}