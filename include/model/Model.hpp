//
// Created by nico on 11/9/24.
//

#ifndef MODEL_HPP
#define MODEL_HPP
#include "Grid.hpp"

class Model {
    Grid grid;
public:
    Model();

    Grid& getGrid();
    const Grid& getGrid() const;
};

#endif //MODEL_HPP
