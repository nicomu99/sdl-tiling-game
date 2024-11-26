//
// Created by nico on 11/26/24.
//

#ifndef FILEHANDLER_HPP
#define FILEHANDLER_HPP

class FileHandler {
public:
    static void saveGameState(int score);
    static int loadGameState();
};

#endif //FILEHANDLER_HPP
