#include "sudoku.h"

std::vector<std::vector<int>> sudoku::generateGrid(std::string difficulty)
{
    std::vector<std::vector<int>> grid(9);

    for (auto i = 0; i < 9; i++)
    {
        std::vector<int> vec(9, 0);

        grid[i] = vec;
    }


    return grid;
}

void sudoku::printGrid(std::vector<std::vector<int>> grid)
{
    for (auto vec: grid)
    {
        for (auto num: vec)
        {
            std::cout << num << " ";
        }
        std::cout << std::endl;
    }
}
