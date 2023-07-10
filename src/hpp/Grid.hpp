#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <chrono>
#include <thread>
#include "Shape.hpp"


const int GRID_HEIGHT = 20;
const int GRID_WIDTH = 10;


class Grid{

    public:
        Grid();
        void printGrid();
        void checkGrid(bool instant=false);
        void moveLeft();
        void moveRight();
        void froze();
        void lineCheck();
        void deleteLine(int i);
        void drawActual(int a=0, int b=3);
        void turnActual();
        void restart();
        Shape getAcutal();
        Shape getNext();
        std::vector<std::vector<int>>& getGrid();
        int getScore();
        bool getLoose();
    private:
        bool loose = false;
        Shape actual;
        Shape next;
        int score=0;
        std::vector<std::vector<int>> grid;    

};