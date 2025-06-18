#include <iostream>
#include <vector>
#include <queue>
#include <iomanip>
#include <random>
#include <set>


struct cell {
    int val;
    bool flag;
    bool open;
    int flags_around;
    std::vector<std::pair<int, int>> neighbours;

    explicit cell(int v = 0, bool f = false, bool o = false, int f_a = 0):
        val(v), flag(f), open(o), flags_around(f_a)
    {}
};



class Minesweeper_board {

    int len, wid, mine_count, flag_count, open_count;
    std::vector<std::vector<cell>> board;

public:

    enum class Difficulty {
        easy = 1,
        medium = 2,
        hard = 3,
    };

    Minesweeper_board(int x, int y, const Difficulty level){

        auto [l, w, m] = difficulty(level);
        len = l;
        wid = w;
        mine_count = m;
        flag_count = 0;
        open_count = 0;
        board = std::vector(wid, std::vector<cell>(len));

        for (int i = 0; i < wid; i++) {
            for (int j = 0; j < len; j++) {
                std::cout << "pos " << i << " " << j << std::endl;
                for (int a = -1; a <= 1; a++) {
                    for (int b = -1; b <= 1; b++) {
                        if ((a != 0 || b != 0) && i + a >= 0 && i + a < wid && j+b >= 0 && j+b < len) {
                            board[i][j].neighbours.emplace_back(i + a, j + b);
                            std::cout << std::setw(3) << "neighbour " << i+a << " " << j+b << std::endl;
                        }
                    }
                }
            }
        }

        std::random_device rd;                                            /*Random mine generator*/
        std::mt19937 gen(rd());
        std::uniform_int_distribution<int> dist(0, wid * len -1);

        std::set<int> positions;

        while (positions.size() < mine_count){
            int pos = dist(gen);
            positions.insert(pos);
        }

        for (auto t : positions) {
            const int row = t / len;
            const int col = t % len;
            board[row][col].val = -1;
            std::cout << "mine: " << row << " " << col << std::endl;
            for (int a = -1; a <= 1; a++) {
                for (int b = -1; b <= 1; b++) {
                    if ((a != 0 || b != 0) && row+a >= 0 && row+a < wid && col+b >= 0 && col+b < len) {
                        if (board[row+a][col+b].val != -1) {
                            board[row + a][col + b].val++;
                        }
                    }
                }
            }
        }

        std::cout << "\nFully constructed "<< std::endl;

    }

    std::vector<cell>& operator[](const int x) {
        return board[x];
    }

    [[nodiscard]] int get_width() const {return wid;}

    [[nodiscard]] int get_length() const {return len;}

    [[nodiscard]] int get_mine_count() const {return mine_count;}

    [[nodiscard]] int get_flag_count() const {return flag_count;}

    [[nodiscard]] int get_open_count() const {return open_count;}

    void open_cell(const int i, const int j) {

        board[i][j].open = true;
        open_count++;

    }

    void toggle_flag (const int i, const int j)& {

        if (board[i][j].flag == false && flag_count == mine_count) {
            std::cout << "\nNo more flags available";
            return;
        }

        board[i][j].flag = !board[i][j].flag;
        if (board[i][j].flag) {
            flag_count++;
        }
        else {
            flag_count--;
        }

        for (int a = -1; a <= 1; a++) {
            for (int b = -1; b <= 1; b++) {

                if ((a != 0 || b != 0) && i + a >= 0 && i + a < wid && j + b >= 0 && j + b < len &&(board[i + a][j + b].val != -1)) {
                    if (board[i][j].flag) {
                        board[i + a][j + b].flags_around++;
                    }
                    else{
                        board[i + a][j + b].flags_around--;
                    }
                }

            }
        }

    }


    void show_mines() {

        for (int i = 0; i < wid; i++) {
            for (int j = 0; j < len; j++) {

                if (board[i][j].val == -1) {
                    open_cell(i, j);
                }

            }
        }

    }

