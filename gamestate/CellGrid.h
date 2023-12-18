//
// Created by Ramil on 12/7/2023.
//

#ifndef LAB_2_CELLGRID_H
#define LAB_2_CELLGRID_H

#include <iostream>
#include <vector>

struct Cell {
    int x;
    int y;
    bool alive = false;
};

class CellGrid {
private:
    const int width;
    const int height;
    Cell** cells;
    std::vector<Cell*> aliveCells = std::vector<Cell*>();
public:
    const std::vector<Cell*> &GetAliveCells() const;

    const int getWidth() const;

    const int getHeight() const;



    virtual ~CellGrid();
    CellGrid(int width, int height);
    Cell GetCell(int x, int y);
    void AliveCell(int x, int y);

    void KillCell(int x, int y);
};


#endif //LAB_2_CELLGRID_H
