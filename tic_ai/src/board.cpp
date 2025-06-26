
#include "board.hpp"

#include "board.hpp"

void board::display() const{
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

bool board::check_win(int i, int j, char c)
{
    std::vector<std::pair<int, int>> directions = {
        {1, 0},  // Vertical
        {0, 1},  // Horizontal
        {1, 1},  // Diagonal
        {1, -1}  // Diagonal
    };

    

    for (const auto [dx, dy]: directions)
    {
        int count = 1;
        int x = i + dx;
        int y = j + dy;

        while (in_range_x(x) && in_range_y(y) && grid[x][y] == c)
        {
            count += 1;
            x += dx;
            y += dy;
        }

        x = i - dx;
        y = j - dy;

        while (in_range_x(x) && in_range_y(y) && grid[x][y] == c)
        {
            count += 1;
            x -= dx;
            y -= dy;
        }

        if (count >= limit) {
            return true;
        }
    }
    return false;
}

long long board::evaluate(int i, int j, char c)
{
    long long final_score = 0;

    std::vector<std::pair<int, int>> directions = {
        {1, 0},  // Vertical
        {0, 1},  // Horizontal
        {1, 1},  // Diagonal
        {1, -1}  // Diagonal
    };

    

    for (const auto [dx, dy]: directions)
    {
        long long score = 0;
        int count = 1;
        bool open_1 = true;
        bool open_2 = true;
        int x = i + dx;
        int y = j + dy;

        while (in_range_x(x) && in_range_y(y) && grid[x][y] == c)
        {
            count += 1;
            x += dx;
            y += dy;
        }
        if ((!in_range_x(x) || !in_range_y(y)) || grid[x][y] != ' ')
        {
            open_1 = false;
        }
        else
        {
            open_1 = true;
        }

        x = i - dx;
        y = j - dy;
        while (in_range_x(x) && in_range_y(y) && grid[x][y] == c)
        {
            count += 1;
            x -= dx;
            y -= dy;
        }

        if ((!in_range_x(x) || !in_range_y(y)) || grid[x][y] != ' ')
        {
            open_2 = false;
        }
        else
        {
            open_2 = true;
        }

        if (count >= limit)
        { // Winning move
            score = std::pow(10, limit - 1); // Winning move
            final_score += score;
            return final_score;
        }

        score += std::pow(10, count - 1);
         
        if (open_1 && open_2)
        {
            score *= 2;
        }
        else if (open_1 || open_2)
        {
            score *= 1;
        }
        else
        {
            score *= 0;
        }

        final_score += score;
    }

    return final_score;
}

long long board::evaluate_board()
{
    long long p1_score = 0;
    long long p2_score = 0;

    for (int i = 0; i < grid.size(); ++i)
    {
        for (int j = 0; j < grid[0].size(); ++j)
        {
            if (grid[i][j] == p1)
            {
                p1_score += evaluate(i, j, p1);
            }
            else if (grid[i][j] == p2)      
            {
                p2_score += evaluate(i, j, p2);
            }
        }
    }
    return p1_score - p2_score;
}

long long board::minimax(int depth, bool is_maximising, long long alpha = LLONG_MIN, long long beta = LLONG_MAX)
{
    if (filled >= max_moves || depth == 0)
    {
        return evaluate_board();
    }

    long long best_score;
    if (is_maximising)
    {
        best_score == LLONG_MIN;
        for (int i = 0; i < grid.size(); ++i)
        {
            for (int j = 0; j < grid.size(); ++j)
            {
                if (grid[i][j] == ' ')
                {
                    grid[i][j] = p1;
                    filled++;
                    long long score = minimax(depth - 1, !is_maximising, alpha, beta);
                    grid[i][j] = ' ';
                    alpha = std::max(alpha, score);
                    best_score = std::max(best_score, score);

                    if (alpha >= beta) break;
                }
            }
            if (alpha >= beta) break;
        }
    }
    else
    {
        best_score = LLONG_MAX;
        for (int i = 0; i < grid.size(); ++i)
        {
            for (int j = 0; j < grid.size(); ++j)
            {
                if (grid[i][j] == ' ')
                {
                    grid[i][j] = p2;
                    filled++;
                    long long score = minimax(depth - 1, !is_maximising, alpha, beta);
                    grid[i][j] = ' ';

                    best_score = std::min(best_score, score);

                    beta = std::min(beta, score);

                    if (beta <= alpha) break;
                }
            }

            if (beta <= alpha) break;
        }
    }
    return best_score;
}

std::pair<int, int> board::best_move(bool is_maximising)
{
    long long best_score = is_maximising? LLONG_MIN : LLONG_MAX;
    std::pair<int, int> best_move = {-1, -1};

    for (int i = 0; i < grid.size(); ++i)
    {
        for (int j = 0; j < grid[0].size(); ++j)
        {
            if (grid[i][j] == ' ')
            {
                char cp = is_maximising ? p1 : p2;

                grid[i][j] = cp;
                filled ++;
                long long score = minimax(4, !is_maximising);

                grid[i][j] = ' ';

                if ((is_maximising && score > best_score) || 
                   (!is_maximising && score < best_score))
                {
                    best_score = score;
                    best_move = {i, j};
                }
            }
        }
    }

    return best_move;
}