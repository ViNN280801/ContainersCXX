#include "Grid.hpp"

int main()
{
    // Declaring a grid that stores int using default arguments for the constructor
    Grid<int> int_grid;

    // Declaring a grid 5x5 that stores double
    Grid<double> double_grid{5UL, 5UL};

    int_grid.at(0UL, 0UL) = 4;
    int x{int_grid.at(0UL, 0UL).value_or(0)};

    std::cout << x << std::endl;

    // Testing copy constructor
    Grid<int> grid2{int_grid}; 
    Grid<int> another_int_grid;

    // Testing assignment operator
    another_int_grid = grid2;

    // Testing copy constructor on another type of Grid
    Grid<int> grid3{double_grid};

    // Testing assignment operator on another type of Grid
    another_int_grid = grid3;

    return EXIT_SUCCESS;
}