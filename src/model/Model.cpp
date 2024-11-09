//
// Created by nico on 11/9/24.
//
#include "Model.hpp"

Model::Model(): grid(Grid()) { }

Grid& Model::getGrid() {
    return grid;
}

const Grid& Model::getGrid() const {
    return grid;
}
