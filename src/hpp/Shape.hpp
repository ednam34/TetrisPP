#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <random>
#include <ctime>

const int SIZE=3;

enum piece{I,J,L,O,Z,S,T};

class Shape{
    public:
        Shape(piece i);
        Shape();
        void SetMatrix();
        std::vector<std::vector<int>>& getMatrix();
        void setShape();
        void printMatrix();
        void cleanShape();
        void setXY(int x, int y);
        int getX();
        void setX(int x);
        int getY();
        void setY(int y);
    void turnShape();
        piece randomPiece();
    private:
        std::vector<std::vector<int>> matrix; 
        piece p;
        int x=4;
        int y=1;
        int state=0;
};