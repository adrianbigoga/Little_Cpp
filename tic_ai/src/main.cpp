#include "board.hpp"
#include "logic.hpp"

int main()
{
    std::cout << "game";
    int l = 4;
    board b(10, 10, l, 'x', 'o');

    game(b);
    //b.display();
    return 0;
}