//
// Created by nico on 11/26/24.
//
#include "FileHandler.hpp"

#include <fstream>
#include <iostream>

#include "Constants.hpp"

void FileHandler::saveGameState(int score) {
    std::ofstream out_file(Constants::SCORE_FILE_NAME);

    if(out_file.is_open()) {
        out_file << score;
        out_file.close();
    } else {
        std::cerr << "Failed to open file." << std::endl;
    }
}

int FileHandler::loadGameState() {
    std::ifstream in_file(Constants::SCORE_FILE_NAME);
    std::string line;
    if(in_file.is_open()) {
        std::getline(in_file, line);
        in_file.close();
    } else {
        std::cerr << "Failed to open file. Creating file." << std::endl;

        std::ofstream new_file(Constants::SCORE_FILE_NAME);
        if(new_file.is_open()) {
            new_file << "0";
            new_file.close();
            line = "0";
        } else {
            throw::std::runtime_error("File creation was not possible. Aborting.");
        }
    }

    return std::stoi(line);
}
