#ifndef SUDOKU_H
#define SUDOKU_H

#include <string>
#include <vector>
#include <cstdlib>
#include <iostream>

class sudoku
{
    std::string difficulty;
public:
    std::vector<std::vector<int>> generateGrid(std::string difficulty);
    void printGrid(std::vector<std::vector<int>> grid);

};

#endif // SUDOKU_H