    void spread_open(const int i, const int j) {

        std::queue<std::pair<int, int>> q;
        std::set<std::pair<int, int>> passed;
        q.emplace(i, j);

        while (!q.empty()) {

            auto [x, y] = q.front();
            q.pop();
            open_cell(x, y);
            passed.emplace(x, y);
            if (board[x][y].val == 0) {
                for (auto [a, b]: board[x][y].neighbours) {

                    if (!passed.contains(std::make_pair(a, b)) && !board[a][b].open) {
                        passed.emplace(a, b);
                        q.emplace(a, b);
                    }

                }
            }

        }

    }

    void display() const {

        for (int i = 0; i < wid; i++) {
            std::cout << "| ";
            for (int j = 0; j < len; j++) {

                if (board[i][j].flag && !board[i][j].open) {
                    std::cout << std::setw(1) << "f" << " | ";
                    continue;
                }
                if (!board[i][j].open) {
                    std::cout << std::setw(1) << 'X' << " | ";
                    continue;
                }
                std::cout << std::setw(1) << ((board[i][j].val==-1)? '*': static_cast<char>(board[i][j].val==0?' ': '0' + board[i][j].val)) << " | ";

            }
            std::cout << std::endl << std::string(len*4 +1 , '-') << std::endl;
        }

    }

private:
    static std::tuple<int, int, int> difficulty(const Difficulty level){
        switch (level) {
            case Difficulty::easy:
                return std::make_tuple(5, 5, 5);
            case Difficulty::medium:
                return std::make_tuple(16, 16, 40);
            case Difficulty::hard:
                return std::make_tuple(30, 16, 99);
            default:
                return std::make_tuple(9, 9, 10);
        }
    }

};

void get_moves(Minesweeper_board& grid, int& row, int& col, int& move, bool& playing) {

    std::cout << "\nEnter row and column position to play: ";
    std::cin >> row >> col;

    while ((row < 0 || col < 0 || row >= grid.get_width() || col >= grid.get_length()) && (row != 100 || col != 100)) {
        std::cout << "\nEnter valid options";
        std::cin>> row >> col;
    }

    if (row == 100 && col == 100) {
        playing = false;
        return;
    }

    while (grid[row][col].open) {
        if (grid[row][col].flags_around == grid[row][col].val) {
            break;
        }
        std::cout << "\nEnter row and column position to play: ";
        std::cin >> row >> col;
    }

    std::cout << "\n1 to OPEN OR 2 to PLACE FLAG";
    std::cin >> move;

    while (move != 1 && move != 2) {
        std::cout << "\nEnter valid move: ";
        std::cin >> move;
    }
}



void game(Minesweeper_board& grid) {
    bool playing = true;
    int row, col;
    int move;
    int size = grid.get_width() * grid.get_length();

    std::cout << "\n size: " << size << std::endl;
    std::cout << "\n mine: " << grid.get_mine_count() << std::endl;

    grid.display();

    while (playing) {
        std::cout << "\nOpen count: " << grid.get_open_count() << std::endl;

        if (grid.get_open_count() == size - grid.get_mine_count()) {
            grid.display();
            std::cout <<  "\n you win ";
            return;
        }

        get_moves(grid, row, col, move, playing);

        if (move == 2) {
            grid.toggle_flag(row, col);
            // grid[row][col].flag = true;
            grid.display();
            continue;
        }

        if (!playing) return;

        if (grid[row][col].val == -1) {  // if it is a mine
            grid.show_mines();
            grid.display();
            std::cout << "game lost";
            return;
        }

        if (grid[row][col].open && grid[row][col].flags_around == grid[row][col].val) {
            for (auto [i, j]: grid[row][col].neighbours) {
                if (!grid[i][j].open){
                    grid.open_cell(i, j);
                    if (grid[i][j].val == -1) {
                        grid.show_mines();
                        grid.display();
                        std::cout << "game lost";
                        return;
                    }
                }
            }
        }

        if (grid[row][col].val == 0) {
            grid.spread_open(row, col);
        }

        grid.open_cell(row, col);

        grid.display();
    }
}


int main() {

    Minesweeper_board board(1, 2, Minesweeper_board::Difficulty::easy);

    ::game(board);

    return 0;

}